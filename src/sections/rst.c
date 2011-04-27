/*
$Id: rst.c,v 1.10 2009/11/22 15:36:27 rhabarber1848 Exp $


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de  (rasc)



   -- RST section
   -- Running Status Table
   -- ETSI EN 300 468     5.2.7

*/

#include "dvbsnoop.h"
#include "rst.h"
#include "strings/dvb_str.h"
#include "misc/output.h"

void section_RST (u_char *b, int len)
{

 typedef struct  _RST {
    u_int      table_id;
    u_int      section_syntax_indicator;		
    u_int      reserved_1;
    u_int      reserved_2;
    u_int      section_length;

    // N1 RST_LIST2

 } RST;


 typedef struct _RST_LIST2 {
    u_int      transport_stream_id;
    u_int      original_network_id; 
    u_int      service_id; 
    u_int      event_id; 
    u_int      reserved_1;
    u_int      running_status;
 } RST_LIST2;



 RST        r;
 RST_LIST2  r2;
 int        len1;


 
 r.table_id 			 = b[0];
 r.section_syntax_indicator	 = getBits (b, 0, 8, 1);
 r.reserved_1 			 = getBits (b, 0, 9, 1);
 r.reserved_2 			 = getBits (b, 0, 10, 2);
 r.section_length		 = getBits (b, 0, 12, 12);


 out_nl (3,"RST-decoding....");
 out_S2B_NL (3,"Table_ID: ",r.table_id, dvbstrTableID (r.table_id));
 if (r.table_id != 0x71) {
   out_nl (3,"wrong Table ID");
   return;
 }


 out_SB_NL (3,"section_syntax_indicator: ",r.section_syntax_indicator);
 out_SB_NL (6,"reserved_1: ",r.reserved_1);
 out_SB_NL (6,"reserved_2: ",r.reserved_2);
 out_SW_NL (5,"Section_length: ",r.section_length);


 len1 = r.section_length - 3;
 b   += 3;

 indent (+1);
 while (len1 > 0) {

   r2.transport_stream_id	 = getBits (b, 0,  0,  16);
   r2.original_network_id	 = getBits (b, 0, 16,  16);
   r2.service_id		 = getBits (b, 0, 32,  16);
   r2.event_id			 = getBits (b, 0, 48,  16);
   r2.reserved_1		 = getBits (b, 0, 64,   5);
   r2.running_status		 = getBits (b, 0, 69,   3);

   b    += 9;
   len1 -= 9;

   out_NL (3);
   out_SW_NL  (3,"Transport_stream_ID: ",r2.transport_stream_id);
   out_S2W_NL (3,"Original_network_ID: ",r2.original_network_id,
        dvbstrOriginalNetwork_ID(r2.original_network_id));
   out_S2W_NL (3,"Service_ID: ",r2.service_id,
	 " --> refers to PMT program_number"); 
   out_SW_NL  (3,"Event_ID: ",r2.event_id);
   out_SB_NL  (6,"reserved_1: ",r2.reserved_1);
   out_S2B_NL (3,"Running_status: ",r2.running_status,
	dvbstrRunningStatus_FLAG (r2.running_status));

 } // while len1
 indent (-1);


}




