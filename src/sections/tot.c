/*
$Id: tot.c,v 1.12 2009/11/22 15:36:27 rhabarber1848 Exp $


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de  (rasc)


 -- TOT section
 -- Time Offset Table
 -- ETSI EN 300 468     5.2.6

*/

#include "dvbsnoop.h"
#include "tot.h"
#include "descriptors/descriptor.h"
#include "strings/dvb_str.h"
#include "misc/output.h"
#include "misc/pkt_time.h"

void section_TOT (u_char *b, int len)
{

 u_int      table_id;
 u_long     UTC_time_MJD;
 u_long     UTC_time_UTC;
 int        len1;


 

  out_nl (3,"TOT-decoding....");
  table_id = outBit_S2x_NL (3,"Table_ID: ",  b,  0, 8,
		  (char *(*)(u_long)) dvbstrTableID );     
  if (table_id != 0x73) {
    out_nl (3,"wrong Table ID");
    return;
  }


  outBit_Sx_NL (3,"section_syntax_indicator: ",		b,  8,  1);
  outBit_Sx_NL (6,"reserved_1: ",			b,  9,  1);
  outBit_Sx_NL (6,"reserved_2: ",			b, 10,  2);
  outBit_Sx_NL (3,"Section_length: ",			b, 12, 12);


  out (3,"UTC_time: ");
  UTC_time_MJD		 = getBits (b, 0, 24, 16);
  UTC_time_UTC		 = getBits (b, 0, 40, 24);
  print_time40 (3, UTC_time_MJD,UTC_time_UTC);
  out_NL (3);

  outBit_Sx_NL (6,"reserved_3: ",			b, 64,  4);


  len1 = outBit_Sx_NL (5,"Descriptor_loop_length: ",	b, 68, 12);
  b   += 10;

  indent (+1);
  while (len1 > 0) {
 	int x;

	x = descriptor (b, DVB_SI);
	len1 -= x;
	b    += x;
  }
  indent (-1);
  out_NL (3);


  outBit_Sx_NL (5,"CRC: ",				b,  0, 32);
}




