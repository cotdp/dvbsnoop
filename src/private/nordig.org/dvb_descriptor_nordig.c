/*
$Id: dvb_descriptor_nordig.c,v 1.3 2008/09/01 08:06:07 mws Exp $ 


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de (rasc)

 -- Private DVB Descriptors  nordig.org

*/

#include "dvbsnoop.h"
#include "dvb_descriptor_nordig.h"
#include "strings/dvb_str.h"
#include "misc/hexprint.h"
#include "misc/output.h"

/*
 *
 * Private DVB descriptors
 * User Space: nordig.org
 *
 */

/*
   0x83  Logic Channel Descriptor
   NorDig-Basic ver 1.0.1, 01.07.2003
*/
void descriptor_PRIVATE_NordigORG_LogicChannelDescriptor (u_char *b)
{
	unsigned int tag = b[0];
	unsigned int len = b[1];
	unsigned int i;

	out_nl(4, "--> NorDig Logic Channel Descriptor ");

	b += 2;

	indent(+1);

	for (i = 0; i < len; i += 4) {
		unsigned int service_id = (b[i] << 8) | b[i + 1];
		unsigned int visible_service_flag = (b[i + 2] >> 7) & 1;
		unsigned int reserved = (b[i + 2] >> 6) & 1;
		unsigned int logic_channel_number = ((b[i + 2] << 8) | b[i + 3]) & 0x3fff;

		out_NL(4);
		out_SW_NL(4, "service_id: ", service_id);
		out_SB_NL(4, "visible_service_flag: ", visible_service_flag);
		out_SB_NL(4, "reserved: ", reserved);
		out_SW_NL(4, "logic_channel_number: ", logic_channel_number);
	}

	indent(-1);
	out_NL(4);
}

/*
   0xA0  Logic Channel Descriptor
   NorDig-Unified ver 2.0, 01.07.2008
*/
void descriptor_PRIVATE_NordigORG_ContentProtectionDescriptor (u_char *b)
{
	unsigned int tag = b[0];
	unsigned int len = b[1];
	unsigned int protectionLevel = b[2];

	out_nl(4, "--> NorDig Content Protection Descriptor ");

	b += 2;

	indent(+1);
	out_NL(4);
	out_SB_NL(2, "value: ", protectionLevel);

	switch(protectionLevel)
	{
		default:
		case 0x00:
			out_nl(4, "Outputs shall not be protected.");
			break;
		case 0x01:
			out_nl(4, "Content protection not required.");
			break;
		case 0x02:
			out_nl(4, "Content protection mandatory for video resolution > 576 lines.");
			break;
		case 0x03:
			out_nl(4, "Content protection mandatory regardless of video format and resolution.");
			break;
	}
	indent(-1);
	out_NL(4);
}
