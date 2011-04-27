/*
$Id: descriptor.c,v 1.33 2009/11/22 15:36:06 rhabarber1848 Exp $


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de (rasc)


 -- Descriptors 

*/


#include "dvbsnoop.h"
#include "descriptor.h"
#include "mpeg_descriptor.h"
#include "dvb_descriptor.h"
#include "dsmcc_carousel_descriptor.h"
#include "dsmcc_int_unt_descriptor.h"
#include "mhp_ait_descriptor.h"
#include "tva_rnt_descriptor.h"
#include "misc/hexprint.h"
#include "misc/output.h"

/*
  determine descriptor type and print it...
  return byte length
*/

int  descriptor  (u_char *b, DTAG_SCOPE scope)
{
 int len;
 int id;


  id  =  (int)b[0];  
  len = ((int)b[1]) + 2;   	// total length

  // nothing to print here? 
  // well, I guess all descriptors need a verbosity >=4...
  if (getMaxVerboseLevel() < 4) return len;

  indent (+1);


  switch  (scope) {

     case DSMCC_STREAM:
  		descriptorMPEG (b); 
		break;

     case DSMCC_CAROUSEL:
  		descriptorDSMCC_CAROUSEL (b);
		break;

     case DSMCC_INT_UNT:	// EN 301 192, TS 102 006
  		if (id < 0x40)	descriptorDSMCC_INT_UNT (b);
		else 		descriptorDVB (b);
		break;

     case MHP_AIT:
		descriptorMHP_AIT (b);
		break;

     case TVA_RNT:		// TS 102 323
  		if (id < 0x40)	descriptorMPEG (b);
		else		descriptorTVA (b);
		break;

     case MPEG:
     case DVB_SI:
     default:
  		if (id < 0x40)	descriptorMPEG (b);
		else	 	descriptorDVB (b);
		break;

  }


  indent (-1);

  return len;   // (descriptor total length)
}








/*
  Any  descriptor  (Basic Descriptor output)
  ETSI 300 468 // ISO 13818-1
*/

void descriptor_any (u_char *b)
{
 int  len;


 // tag		 = b[0];
 len       	 = b[1];

 print_databytes (4,"Descriptor-data:", b+2, len);
}





