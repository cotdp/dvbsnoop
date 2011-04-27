/*
$Id: ints.c,v 1.16 2009/11/22 15:36:05 rhabarber1848 Exp $


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de (rasc)


 --  INT Section
 --  IP/MAC Notification Section
 --  DSM-CC Data Carousel  EN 301 192 

*/

#include "dvbsnoop.h"
#include "ints.h"
#include "dsmcc_misc.h"

#include "strings/dvb_str.h"
#include "strings/dsmcc_str.h"
#include "misc/output.h"

void section_DSMCC_INT (u_char *b, int len)
{
 /* EN 301 192 7.x */

 int        len1,i;
 u_int      table_id;
 u_int      section_length;



 out_nl (3,"INT-decoding....");
 table_id = outBit_S2x_NL (3,"Table_ID: ",	b, 0, 8,
				(char *(*)(u_long))dvbstrTableID );
 if (table_id != 0x4c) {
   out_nl (3,"wrong Table ID");
   return;
 }


 outBit_Sx_NL (4,"Section_syntax_indicator: ",	b, 8, 1);
 outBit_Sx_NL (6,"reserved_1: ",		b, 9, 1);
 outBit_Sx_NL (6,"reserved_2: ",		b,10, 2);
 section_length = outBit_Sx_NL (5,"section_length: ",	b,12,12);
 outBit_S2x_NL(3,"Action_type: ",		b,24, 8,
			(char *(*)(u_long))dsmccStrAction_Type );
 outBit_Sx_NL (3,"Platform_id_hash: ",		b,32, 8);
 outBit_Sx_NL (6,"reserved_3: ",		b,40, 2);

 outBit_Sx_NL (3,"Version_number: ",		b,42, 5);
 outBit_S2x_NL(3,"Current_next_indicator: ",	b,47, 1,
			(char *(*)(u_long))dvbstrCurrentNextIndicator );
 outBit_Sx_NL (3,"Section_number: ",		b,48, 8);
 outBit_Sx_NL (3,"Last_section_number: ",	b,56, 8);

 outBit_S2x_NL(3,"Platform_id: ",		b,64,24,
			(char *(*)(u_long))dsmccStrPlatform_ID );
 outBit_S2x_NL(3,"Processing_order: ",		b,88, 8,
			(char *(*)(u_long))dsmccStrProcessing_order);

 b += 12;
 len1 = section_length - 9;



 i = dsmcc_pto_descriptor_loop ("platform",b); 
 b   += i;
 len1 -= i;

 while (len1 > 4) {
 	i = dsmcc_pto_descriptor_loop ("target",b); 
	b   += i;
	len1 -= i;

 	i = dsmcc_pto_descriptor_loop ("operational",b); 
	b   += i;
	len1 -= i;
 }
 out_NL (4);


 outBit_Sx_NL (5,"CRC: ",	b,0,32);
}





