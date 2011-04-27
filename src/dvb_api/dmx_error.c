/*
$Id: dmx_error.c,v 1.4 2009/11/22 15:36:07 rhabarber1848 Exp $


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de  (rasc)


 -- simple error output for DMX & file I/O

*/


#include <stdio.h>
#include <stdlib.h>
#include <errno.h>



int  IO_error (char *str)
{
   char *s;
   int  err;
  

   s = (str) ? str : "";
   err = errno;

   switch (err) {

	case EOVERFLOW:
		fprintf (stderr,
			"Error(%d): %s: Buffer overflow, stream bandwidth to high\n",
			err,s);
		break;

	default:
		fprintf (stderr,"Error(%d): ",err);
		perror(s);
		break;

   }

   return err;

}


