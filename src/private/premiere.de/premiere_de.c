/*
$Id: premiere_de.c,v 1.6 2009/11/22 15:36:20 rhabarber1848 Exp $


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de  (rasc)


  -- User defined table // Private
  -- Premiere Content Information Table CIT

*/




#include "dvbsnoop.h"
#include "premiere_de.h"

#include "section_premiere_cit.h"
#include "section_premiere_cpt.h"
#include "dvb_descriptor_premiere.h"



/*
 
 Please check for legal issues, when using provider specific
 data structures in your own software!
 Using  these data structures may require a certification or
 licensing process by the provider.

 */

static PRIV_DESCR_ID_FUNC pdescriptors[] = {
	{ 0xF0, DVB_SI,   descriptor_PRIVATE_PremiereDE_ContentOrder },
	{ 0xF1, DVB_SI,   descriptor_PRIVATE_PremiereDE_ParentalInformation },
	{ 0xF2, DVB_SI,   descriptor_PRIVATE_PremiereDE_ContentTransmission },
	{ 0x00,	0,        NULL } // end of table  (id = 0x00, funct = NULL)
};


static PRIV_SECTION_ID_FUNC psections[] = {
	{ 0xA0,	section_PRIVATE_PremiereDE_CIT },
	{ 0xA1,	section_PRIVATE_PremiereDE_CPT },
	{ 0x00, NULL }	// end of table  (id = 0x00, funct = NULL)
	
};





//
// -- Return private section/descriptor id tables
// -- for this scope
//

void getPrivate_PremiereDE ( PRIV_SECTION_ID_FUNC **psect,
		PRIV_DESCR_ID_FUNC **pdesc)
{
   *psect = psections;
   *pdesc = pdescriptors;
}




