/*
$Id: fe_signal.c,v 1.18 2009/11/22 15:36:07 rhabarber1848 Exp $


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de  (rasc)


 -- Signal Statistics  Current Frequency/Transponder
 --  DVB-API 

*/


#include <stdint.h>
#include <sys/time.h>
#include <unistd.h>
#include <errno.h>


#include "dvbsnoop.h"
#include "fe_signal.h"
#include "fe_misc.h"

#include "misc/cmdline.h"
#include "misc/output.h"
#include "misc/pkt_time.h"
#include "misc/sig_abort.h"

#include "dmx_error.h"
#include "dvb_api.h"


int  do_SignalStrength (OPTION *opt)

{
  int        fd_fe = 0;
  struct timeval tv,last_tv, first_tv;
  u_long     count;
  FE_SIGNAL  s;
  FE_SIG_CAP has;

 


  if (opt->inpPidFile) {
	fprintf (stderr,"Error: FileMode not supported...\n");
	return -1;
  } 


  if((fd_fe = open(opt->devFE,O_RDONLY)) < 0){
     IO_error(opt->devFE);
     return -1;
  }



  // -- check capabilities
 
  has.ber 	= capability_Check (fd_fe, FE_READ_BER);
  has.snr	= capability_Check (fd_fe, FE_READ_SNR);
  has.strength	= capability_Check (fd_fe, FE_READ_SIGNAL_STRENGTH);
  has.status	= capability_Check (fd_fe, FE_READ_STATUS);
  has.ublocks	= capability_Check (fd_fe, FE_READ_UNCORRECTED_BLOCKS);



   indent (0);
   out_NL (2);
   out_nl (2,"---------------------------------------------------------");
   out_nl (2,"Transponder/Frequency signal strength statistics...");
   if (opt->rd_packet_count > 0) {
	   out_nl (2,"max cycle count: %ld ", opt->rd_packet_count);
   }
   out_nl (9,"Capabilities: BER: %d  SNR: %d  SIG: %d  STAT: %d  UBLK: %d",
		   has.ber, has.snr, has.strength, has.status, has.ublocks);
   out_nl (2,"---------------------------------------------------------");




   gettimeofday (&first_tv, NULL);
   last_tv.tv_sec  =  first_tv.tv_sec;
   last_tv.tv_usec =  first_tv.tv_usec;



  count = 0;
  while ( !isSigAbort() ) {
	int  err;
	int  d_tim_ms;


	count++;
	out (6, "cycle: %lu  ",count);

	gettimeofday (&tv, NULL);
   	d_tim_ms = delta_time_ms (&tv, &last_tv);
	if (d_tim_ms <= 0) d_tim_ms = 1;   //  ignore usecs 
	last_tv.tv_sec  =  tv.tv_sec;
	last_tv.tv_usec =  tv.tv_usec;

	out (6, "d_time: %ld.%03ld s  ", d_tim_ms / 1000UL, d_tim_ms % 1000UL);

				   

	err = read_Signal (fd_fe, &s, &has);
	    if (err == -1) return -1;
//	    if (err == -2) {
//		    out_nl (1," No signal...");
//		    continue;
//	    }

	    // & 0xFFFF necessary, due to interface transformations??
	if (has.strength)  out (1,"Sig: %u  ", s.strength & 0xFFFFL);
	if (has.snr)	   out (2,"SNR: %u  ", s.snr & 0xFFFFL);
	if (has.ber)	   out (3,"BER: %lu  ",s.ber);
	if (has.ublocks)   out (4,"UBLK: %ld  ",s.ublocks);
	if (has.status) {
		out (4,"Stat: 0x%02x ",s.status);
		out_status_detail (5,s.status);
	}
	out_NL(1);


	if (opt->timeout_ms) usleep (opt->timeout_ms * 1000);
	if (d_tim_ms == 0) usleep (1000);	// don't kill the system


	// count cycles? ?
	if (opt->rd_packet_count && (opt->rd_packet_count <= count)) break;

  } // while



  close(fd_fe);
  return 0;
}



