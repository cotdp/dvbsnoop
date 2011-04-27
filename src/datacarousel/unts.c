/*
$Id: unts.c,v 1.8 2009/11/22 15:36:05 rhabarber1848 Exp $


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de (rasc)


 -- UNT Section  (Update Notification Table)
 -- DSM-CC Data Carousel  ETSI TS 102 006

*/

#include "dvbsnoop.h"
#include "unts.h"
#include "dsmcc_misc.h"
#include "strings/dvb_str.h"
#include "strings/dsmcc_str.h"
#include "misc/output.h"

void section_DSMCC_UNT (u_char *b, int len)
{

 int        len1,i;
 u_int      table_id;
 u_int      section_length;



 out_nl (3,"UNT-decoding....");
 table_id = outBit_S2x_NL (3,"Table_ID: ",	b, 0, 8,
				(char *(*)(u_long))dvbstrTableID );
 if (table_id != 0x4b) {
   out_nl (3,"wrong Table ID");
   return;
 }


 outBit_Sx_NL (4,"Section_syntax_indicator: ",	b, 8, 1);
 outBit_Sx_NL (6,"reserved_1: ",		b, 9, 1);
 outBit_Sx_NL (6,"reserved_2: ",		b,10, 2);
 section_length = outBit_Sx_NL (5,"section_length: ",	b,12,12);
 outBit_S2x_NL(3,"Action_type: ",		b,24, 8,
			(char *(*)(u_long))dsmccStrAction_Type );
 outBit_Sx_NL (3,"OUI_hash: ",			b,32, 8);
 outBit_Sx_NL (6,"reserved_3: ",		b,40, 2);

 outBit_Sx_NL (3,"Version_number: ",		b,42, 5);
 outBit_S2x_NL(3,"Current_next_indicator: ",	b,47, 1,
			(char *(*)(u_long))dvbstrCurrentNextIndicator );
 outBit_Sx_NL (3,"Section_number: ",		b,48, 8);
 outBit_Sx_NL (3,"Last_section_number: ",	b,56, 8);

 outBit_S2x_NL(3,"OUI: ",			b,64,24,
			(char *(*)(u_long))dsmccStrOUI );
 outBit_S2x_NL(3,"Processing_order: ",		b,88, 8,
			(char *(*)(u_long))dsmccStrProcessing_order);

 b += 12;
 len1 = section_length - 9;



 /* common descriptor loop */

 i = dsmcc_pto_descriptor_loop ("common",b); 
 b    += i;
 len1 -= i;


 indent (+1);
 while (len1 > 4) {
	int len2;

	i= dsmcc_CompatibilityDescriptor(b);
	b    += i;
	len1 -= i;

	len2 = outBit_Sx_NL (3,"platform_loop_length: ",	b, 0,16);
	b    += 2;
	len1 -= 2;

	while (len2 > 0) {

 		i = dsmcc_pto_descriptor_loop ("target",b); 
		b    += i;
		len1 -= i;
		len2 -= i;

 		i = dsmcc_pto_descriptor_loop ("operational",b); 
		b    += i;
		len1 -= i;
		len2 -= i;
	}
	out_NL (4);
 }
 indent (-1);


 outBit_Sx_NL (5,"CRC: ",	b,0,32);
}




