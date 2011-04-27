/*
$Id: pkt_time.c,v 1.13 2009/11/22 15:36:10 rhabarber1848 Exp $



 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de (rasc)

*/


#include "dvbsnoop.h"
#include "cmdline.h"
#include "pkt_time.h"

#include <unistd.h>
#include <time.h>


static struct timeval    last_tv = {0,0};


/*
  -- Print receive time of Packet

*/

static unsigned long timeval_to_ms(const struct timeval *tv)
{
	return (tv->tv_sec * 1000) + ((tv->tv_usec + 500) / 1000);
}

long delta_time_ms (struct timeval *tv, struct timeval *last_tv)
{
	return timeval_to_ms(tv) - timeval_to_ms(last_tv);
}

void  out_receive_time (int verbose, OPTION *opt)

{
 struct timeval           tv;
 time_t                   t;
 long                     ms;
 char                     tstr[128];



 switch (opt->time_mode) {

    case FULL_TIME:
            t = time (&t);
            strftime (tstr,sizeof(tstr)-1,"%a %Y-%m-%d  %H:%M:%S",
			localtime(&t));
            gettimeofday (&tv, NULL);
            out (verbose,"Time received: %s.%03ld\n", tstr, tv.tv_usec/1000 );
            break;

    case DELTA_TIME:
            gettimeofday (&tv, NULL);
	    ms = delta_time_ms(&tv, &last_tv);
            out (verbose,"Time (delta) received: %0ld.%03ld (sec)\n", ms / 1000, ms % 1000);
            last_tv.tv_sec  =  tv.tv_sec;
            last_tv.tv_usec =  tv.tv_usec;
            break;

    case NO_TIME:
    default:
            break;

 }

 return;
}




void  init_receive_time (void)

{
  gettimeofday (&last_tv, NULL);
}




