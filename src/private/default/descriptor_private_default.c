/*
$Id: descriptor_private_default.c,v 1.3 2009/11/22 15:36:18 rhabarber1848 Exp $


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de (rasc)


 -- Descriptors 

*/


#include "dvbsnoop.h"
#include "descriptor_private_default.h"
#include "misc/helper.h"
#include "misc/output.h"






/*
  User defined descriptor  (Basic Descriptor output)
  ETSI 300 468 // ISO 13818-1
*/

void descriptor_PRIVATE_default (u_char *b)
{
 int  len;

 // tag		 = b[0];
 len       	 = b[1];

 print_databytes (4,"Descriptor-data:", b+2, len);
}


