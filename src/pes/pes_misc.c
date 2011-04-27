/*
$Id: pes_misc.c,v 1.12 2009/11/22 15:36:13 rhabarber1848 Exp $


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de  (rasc)



 -- PS misc.
 -- PES misc.

*/




#include "dvbsnoop.h"
#include "pes_misc.h"
#include "strings/dvb_str.h"
#include "misc/hexprint.h"
#include "misc/helper.h"
#include "misc/output.h"




/*
 *  PTS //  DTS
 *  Len is 36 bits fixed
 */

void  print_xTS_field (int v, const char *str, u_char *b, int bit_offset) 
{
  long long   xTS_32_30;
  long long   xTS_29_15;
  long long   xTS_14_0;
  long long   ull;
  int         bo = bit_offset;
  int         v1 = v+1;


  out_nl (v,"%s:",str);
  indent (+1);

    xTS_32_30 = outBit_Sx_NL (v1,"bit[32..30]: ",	b, bo+0,  3);
                outBit_Sx_NL (v1,"marker_bit: ",	b, bo+3,  1);
    xTS_29_15 = outBit_Sx_NL (v1,"bit[29..15]: ",	b, bo+4, 15);
                outBit_Sx_NL (v1,"marker_bit: ",	b, bo+19, 1);
    xTS_14_0  = outBit_Sx_NL (v1,"bit[14..0]: ",	b, bo+20,15);
                outBit_Sx_NL (v1,"marker_bit: ",	b, bo+35, 1);

    ull = (xTS_32_30<<30) + (xTS_29_15<<15) + xTS_14_0;
    out (v," ==> %s: ", str);
    print_timebase90kHz (v, ull);
    out_NL (v);

  indent (-1);
}







