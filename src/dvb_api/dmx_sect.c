/*
$Id: dmx_sect.c,v 1.35 2009/11/22 15:36:07 rhabarber1848 Exp $


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de (rasc)


 --  Sections Streams
 --  For more information please see:
 --  ISO 13818 (-1) and ETSI 300 468

*/


#include "dvbsnoop.h"
#include "misc/cmdline.h"
#include "misc/output.h"
#include "misc/pid_mem.h"
#include "misc/sig_abort.h"

#include "sections/sectables.h"

#include "dvb_api.h"
#include "file_io.h"
#include "dmx_error.h"
#include "dmx_sect.h"



#define SECT_BUF_SIZE (256*1024)	/* default DMX buffer size */
#define READ_BUF_SIZE (32*1024)		/* section work buffer (section is @5K) */


static long  sect_read (int fd, u_char *buf, long buflen);
static int   doReadSECT_2 (OPTION *opt);





/* 
 -- read sections
 -- single pid sections or spider pid sections (opt.)
 */

int  doReadSECT (OPTION *opt)
{
   int    status;


   // -- first pid
   status = doReadSECT_2 (opt);
   mark_PidMem_as_used (opt->pid);

   if (status) return status;


   // -- spider option requested?
   if (opt->spider_pid) {
   	u_int  pid;

	while ( !isSigAbort() ) {
		pid = get_UnusedPidFromMem ();
		if (pid == INVALID_PID) break;

		// new spidered pid
		opt->pid = pid;
		status = doReadSECT_2 (opt);
		mark_PidMem_as_used (pid);

		if (status) return status;
	}

   }

   return status;
}





/* 
 -- read single section
 */

static int  doReadSECT_2 (OPTION *opt)

{
  int     fd;
  u_char  buf[READ_BUF_SIZE]; 		/* data buffer */
  long    count;
  long    filtered_count;
  char    *f;
  int     openMode;
  int     dmxMode;
  long    dmx_buffer_size = SECT_BUF_SIZE;



  if (opt->inpPidFile) {
  	f        = opt->inpPidFile;
  	openMode = O_RDONLY | O_LARGEFILE | O_BINARY;
        dmxMode  = 0;
  } else {
  	f        = opt->devDemux;
  	openMode = O_RDWR;
        dmxMode  = 1;
  }


  if((fd = open(f,openMode)) < 0){
      IO_error(f);
      return -1;
  }


  /*
   -- init demux
  */

  if (dmxMode) {
    struct dmx_sct_filter_params flt;


    // -- alloc dmx buffer for SECTION
    if (opt->rd_buffer_size > 0) {
	    dmx_buffer_size = opt->rd_buffer_size;
    }

    if (ioctl(fd,DMX_SET_BUFFER_SIZE, dmx_buffer_size) < 0) {
	IO_error ("DMX_SET_BUFFER_SIZE failed: ");
	close (fd);
	return -1;
    }


    memset (&flt, 0, sizeof (struct dmx_sct_filter_params));

    flt.pid = opt->pid;


    // -- set filter (info from the dvb api v3:)
    // --  The filter comprises 16 bytes(?) covering byte 0 and byte 3..17 in
    // --  a section,thus excluding bytes 1 and 2 (len field of a sect).

    { int i;
      for (i=0; i < opt->filterLen && i < DMX_FILTER_SIZE; i++) {
	    flt.filter.filter[i] = opt->filter[i];
	    flt.filter.mask[i]   = opt->mask[i];
      }
     //    memcpy(&flt.filter.filter, opt->filter, DMX_FILTER_SIZE);
     //    memcpy(&flt.filter.mask, opt->mask, DMX_FILTER_SIZE);
    }

    

    flt.timeout = opt->timeout_ms;
    flt.flags = DMX_IMMEDIATE_START;
    if (opt->crc) flt.flags |= DMX_CHECK_CRC;

    if (ioctl (fd, DMX_SET_FILTER, &flt) < 0) {
	IO_error ("DMX_SET_FILTER failed: ");
 	close(fd);
	return -1;
    }

  }




/*
  -- read SECTION packets for pid
*/

  count = 0;
  filtered_count = 0;
  while ( !isSigAbort() ) {
    long   n;
    int    filter_match = 1;


    n = sect_read(fd,buf,sizeof(buf));

    // -- error or eof?
    if (n < 0) {
	int err;
	char s[64];

	sprintf (s,"read (PID 0x%04x)",opt->pid);
	err = IO_error(s);
	if (err == ETIMEDOUT) break;		// Timout, abort
	continue;
    }

    if (n == 0) {
	if (dmxMode) continue;	// dmxmode = no eof!
	else break;		// filemode eof 
    }



    count ++;



    // -- FILE filter mode when reading from file (soft section filter)
    // --  The filter comprises 16 bytes(?) covering byte 0 and byte 3..17
   
    if (! dmxMode) {					// file read mode
      int i;
      for (i=0; i < opt->filterLen; i++) {
	    int j;
	    j =  (i) ? i+2 : 0;			// Byte 0, 3..17

	    if ( (buf[j] & opt->mask[i]) != (opt->filter[i] & opt->mask[i]) ) {
    		filter_match = 0;   // fail!
		break;
	    }
      }
    }



    // -- packet output ? (binary or decoded)
    // -- This happens, when filter are matching (hard or soft filter)
 
    if (filter_match) { 

	filtered_count++;

	if (opt->binary_out) {

	       // direct write to FD 1 ( == stdout)
	       write (1, buf,n);

	} else {

	       processSI_packet (opt->pid, count, buf, n);

	} 

    }  // filter_match: packet out



    // Clean Buffer
//    if (n > 0 && n < sizeof(buf)) memset (buf,0,n+1); 


    // count packets ?
    if (opt->rd_packet_count > 0) {
       if (count >= opt->rd_packet_count) break;
    }
    if (opt->dec_packet_count > 0) {
       if (filtered_count >= opt->dec_packet_count) break;
    }


  } // while


  /*
    -- Stop Demux
  */

  if (dmxMode) {
    ioctl (fd, DMX_STOP, 0);
  }


  close(fd);
  return 0;
}







/*
 * -- section read
 * -- read one section
 * -- return: equivalent to read();
 */

static long  sect_read (int fd, u_char *buf, long buflen)
{
    int    n;
    int    sect_len;


    n = read(fd,buf,3);				// read section header
    if (n <= 0) return n;			// error or strange, abort

    // section size
    // -- table_id 	8  uimsbf
    // -- some stuff   	4  bits
    // -- sectionlength 12 uimsbf

    sect_len = ((buf[1] & 0x0F) << 8) + buf[2];	// get section size
    if (sect_len > (buflen-3)) return -1;	// something odd?

    n = read(fd,buf+3,sect_len);		// read 1 section
    if (n >=0) n += 3;				// we already read header bytes

    return n;
}






/*
 // $$$ TODO
*   u_int      table_id;
+   u_int      section_syntax_indicator;		
    u_int      reserved_1;
    u_int      reserved_2;
    u_int      section_length;
    u_int      service_id;
    u_int      reserved_3;
*   u_int      version_number;
    u_int      current_next_indicator;
*   u_int      section_number;
*   u_int      last_section_number;


    -- get table_id + version      tid_ver[32] (id, version, last_sec_no,completed)
     --> check section_syntax
     --> get last_section_nr & sect_number

 */

