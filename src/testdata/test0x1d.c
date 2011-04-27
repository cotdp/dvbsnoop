/*
$Id: test0x1d.c,v 1.11 2009/11/22 15:36:32 rhabarber1848 Exp $


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de



   -- test data section
   -- DVB test and measurement signalling channel
   -- ETSI TR 101 291

*/

#include "dvbsnoop.h"
#include "test0x1d.h"
#include "misc/output.h"
#include "misc/hexprint.h"

void section_TESTDATA (u_char *b, int len)
{

 out_nl (3,"TESTDATA-decoding....");

 outBit_Sx_NL (3,"Table_ID: ",			b,  0, 6);
 outBit_Sx_NL (3,"priority_level: ",		b,  6, 2);
 outBit_Sx_NL (3,"section_syntax_indicator: ",	b,  8, 1);


 // $$$ TODO   ...
 print_databytes(5,"Data:",b,len);

}




