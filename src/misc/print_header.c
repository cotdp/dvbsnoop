/*
$Id: print_header.c,v 1.8 2009/11/22 15:36:10 rhabarber1848 Exp $


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de (rasc)

*/


#include <stdio.h>

#include "dvbsnoop.h"
#include "print_header.h"
#include "misc/cmdline.h"
#include "misc/output.h"
#include "misc/pkt_time.h"




void  print_packet_header (OPTION *opt, char *packetTyp, u_int pid, int count, int length)

{
   char  str[50];
   char  *s;


   if (pid != DUMMY_PID) {
   	sprintf (str,"%u (0x%04x)",pid,pid);
	s = str;
   } else {
	s = "(Unkown PID)";
   }

   // Full Transport Stream Read?
   if (opt->ts_raw_mode && (opt->packet_mode == TS)) {
	s = "(Full TS read)";
   }


   out_nl (1,"\n------------------------------------------------------------");
   out_nl (1,"%s-Packet: %08ld   PID: %s, Length: %d (0x%04x)",
		packetTyp, count, s, length,length);

   if (opt->inpPidFile) {
   	out_nl (1,"from file: %s",opt->inpPidFile);
   } else {
   	out_receive_time (1, opt);
   }

//   if (skipped_bytes) {
//       out_nl (1,"Syncing %s... (%ld bytes skipped)",
//		packetTyp,skipped_bytes);
//   }

   out_nl (1,"------------------------------------------------------------");


}



