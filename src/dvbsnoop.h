/*
$Id: dvbsnoop.h,v 1.25 2009/11/22 15:36:05 rhabarber1848 Exp $


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2005   Rainer.Scherg@gmx.de

*/

#ifndef __DVBSNOOP_H
#define __DVBSNOOP_H 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#include "version.h"
#include "misc/helper.h"
#include "misc/output.h"



//
// -- some DVB definitions
//

#define MAX_PID      0x1FFF
#define PID_FULL_TS  0x2000	/* special PID for reading full/raw TS */
				/* THIS is defined by Linux DVB-API !! */

#define DUMMY_PID    0xFFFF	/* special if no pid is needed */
#define INVALID_PID  0xFEFE	/* a invalid PID*/




//
// -- BSD style type shortcuts...
// -- may be already defined by system (typedef in linux/types.h)
// -- so we overwrite this via #define to avoid compiler warnings
//

#define u_char  unsigned char
#define u_int   unsigned int
#define u_long  unsigned long


#endif


