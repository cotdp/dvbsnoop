/*
$Id: eicta_org.c,v 1.1 2008/08/30 19:23:40 obi Exp $


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de  (rasc)


  -- Private Data Structures for:
  -- eicta.org

*/

#include "dvbsnoop.h"
#include "eicta_org.h"
#include "dvb_descriptor_eicta.h"

static PRIV_DESCR_ID_FUNC pdescriptors[] = {
	{ 0x83, DVB_SI,   descriptor_PRIVATE_EictaORG_LogicalChannelDescriptor },
	{ 0x84, DVB_SI,   descriptor_PRIVATE_EictaORG_PreferredNameListDescriptor },
	{ 0x85, DVB_SI,   descriptor_PRIVATE_EictaORG_PreferredNameIdentifierDescriptor },
	{ 0x86, DVB_SI,   descriptor_PRIVATE_EictaORG_EacemStreamIdentifierDescriptor },
	{ 0x00,	0,        NULL } // end of table  (id = 0x00, funct = NULL)
};

//
// -- Return private section/descriptor id tables
// -- for this scope
//

void getPrivate_EictaORG ( PRIV_SECTION_ID_FUNC **psect,
		PRIV_DESCR_ID_FUNC **pdesc)
{
   *psect = NULL;
   *pdesc = pdescriptors;
}

