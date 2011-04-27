/*
$Id: dmx_pes.c,v 1.38 2009/11/22 15:36:07 rhabarber1848 Exp $


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de (rasc)


 -- Streams: PES  & PS

 --  For more information please see:
 --  ISO 13818-1 and ETSI 300 468

*/


#include "dvbsnoop.h"
#include "misc/cmdline.h"
#include "misc/output.h"
#include "misc/sig_abort.h"

#include "pes/pespacket.h"
#include "dvb_api.h"
#include "file_io.h"
#include "dmx_error.h"
#include "dmx_pes.h"



#define PES_BUF_SIZE  (256 * 1024)	// default PES dmx buffer size 
#define READ_BUF_SIZE (256 * 1024)  	// larger (64KB + 6 Bytes) !!!/
#define PUSHBACK_BUF_SIZE (128)		// < 1024 bytes!!  see below  
#define SKIP_BUF_SIZE  (1024)		// for debugging, etc. 




static void out_SkipBuffer (int v, int len);
static long pes_SyncBufferRead (int fd, u_char *buf, u_long max_len, u_long *skipped_bytes);

#define  DIRECT_BUFFERED_READ  1		// see below!
static int  pes_rawBufferedPushByte (u_char c);
static long pes_rawBufferedRead (int fd, u_char *dest_buf, u_long dest_len);






// int  doReadPS (OPTION *opt)
int  doReadPES (OPTION *opt)

{
  int     fd;
  u_char  buf[READ_BUF_SIZE]; 		/* data buffer */
  u_char  *b;				/* ptr to packet start */
  long    count;
  char    *f;
  int     openMode;
  int     dmxMode;
  long    dmx_buffer_size = PES_BUF_SIZE;




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
    struct dmx_pes_filter_params flt;


    // -- alloc dmx buffer for PES
    if (opt->rd_buffer_size > 0) {
	    dmx_buffer_size = opt->rd_buffer_size;
    }

    if (ioctl(fd,DMX_SET_BUFFER_SIZE, dmx_buffer_size) < 0) {
	IO_error ("DMX_SET_BUFFER_SIZE failed: ");
	close (fd);
	return -1;
    }

    memset (&flt, 0, sizeof (struct dmx_pes_filter_params));

    flt.pid = opt->pid;
    flt.input  = DMX_IN_FRONTEND;
    flt.output = DMX_OUT_TAP;
    flt.pes_type = DMX_PES_OTHER;
    flt.flags = DMX_IMMEDIATE_START;

    if (ioctl(fd,DMX_SET_PES_FILTER,&flt) < 0) {
	IO_error ("DMX_SET_PES_FILTER failed: ");
	close (fd);
	return -1;
    }

  }




/*
  -- read PES packet for pid
*/

  count = 0;
  while (! isSigAbort() ) {
    long    n;
    u_long  skipped_bytes = 0;


    //  -- Read PES packet  (sync Read)
    n = pes_SyncBufferRead (fd,buf,sizeof(buf), &skipped_bytes);
    b = buf;


    // -- error or eof?
    if (n < 0) {
	int err;
	
	err = IO_error("read");
	// if (err == ETIMEDOUT) break;		// Timout, abort
	continue;
    }

    if (n == 0) {
	if (dmxMode) continue;	// dmxmode = no eof!
	else break;		// filemode eof 
    }


    count ++;

    if (opt->binary_out) {

	// direct write to FD 1 ( == stdout)
	write (1, b, n);

    } else {

    	// -- skipped Data to get sync byte?
    	if (skipped_bytes) {
		out_nl (3,"!!! %ld bytes skipped to get PS/PES sync!!!",skipped_bytes);
		out_SkipBuffer (8, skipped_bytes);
    	}

	processPS_PES_packet (opt->pid, count, b, n);

    } // bin_out



    // Clean Buffer
//    if (n > 0 && n < sizeof(buf)) memset (buf,0,n+1); 


    // count packets ?
    if (opt->rd_packet_count > 0) {
       if (count >= opt->rd_packet_count) break;
    }
    if (opt->dec_packet_count > 0) {
       if (count >= opt->dec_packet_count) break;
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




// -----------------------------------------------------------



u_char SkipBuffer[SKIP_BUF_SIZE];



/*
  -- output skipped bytes from last read
 */

static void  out_SkipBuffer (int v, int len)

{
  int  lmax;
  int  l;

   lmax = (sizeof(SkipBuffer)/sizeof(u_char));
   l = (len > lmax) ? lmax : len;

   print_databytes (v,"Skipped bytes:", SkipBuffer, l);
   
   if (l == lmax) {
   	out_nl (v,"...");
   	out_NL (v);
   }

}




/*
  -- read PES packet (Synced)
  -- buffer pre-read bytes for next execution
  -- return: len // read()-return code
*/

static long pes_SyncBufferRead (int fd, u_char *buf, u_long max_len, u_long *skipped_bytes)

{
    u_long  sync;
    u_char  *org_buf = buf;


    // -- simple PES sync... seek for 0x000001 (PES_SYNC_BYTE)
    // ISO/IEC 13818-1:
    // -- packet_start_code_prefix -- The packet_start_code_prefix is
    // -- a 24-bit code. Together with the stream_id that follows it constitutes
    // -- a packet start code that identifies the beginning of a packet.
    // -- The packet_start_code_prefix  is the bit stream
    // -- '0000 0000 0000 0000 0000 0001' (0x000001).


    *skipped_bytes = 0;
    sync = 0xFFFFFFFF;


    // -- seek packet sync start

    while (1) {
	u_char b[4];
        int    n;

	n = pes_rawBufferedRead (fd, b,1);
	if (n <= 0) return n;			// error or strange, abort

	// -- byte shift for packet_start_code_prefix
	// -- sync found? 0x000001 + valid PESstream_ID or PS_stream_ID

	sync = (sync << 8) | *b;
	if ( (sync & 0xFFFFFF00) == 0x00000100 ) {
		*skipped_bytes -= 3;
    		buf[0] = 0x00;			// write sync + ID to buffer
		buf[1] = 0x00;
		buf[2] = 0x01;
		buf[3] = *b;
		break;
	}

	// -- store skipped bytes
	if ( (*skipped_bytes) < (sizeof(SkipBuffer)/sizeof(u_char)) ) {
		SkipBuffer[*skipped_bytes] = *b;
	}

	(*skipped_bytes)++;
    }



    // -- Sync found!
    // -- evaluate packet_id and seek packet end (next sync)


    if (buf[3] >= 0xBC)  {			// PES system packet with length

        long    n1,n2;
	long    l;

	n1 = pes_rawBufferedRead (fd, buf+4,2);
	if (n1 < 0) return n1;

    	if (n1 == 2) {
        	l = (buf[4]<<8) + buf[5];		// PES packet size...
		n1 = 6; 				// 4+2 bytes read

		if (l > 0) {
			n2 = pes_rawBufferedRead (fd, buf+n1, (unsigned int) l );
           		return  (n2 < 0) ? n2 : n1+n2;
		} else {	// unbound stream!
			max_len -= n1;					// l=0
			buf     += n1;
		}
    	} else {
		max_len -= n1 + 4;
		buf     += n1 + 4;
	}

    } else {
	max_len -=  4;
	buf     +=  4;
    }



    // -- seek packet end (sync to next packet)
    // -- ISO 13818-1 length=0 packets (unbound video streams)
    // -- ISO 13818-2 packets


    sync = 0xFFFFFFFF;
    while (max_len > 0) {
	u_char c;
	int    n;

	// $$$ TODO: may be optimized 
	n = pes_rawBufferedRead (fd, buf,1);
	if (n < 0) return n;

	c = *buf++;
	max_len -= n;

	// -- EOF
	if (n == 0) {
		return (long) (buf - org_buf);
	}


	// -- next packet found? (sync detected)
	sync = (sync << 8) | c;
	if ( (sync & 0x00FFFFFF) == 0x000001 ) {
		pes_rawBufferedPushByte (*(--buf));	 // push back sync bytes
		pes_rawBufferedPushByte (*(--buf));
		pes_rawBufferedPushByte (*(--buf));
		return (long) (buf - org_buf);
	}
    }

    return -1;					// buffer overflow
}







// -----------------------------------------------------------



//
// -- PS/PES raw buffer operations (prior to pes sync)
//

//
// -- Byte Push Back Buffer to raw stream buffer
// -- return: -1: buffer overflow
//


static u_char  PB_buffer[PUSHBACK_BUF_SIZE];   // not to large, many bytes might be pushed
static int     PB_pos = 0;


static int pes_rawBufferedPushByte (u_char c)
{
	if ( PB_pos >= (sizeof(PB_buffer) / sizeof(u_char)) ) {
		return -1;		// overflow
	}

	PB_buffer[PB_pos++] = c;
	return 0;
}







//
// -- 2 implementations to choose...
// -- over time only one will survive...
//


#ifdef DIRECT_BUFFERED_READ

/*
  -- raw read PES stream (check push backs)
  -- pre-read bytes for next call
  -- return: len // read()-return code
*/

static long pes_rawBufferedRead (int fd, u_char *dest_buf, u_long dest_len)

{
 int n1 = 0;
 int n2 = 0;


  // -- Bytes in PushBack buffer?
  // -- copy to destination buffer
 
  while ( (PB_pos > 0) && (dest_len > 0) ) {
	*dest_buf++ = PB_buffer[--PB_pos];
	dest_len--;
	n1++;
  }

  if (dest_len > 0) {
  	n2 = read(fd,dest_buf,dest_len);
	if (n2 < 0) return n2;
  }

  return n1 + n2;
}



#else



/*
  -- raw read PES stream buffered (+ check push backs)
  -- buffer pre-read bytes for next call
  -- disadvantage:  driver -> memcopy -> readbuffer -> memcopy -> pes_packet-buffer
  -- return: len // read()-return code
*/

static long pes_rawBufferedRead (int fd, u_char *dest_buf, u_long dest_len)

{
#define RAW_READ_BUF_SIZE (16 * 1024)		/* buffered read buffer        */ 
  static u_char  *rd_buf = (u_char *)NULL;
  static u_int   pos_Start;
  static u_int   pos_End;

  u_char	 *org_dest_buf = dest_buf;



  // -- first time, init buffer
  if (! rd_buf) {
	  pos_Start = 0;
	  pos_End   = 0;
	  rd_buf = malloc (RAW_READ_BUF_SIZE * sizeof(u_char));
	  if (! rd_buf) {
		  IO_error("malloc");
		  exit (1);
	  }
  }


  // -- Bytes in PushBack buffer?
  // -- copy to destination buffer
 
  while ( (PB_pos > 0) && (dest_len > 0) ) {
	*dest_buf++ = PB_buffer[--PB_pos];
	dest_len--;
  }




  // -- transfere data from rd buffer 

  while (dest_len > 0) {
	int  copy_len;
	int  stored_len;
	int  n;


	stored_len = pos_End - pos_Start;
	copy_len   = (dest_len <= stored_len) ? dest_len : stored_len;

	if (copy_len > 0) {
		memcpy (dest_buf, rd_buf+pos_Start, copy_len);
		pos_Start += copy_len;
		dest_buf  += copy_len;
		dest_len  -= copy_len;
	} else {
		pos_Start = 0;
		pos_End   = 0;
    		n = read(fd,rd_buf,RAW_READ_BUF_SIZE);
		if (n <= 0) return n;
		pos_End = n;
	}

  }

  return (long) (dest_buf - org_dest_buf);
}

#endif











// $$$ TODO:
// read unbound video streams (length 0) until next sync is read
// push back function for already pre-read bytes





// $$$ TODO
// also read iso 13818-2 and iso 13818-3 streams

