/*
$Id: dvb_descriptor_eicta.c,v 1.1 2008/08/30 19:23:40 obi Exp $ 


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de (rasc)

 -- Private DVB Descriptors  eicta.org

*/

#include "dvbsnoop.h"
#include "dvb_descriptor_eicta.h"
#include "strings/dvb_str.h"
#include "misc/hexprint.h"
#include "misc/output.h"

/*
 *
 * Private DVB descriptors
 * User Space: eicta.org
 *
 */

/*
 * 0x83: Logical Channel Descriptor
 * e-book_ed_2.02 corr-acro.doc
 */
void descriptor_PRIVATE_EictaORG_LogicalChannelDescriptor (u_char *b)
{
	unsigned int len = b[1];
	unsigned int i;

	out_nl(4, "--> eicta.org Logical Channel Descriptor");

	b += 2;

	indent(+1);

	for (i = 0; i < len; i += 4) {
		unsigned int service_id = (b[i] << 8) | b[i + 1];
		unsigned int visible_service_flag = (b[i + 2] >> 7) & 1;
		unsigned int reserved = (b[i + 2] >> 2) & 0x1f;
		unsigned int logical_channel_number = ((b[i + 2] << 8) | b[i + 3]) & 0x3ff;

		out_NL(5);
		out_SW_NL(5, "service_id: ", service_id);
		out_SB_NL(5, "visible_service_flag: ", visible_service_flag);
		out_SB_NL(5, "reserved: ", reserved);
		out_SW_NL(5, "logical_channel_number: ", logical_channel_number);
	}

	indent(-1);
	out_NL(4);
}

/*
 * 0x84: Preferred Name List Descriptor
 * e-book_ed_2.02 corr-acro.doc
 */
void descriptor_PRIVATE_EictaORG_PreferredNameListDescriptor (u_char *b)
{
	unsigned int len = b[1];
	unsigned int i, j;

	out_nl(4, "--> eicta.org Preferred Name List Descriptor");

	b += 2;

	indent(+1);

	for (i = 0; i < len; i += 4) {
		unsigned int ISO_639_language_code = (b[i] << 16) | (b[i + 1] << 8) | b[i + 2];
		unsigned int name_count = b[i + 3];

		out_NL(4);
		out_SL_NL(4, "ISO_639_language_code: ", ISO_639_language_code);
		out_SB_NL(4, "name_count: ", name_count);

		indent(+1);

		for (j = 0; j < name_count; j++) {
			unsigned int name_id = b[i + 4];
			unsigned int name_length = b[i + 5];
			const char *name = &b[i + 6];

			out_NL(4);
			out_SB_NL(4, "name_id: ", name_id);
			out_SB_NL(4, "name_length: ", name_length);

			if (name_length > 0)
				out_nl(4, "name: %.s", name_length, name);

			i += name_length + 2;
		}

		indent(-1);
	}

	indent(-1);
	out_NL(4);
}

/*
 * 0x85: Preferred Name Identifier Descriptor
 * e-book_ed_2.02 corr-acro.doc
 */
void descriptor_PRIVATE_EictaORG_PreferredNameIdentifierDescriptor (u_char *b)
{
	out_nl(4, "--> eicta.org Preferred Name Identifier Descriptor");

	indent(+1);

	out_SB_NL(4, "name_id: ", b[2]);

	indent(-1);
	out_NL(4);
}

/*
 * 0x86: Eacem Stream Identifier Descriptor
 * e-book_ed_2.02 corr-acro.doc
 */
void descriptor_PRIVATE_EictaORG_EacemStreamIdentifierDescriptor (u_char *b)
{
	out_nl(4, "--> eicta.org Eacem Stream Identifier Descriptor");

	indent(+1);

	out_SB_NL(4, "version_byte: ", b[2]);

	indent(-1);
	out_NL(4);
}

