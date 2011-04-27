/*
$Id: dmx_ts.c,v 1.38 2009/11/22 15:36:07 rhabarber1848 Exp $


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de  (rasc)


 -- Transport Streams
 --  For more information please see:
 --  ISO 13818 (-1) and ETSI 300 468

*/


#include "dvbsnoop.h"
#include "misc/cmdline.h"
#include "misc/output.h"
#include "misc/sig_abort.h"

#include "ts/tslayer.h"
#include "ts/ts2secpes.h"
#include "ts/ts_cc_check.h"

#include "dvb_api.h"
#include "file_io.h"
#include "dmx_error.h"
#include "dmx_ts.h"




#define TS_PACKET_LEN (188)              /* TS RDSIZE is fixed !! */
#define TS_SYNC_BYTE  (0x47)             /* SyncByte fuer TS  ISO 138181-1 */
#define TS_BUF_SIZE   (256 * 1024)	 /* default DMX_Buffer Size for TS */
#define READ_BUF_SIZE (3*TS_PACKET_LEN)  /* min. 2x TS_PACKET_LEN!!! */



static long ts_SyncRead (int fd, u_char *buf, long max_buflen, long *skipped_bytes);





int  doReadTS (OPTION *opt)

{
  int     fd_dmx = 0, fd_dvr = 0;
  u_char  buf[READ_BUF_SIZE]; 	/* data buffer */
  u_char  *b;			/* ptr for packet start */
  long    count;
  long    filtered_count;
  char    *f;
  int     openMode;
  int     fileMode;
  long    dmx_buffer_size = TS_BUF_SIZE;


  

  if (opt->inpPidFile) {
  	f        = opt->inpPidFile;
  	openMode = O_RDONLY | O_LARGEFILE | O_BINARY;
        fileMode = 1;
  } else {
  	f        = opt->devDvr;
  	openMode = O_RDONLY;
        fileMode = 0;
  } 


  if((fd_dvr = open(f,openMode)) < 0){
      IO_error(f);
      return -1;
  }


  


  /*
   -- init demux
  */

  if (!fileMode) {
    struct dmx_pes_filter_params flt;

    if((fd_dmx = open(opt->devDemux,O_RDWR)) < 0){
        IO_error(opt->devDemux);
	close (fd_dvr);
        return -1;
    }


    // -- alloc dmx buffer for TS
    if (opt->rd_buffer_size > 0) {
	    dmx_buffer_size = opt->rd_buffer_size;
    }

    // -- full Transport Stream Read?? (special DVB-API-PID...)
    if (opt->ts_raw_mode) {
	    opt->pid = PID_FULL_TS;
    }


    if (ioctl(fd_dmx,DMX_SET_BUFFER_SIZE, dmx_buffer_size) < 0) {
	IO_error ("DMX_SET_BUFFER_SIZE failed: ");
	close (fd_dmx);
	close (fd_dvr);
	return -1;
    }

    memset (&flt, 0, sizeof (struct dmx_pes_filter_params));

    flt.pid = opt->pid;
    flt.input  = DMX_IN_FRONTEND;
    flt.output = DMX_OUT_TS_TAP;
    flt.pes_type = DMX_PES_OTHER;
    flt.flags = DMX_IMMEDIATE_START;

    if (ioctl(fd_dmx,DMX_SET_PES_FILTER,&flt) < 0) {
	IO_error ("DMX_SET_PES_FILTER failed: ");
	close (fd_dmx);
	close (fd_dvr);
	return -1;
    }

  }


  // -- acquire TS subdecoding buffer
  if (opt->ts_subdecode) {
	ts2SecPesInit ();
  }
  // -- init TS CC check
  ts_cc_init ();


/*
  -- read TS packets for pid
*/

  count = 0;
  filtered_count = 0;
  while ( ! isSigAbort() ) {
    long   n;
    long   skipped_bytes    = 0;
    int    pid_filter_match = 1;
    int    packet_pid       = -1;



    // -- Sync TS read!
    n = ts_SyncRead (fd_dvr,buf,sizeof(buf), &skipped_bytes);
    b = buf+(skipped_bytes % TS_PACKET_LEN);



    // -- error or eof?
    if (n < 0) {
	int err;
	
	err = IO_error("read");
	// if (err == ETIMEDOUT) break;		// Timout, abort
	continue;
    }

    if (n == 0) {
	if (!fileMode) continue;	// DVRmode = no eof!
	else {			// filemode eof 
	  ts2SecPes_LastPacketReadSubdecode_Output ();
	  break;
	}
    }



    count ++;



    // -- skipped Data to get sync byte?
    if (skipped_bytes) {
	if (! opt->binary_out) {
		out_nl (3,"!!! %ld bytes skipped to get TS sync!!!");
	}
    }

    // -- SyncByte for TS packet and correct len?
    if (b[0] != TS_SYNC_BYTE || n != TS_PACKET_LEN) {
	if (! opt->binary_out) {
		out_nl (3,"!!! Wrong SyncByte or packet length mismatch (= no TS)!!!");
	}
	continue;
    }



    // -- PID soft filter mode
    // -- We alway do this check (even if we are reading directly
    // -- from dvb device and PID has already been filtered by demux)
   
    packet_pid = getBits (b, 0,11, 13);
    if ((opt->pid >= 0) && (opt->pid <= MAX_PID) && (opt->pid != packet_pid)) {
	pid_filter_match = 0;
    }



    // -- packet output ? (binary or decoded)
    // -- This happens, when filter are matching (hard or soft filter)


    if (pid_filter_match) { 

	filtered_count++;


	if (opt->binary_out) {

		// direct write to FD 1 ( == stdout)
		write (1, b, n);

    	} else {

		processTS_packet (packet_pid, filtered_count, b, n);

	} 

    } // pid_filter_match: packet out




    // count packets ?
    if (opt->rd_packet_count > 0) {
       if (count >= opt->rd_packet_count) break;
    }
    if (opt->dec_packet_count > 0) {
       if (filtered_count >= opt->dec_packet_count) break;
    }


  } // while



  // -- release TS subdecoding buffer
  if (opt->ts_subdecode) ts2SecPesFree ();
  // -- release TS CC checka buffer, etc.
  ts_cc_init ();


  // -- Stop Demux
  if (!fileMode) {
     ioctl (fd_dmx, DMX_STOP, 0);

     close(fd_dmx);
  }

  close(fd_dvr);
  return 0;
}






/*
 * -- sync read (optimized = avoid multiple byte reads)
 * -- Seek TS sync-byte and read packet in buffer
 * -- ATTENTION:  packet is not stored at buf[0]
 *  --       -->  packet starts at buf[skipped_bytes % TS_PACKET_LEN] !!!
 * -- return: equivalent to read();
 */

static long  ts_SyncRead (int fd, u_char *buf, long max_buflen, long *skipped_bytes)
{
    int    n1,n2;
    int    i;
    int    found;


    // -- simple TS sync...
    // -- $$$ to be improved:
    // -- $$$  (best would be: check if buf[188] is also a sync byte)
 

    *skipped_bytes = 0;
    found = 0;
    while (! found) {
    	n1 = read(fd,buf,TS_PACKET_LEN);
    	if (n1 <= 0) return n1;			// error or strange, abort

    	for (i=0;i<n1; i++) {			// search sync byte
		if (buf[i] == TS_SYNC_BYTE) {
			found = 1;
			break;
		}
    	}
    	*skipped_bytes += i;
    }

    // -- Sync found!
    // -- read skipped number of bytes per read try

    if (i == 0) return n1;			// already complete packet read...

    n2 = read(fd,buf+n1,TS_PACKET_LEN-n1+i);	// continue read TS packet
    if (n2 >=0) n2 = n1+n2-i; ;			// should be TS_PACKET_LEN anyway...

    return n2;
}










