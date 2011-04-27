/*
$Id: emm_ecm.c,v 1.12 2009/11/22 15:36:27 rhabarber1848 Exp $


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de (rasc)


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2004   Rainer.Scherg@gmx.de



   -- EMM / ECM Data packet

*/

#include "dvbsnoop.h"
#include "emm_ecm.h"
#include "descriptors/descriptor.h"
#include "strings/dvb_str.h"
#include "misc/helper.h"
#include "misc/output.h"

void section_EMM_ECM (u_char *b, int len)
{
 /* */

 typedef struct  _EMM_ECM {
    u_int      table_id;
    u_int      section_syntax_indicator;		
    u_int      reserved_1;
    u_int      reserved_2;
    u_int      section_length;
    

 } EMM_ECM;




 EMM_ECM  e;
 //int n;


 
 e.table_id 			 = b[0];
 e.section_syntax_indicator	 = getBits (b, 0,  8, 1);
 e.reserved_1 			 = getBits (b, 0,  9, 1);
 e.reserved_2 			 = getBits (b, 0, 10, 2);
 e.section_length		 = getBits (b, 0, 12, 12);



 out_nl (3,"CAMT-decoding....");
 out_S2B_NL (3,"Table_ID: ",e.table_id, dvbstrTableID (e.table_id));

 out_SB_NL (3,"section_syntax_indicator: ",e.section_syntax_indicator);
 out_SB_NL (6,"reserved_1: ",e.reserved_1);
 out_SB_NL (6,"reserved_2: ",e.reserved_2);
 out_SW_NL (5,"Section_length: ",e.section_length);

 print_databytes(3,"CA_message_section_data:",b+3,e.section_length);

 //  !!! decoding the complete ECM/EMM stream may be illegal
 //      so we don't do this!
 //      secrets are secrets even if they are openly transmitted!
 //      you are not allowed to enhance this section!

}
