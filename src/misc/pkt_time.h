/*
$Id: pkt_time.h,v 1.11 2009/11/22 15:36:10 rhabarber1848 Exp $


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de (rasc)

*/


#ifndef __PKT_TIME
#define __PKT_TIME


#include "cmdline.h"
#include "sys/time.h"



void  out_receive_time (int verbose, OPTION *opt);
void  init_receive_time (void);
long delta_time_ms (struct timeval *tv, struct timeval *tv_last);


#endif


