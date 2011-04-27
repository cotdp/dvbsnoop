/*
$Id: pat.c,v 1.12 2009/11/22 15:36:27 rhabarber1848 Exp $


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de  (rasc)


 -- PAT section

*/

#include "dvbsnoop.h"
#include "pat.h"
#include "strings/dvb_str.h"
#include "misc/output.h"
#include "misc/pid_mem.h"

void section_PAT (u_char *b, int len)
{
 /* IS13818-1  S. 62 */

 typedef struct  _PAT {
    u_int      table_id;
    u_int      section_syntax_indicator;		
    u_int      reserved_1;
    u_int      section_length;
    u_int      transport_stream_id;
    u_int      reserved_2;
    u_int      version_number;
    u_int      current_next_indicator;
    u_int      section_number;
    u_int      last_section_number;

    // N pat_list

    u_long     CRC;
 } PAT;

 typedef struct _PAT_LIST {
    u_int      program_number;
    u_int      reserved;
    u_int      network_pmt_PID;
 } PAT_LIST;



 PAT p;
 PAT_LIST pl;
 int n;


 
 p.table_id 			 = b[0];
 p.section_syntax_indicator	 = getBits (b, 0, 8, 1);
 p.reserved_1 			 = getBits (b, 0, 10, 2);
 p.section_length		 = getBits (b, 0, 12, 12);
 p.transport_stream_id		 = getBits (b, 0, 24, 16);
 p.reserved_2 			 = getBits (b, 0, 40, 2);
 p.version_number 		 = getBits (b, 0, 42, 5);
 p.current_next_indicator	 = getBits (b, 0, 47, 1);
 p.section_number 		 = getBits (b, 0, 48, 8);
 p.last_section_number 		 = getBits (b, 0, 56, 8);



 out_nl (3,"PAT-decoding....");
 out_S2B_NL (3,"Table_ID: ",p.table_id, dvbstrTableID (p.table_id));
 if (p.table_id != 0x00) {
   out_nl (3,"wrong Table ID");
   return;
 }

 out_SB_NL (3,"section_syntax_indicator: ",p.section_syntax_indicator);
 out_SB_NL (6,"(fixed): ",0);
 out_SB_NL (6,"reserved_1: ",p.reserved_1);
 out_SW_NL (5,"Section_length: ",p.section_length);


 out_SW_NL (3,"Transport_Stream_ID: ",p.transport_stream_id);
 out_SB_NL (6,"reserved_2: ",p.reserved_2);
 out_SB_NL (3,"Version_number: ",p.version_number);
 out_S2B_NL(3,"current_next_indicator: ",p.current_next_indicator, dvbstrCurrentNextIndicator(p.current_next_indicator));
 out_SB_NL (3,"Section_number: ",p.section_number);
 out_SB_NL (3,"Last_Section_number: ",p.last_section_number);



 // PID list...
 // n = section_length - CRC  - front bytes
 // n = len / anzahl bytes pro pid angabe.
 // Buffer to start of List

 n  = p.section_length - 5 - 4;

 b = b + 8;
 indent (+1);
 for (; n>=4; n=n-4) {
	pl.program_number	 = getBits (b, 0, 0, 16);
	pl.reserved		 = getBits (b, 0, 16, 3);
	pl.network_pmt_PID	 = getBits (b, 0, 19, 13);
	b += 4;

	store_PidToMem (pl.network_pmt_PID);

 	out_NL (3);
	out_SW_NL (3,"Program_number: ",pl.program_number);
	out_SB_NL (6,"reserved: ",pl.reserved);
	out_SW_NL (3,(pl.program_number) ?"Program_map_PID: " :"Network_PID: ",
	             pl.network_pmt_PID);

 }
 indent (-1);
 out_NL (3);

 p.CRC = getBits (b,0,0,32);
 out_SL_NL (5,"CRC: ",p.CRC);

}
