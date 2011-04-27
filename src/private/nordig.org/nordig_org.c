/*
$Id: nordig_org.c,v 1.3 2009/11/22 15:36:18 rhabarber1848 Exp $


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de  (rasc)


  -- Private Data Structures for:
  -- nordig.org

*/




#include "dvbsnoop.h"
#include "nordig_org.h"
#include "dvb_descriptor_nordig.h"


static PRIV_DESCR_ID_FUNC pdescriptors[] = {
	{ 0x83, DVB_SI,   descriptor_PRIVATE_NordigORG_LogicChannelDescriptor },
	{ 0xA0, DVB_SI,   descriptor_PRIVATE_NordigORG_ContentProtectionDescriptor },
	{ 0x00,	0,        NULL } // end of table  (id = 0x00, funct = NULL)
};

//
// -- Return private section/descriptor id tables
// -- for this scope
//

void getPrivate_NordigORG ( PRIV_SECTION_ID_FUNC **psect,
		PRIV_DESCR_ID_FUNC **pdesc)
{
   *psect = NULL;
   *pdesc = pdescriptors;
}




