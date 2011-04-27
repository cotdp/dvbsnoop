/*
$Id: st.c,v 1.9 2009/11/22 15:36:27 rhabarber1848 Exp $


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de  (rasc)


 -- ST section (stuffing)

*/

#include "dvbsnoop.h"
#include "st.h"
#include "strings/dvb_str.h"
#include "misc/output.h"
#include "misc/hexprint.h"

/*
 -- ST section (stuffing)
 -- ETSI EN 300 468   5.2.8
*/

void section_ST (u_char *b, int len)
{

 typedef struct  _ST {
    u_int      table_id;
    u_int      section_syntax_indicator;		
    u_int      reserved_1;
    u_int      reserved_2;
    u_int      section_length;

    // N  databytes

 } ST;


 ST s;


 
 s.table_id 			 = b[0];
 s.section_syntax_indicator	 = getBits (b, 0, 8, 1);
 s.reserved_1 			 = getBits (b, 0, 9, 1);
 s.reserved_2 			 = getBits (b, 0, 10, 2);
 s.section_length		 = getBits (b, 0, 12, 12);


 out_nl (3,"ST-decoding....");
 out_S2B_NL (3,"Table_ID: ",s.table_id, dvbstrTableID (s.table_id));
 if (s.table_id != 0x72) {
   out_nl (3,"wrong Table ID");
   return;
 }

 out_SB_NL (3,"section_syntax_indicator: ",s.section_syntax_indicator);
 out_SB_NL (6,"reserved_1: ",s.reserved_1);
 out_SB_NL (6,"reserved_2: ",s.reserved_2);
 out_SW_NL (5,"Section_length: ",s.section_length);

 b += 3;
 print_databytes (3,"Section data:", b, s.section_length);

}
