/*
$Id: helper.c,v 1.43 2009/11/22 15:36:10 rhabarber1848 Exp $


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de (rasc)

*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>


#include "dvbsnoop.h"
#include "helper.h"
#include "hexprint.h"
#include "output.h"
#include "strings/dvb_str.h"






/*
  -- output bits
  -- get bits and print decode
  -- return: (unsigned long) value
 */

// out text and values without CR/LF

u_long outBit_Sx (int verbosity, const char *text, u_char *buf, int startbit, int bitlen)
{
   u_long value;

   value =  getBits(buf,0,startbit,bitlen);

   if (bitlen <= 8) {
	 out_SB (verbosity,text,(int)value);
   } else if (bitlen <= 16) {
	 out_SW (verbosity,text,(int)value);
   } else if (bitlen <= 24) {
	 out_ST (verbosity,text,(int)value);
   } else {
	 out_SL (verbosity,text,value);
   }

   return value;
}



// out text and values

u_long outBit_Sx_NL (int verbosity, const char *text, u_char *buf, int startbit, int bitlen)
{
  u_long value;

  value = outBit_Sx (verbosity,text,buf,startbit,bitlen);
  out_NL (verbosity);
  return value;

}




// out text, values and string related to value (string table function)

u_long outBit_S2x_NL (int verbosity, const char *text, u_char *buf, int startbit, int bitlen, char *(*f)(u_long) )
{
   u_long value;

   value =  getBits(buf,0,startbit,bitlen);

   if (bitlen <= 8) {
	 out_S2B_NL (verbosity,text,(int)value, (*f)(value));
   } else if (bitlen <= 16) {
	 out_S2W_NL (verbosity,text,(int)value, (*f)(value));
   } else if (bitlen <= 24) {
	 out_S2T_NL (verbosity,text,(int)value, (*f)(value));
   } else {
	 out_S2L_NL (verbosity,text,     value, (*f)(value));
   }

   return value;
}



// out text, values and text2

u_long outBit_S2Tx_NL (int verbosity, const char *text, u_char *buf, int startbit, int bitlen, const char *text2 )
{
   u_long value;

   value =  getBits(buf,0,startbit,bitlen);

   if (bitlen <= 8) {
	 out_S2B_NL (verbosity,text,(int)value, text2);
   } else if (bitlen <= 16) {
	 out_S2W_NL (verbosity,text,(int)value, text2);
   } else if (bitlen <= 24) {
	 out_S2T_NL (verbosity,text,(int)value, text2);
   } else {
	 out_S2L_NL (verbosity,text,     value, text2);
   }

   return value;
}





/*
  -- same for bitlen > 32
  -- return unsigned long long
 */

unsigned long long outBit64_Sx (int verbosity, const char *text, u_char *buf, int startbit, int bitlen)
{
   unsigned long long value;


   if (bitlen <= 48) {
   	value =  getBits48 (buf,0,startbit,bitlen);
	out_SLL (verbosity,text,(int)value);
   } else {
   	value =  getBits64 (buf,0,startbit,bitlen);
	out_SLL (verbosity,text,value);
   }

   return value;
}


unsigned long long outBit64_Sx_NL (int verbosity, const char *text, u_char *buf, int startbit, int bitlen)
{
  unsigned long long value;

  value = outBit64_Sx (verbosity,text,buf,startbit,bitlen);
  out_NL (verbosity);
  return value;

}






/*
  -----------------------------------------------------------------------------------
 */


/* 
  -- get bits out of buffer (max 32 bit!!!)
  -- return: value
  $$$ TODO  to be performance optimized!!
*/

//unsigned long XXgetBits (u_char *buf, int byte_offset, int startbit, int bitlen)
//{
// u_char *b;
// unsigned long  v;
// unsigned long mask;
// unsigned long tmp_long;
//
//
// b = &buf[byte_offset + (startbit / 8)];
// startbit %= 8;
//
// if (bitlen > 24) {
//	 // -- 24..32 bit
//   return (unsigned long) getBits48 (b, 0, startbit, bitlen);
// }
//
// // -- safe is 24 bitlen
// tmp_long = (unsigned long)(
//		 (*(b  )<<24) + (*(b+1)<<16) +
//		 (*(b+2)<< 8) +  *(b+3) );
//
// startbit = 32 - startbit - bitlen;
//
// tmp_long = tmp_long >> startbit;
// mask     = (1ULL << bitlen) - 1;  // 1ULL !!!
// v        = tmp_long & mask;
//
// return v;
//}


/* 
  -- get bits out of buffer (max 32 bit!!!)
  -- return: value
*/

unsigned long getBits (u_char *buf, int byte_offset, int startbit, int bitlen)
{
 u_char *b;
 unsigned long  v;
 unsigned long mask;
 unsigned long tmp_long;
 int           bitHigh;


 b = &buf[byte_offset + (startbit >> 3)];
 startbit %= 8;

 switch ((bitlen-1) >> 3) {
	 case -1:	// -- <=0 bits: always 0
		return 0L;
		break;

	case 0:		// -- 1..8 bit
 		tmp_long = (unsigned long)(
			(*(b  )<< 8) +  *(b+1) );
		bitHigh = 16;
		break;

	case 1:		// -- 9..16 bit
 		tmp_long = (unsigned long)(
		 	(*(b  )<<16) + (*(b+1)<< 8) +  *(b+2) );
		bitHigh = 24;
		break;

	case 2:		// -- 17..24 bit
 		tmp_long = (unsigned long)(
		 	(*(b  )<<24) + (*(b+1)<<16) +
			(*(b+2)<< 8) +  *(b+3) );
		bitHigh = 32;
		break;

	case 3:		// -- 25..32 bit
			// -- to be safe, we need 32+8 bit as shift range 
		return (unsigned long) getBits48 (b, 0, startbit, bitlen);
		break;

	default:	// -- 33.. bits: fail, deliver constant fail value
		out_nl (1," Error: getBits() request out of bound!!!! (report!!) \n");
		return (unsigned long) 0xFEFEFEFE;
		break;
 }

 startbit = bitHigh - startbit - bitlen;
 tmp_long = tmp_long >> startbit;
 mask     = (1ULL << bitlen) - 1;  // 1ULL !!!
 v        = tmp_long & mask;

 return v;
}






/*
  -- get bits out of buffer  (max 48 bit)
  -- extended bitrange, so it's slower
  -- return: value
 */

long long getBits48 (u_char *buf, int byte_offset, int startbit, int bitlen)
{
 u_char *b;
 unsigned long long v;
 unsigned long long mask;
 unsigned long long tmp;

 if (bitlen > 48) {
	out_nl (1," Error: getBits48() request out of bound!!!! (report!!) \n");
	return 0xFEFEFEFEFEFEFEFELL;
 }
 

 b = &buf[byte_offset + (startbit / 8)];
 startbit %= 8;


 // -- safe is 48 bitlen
 tmp = (unsigned long long)(
	 ((unsigned long long)*(b  )<<48) + ((unsigned long long)*(b+1)<<40) +
	 ((unsigned long long)*(b+2)<<32) + ((unsigned long long)*(b+3)<<24) +
	 (*(b+4)<<16) + (*(b+5)<< 8) + *(b+6) );

 startbit = 56 - startbit - bitlen;
 tmp      = tmp >> startbit;
 mask     = (1ULL << bitlen) - 1;	// 1ULL !!!
 v        = tmp & mask;

 return v;
}



/*
  -- get bits out of buffer   (max 64 bit)
  -- extended bitrange, so it's slower 
  -- return: value
 */

unsigned long long getBits64 (u_char *buf, int byte_offset, int startbit, int bitlen)
{
  unsigned long long x1,x2,x3;

  if (bitlen <= 32) {
     x3 = getBits (buf,byte_offset,startbit,bitlen); 
  } else {
     x1 = getBits (buf,byte_offset,startbit,32); 
     x2 = getBits (buf,byte_offset,startbit+32,bitlen-32); 
     x3 = (x1<<(bitlen-32)) + x2;
  }
  return x3;
}






/*
  -----------------------------------------------------------------------------------
 */




/*
  -- get ISO 639  (3char) language code into string[4]
  -- terminate string with \0
  -- return ptr to buf;
 */

u_char *getISO639_3 (u_char *str, u_char *buf)
{
  int i;

  strncpy ((char *) str, (char *)buf, 3);
  *(str+3) = '\0';

  // secure print of string
  for (i=0; i<3; i++) {
     if (!isprint(*(str+i))) {
	     *(str+i) = '.';
     }
  }
  
  return str;
}





/*
  -----------------------------------------------------------------------------------
 */





/*
  -- print_text_468A 
  -- ETSI EN 300 468  Annex A
  -- evaluate string and look on DVB control codes
  -- print the string
*/

static void print_text2_468A (int v, u_char *b, u_int len);

void print_text_468A (int v, const char *s,  u_char *b, u_int len)
{

 out (v, s);

 if (len <= 0) {
    out_nl (v,"\"\"");
 } else {
    out (v,"\"");
    print_text2_468A (v, b,len);
    out (v,"\"");
    out_nl (v,"  -- Charset: %s", dvbstrTextCharset_TYPE (*b));
 }

}


static void print_text2_468A (int v, u_char *b, u_int len)
{
  int    in_emphasis = 0;
  int    i;
  u_char c;
  u_char em_ON  = 0x86;
  u_char em_OFF = 0x87;

 
  for (i=0; i<len; i++) {
    c = b[i];

    if (i == 0 && c < 0x20) continue;   // opt. charset descript.

    if (c == em_ON) {
       in_emphasis = 1;
       out (v,"<EM>");
       continue;
    }
    if (c == em_OFF) {
       in_emphasis = 0;
       out (v,"</EM>");
       continue;
    }

       if (c == 0x8A)     out (v, "<BR>");
       else if (c < 0x20) out (v, ".");
       else               out (v, "%c", c);

  } // for
  

}


/*
  -- print_text_UTF8
  -- print the string using UTF8
  -- (use std_ascii)
*/

void print_text_UTF8 (int v, const char *s,  u_char *b, u_int len)
{
   print_std_ascii (v, s, b, len);
}



/*
  -- print standard ascii text
*/

void print_std_ascii (int v, const char *s, u_char *b, u_int len)
{
  int    i;
  u_char c;
 
  out (v,"%s\"",s);
  for (i=0; i<len; i++) {
    c = b[i];
    if (!isprint (c)) c = '.';
    out (v, "%c", c);
  } 
  out_nl (v,"\"");

}






/*
 -- print time  40 bit (MJD, UTC)
 -- print time  MJD
 -- print time  UTC
 --   16 Bit  MJD,  24 Bit UTC
*/ 

static void _print_time_mjd (int v, u_long mjd)
{
 if (mjd > 0) {
   long   y,m,d ,k;

   // algo: ETSI EN 300 468 - ANNEX C

   y =  (long) ((mjd  - 15078.2) / 365.25);
   m =  (long) ((mjd - 14956.1 - (long)(y * 365.25) ) / 30.6001);
   d =  (long) (mjd - 14956 - (long)(y * 365.25) - (long)(m * 30.6001));
   k =  (m == 14 || m == 15) ? 1 : 0;
   y = y + k + 1900;
   m = m - 1 - k*12;

   out (v, "%02d-%02d-%02d",y,m,d);
 }
}

static void _print_time_utc (int v, u_long utc)
{
 out (v, "%02lx:%02lx:%02lx (UTC)",
	 (utc>>16) &0xFF, (utc>>8) &0xFF, (utc) &0xFF);
}


void print_time_mjd (int v, u_long mjd)
{
  out (v, "0x%04lx [= ",mjd);
  _print_time_mjd (v, mjd);
  out (v,"]");
}

void print_time_utc (int v, u_long utc)
{
  out (v, "0x%06lx [= ",utc);
  _print_time_utc (v, utc);
  out (v,"]");

}

void print_time40 (int v, u_long mjd, u_long utc)
{
  out (v, "0x%lx%06lx [= ",mjd, utc);
  _print_time_mjd (v, mjd);
  out (v," ");
  _print_time_utc (v, utc);
  out (v,"]");
}



/*
 -- print 90kHz timebase
 -- 33 bit  z.B. xTS
*/ 

void print_timebase90kHz (int v, long long time90kHz)

{
   long long ull = time90kHz;

   	int     h,m,s,u;
	u_long  p = ull/9;


	// -- following lines basically taken from "dvbtextsubs  Dave Chapman"
	h=(p/(10000L*60*60));
	m=(p/(10000L*60))-(h*60);
	s=(p/10000L)-(h*3600)-(m*60);
	u=p-(h*10000L*60*60)-(m*10000L*60)-(s*10000L);

    	out (v,"%llu (0x%08llx)", ull,ull);
	out (v,"  [= 90 kHz-Timestamp: %d:%02d:%02d.%04d]", h,m,s,u);
}


/*
 -- print PCR timebase, 27 MHz
*/ 

void print_pcr_time (int v, long long time90kHz, int ext_27MHz)
{
   long long ull = time90kHz * 300 + ext_27MHz;

   	int        h,m,s;
	long       u;
	long long  p = ull/27;
	long long  fa = 1000000;

	// -- following lines basically taken from "dvbtextsubs  Dave Chapman"
	h=(p/(fa*60*60));
	m=(p/(fa*60))-(h*60);
	s=(p/fa)-(h*3600)-(m*60);
	u=p-(h*fa*60*60)-(m*fa*60)-(s*fa);

    	out (v,"%llu (0x%08llx)", ull,ull);
	out (v,"  [= PCR-Timestamp: %d:%02d:%02d.%06ld]", h,m,s,u);
}






/*
  -- print data bytes (str + hexdump)
  -- print  "Private Data" and Hex-Dump
*/
void print_databytes (int v, const char *str, u_char *b, u_int len)
{
  if (len > 0) {
     out_nl (v,str);
	indent (+1);
	printhex_buf (v+1,b,len);
	indent (-1);
  }
}

void print_private_data (int v, u_char *b, u_int len)
{
  print_databytes (v,"Private Data:",b,len);
}

void print_databytes_line  (int v, const char *str, u_char *b, u_int len)
{
  if (len > 0) {
     out (v,"%s ",str);
     printhexline_buf (v+1,b,len);
  }
}




/*
  -- print Bit Matrix  x * y
  -- print  Hex-Value and Bit-String  
  -- Matrix may start at any bit position
  -- x <= 64 bits !!
*/
void print_BitMatrix (int v, char *str, u_char *b, int bitoffset,  int matrix_x, int matrix_y)
{
  unsigned long long c;
  int                i;


  if (matrix_x <= 0 || matrix_y <= 0)  return;


  out_nl (v,"%s (%d x %d)",str,matrix_x,matrix_y);
  indent (1);
  while (matrix_y-- > 0) {

	if (matrix_x <= 32) {
		c = outBit_Sx   (v, "", b, bitoffset , matrix_x);
	} else {
		c = outBit64_Sx (v, "", b, bitoffset , matrix_x);
	}

	out (v,"   [= ");
        i = matrix_x;
	while (--i >= 0) {
		out (v, (c & 1<<i) ? "1" : "0");
	}
	out_nl (v,"]");

	bitoffset += matrix_x;
  }
  indent (-1);

}





/*
  -----------------------------------------------------------------------------------
 */





/*
   -- str2i
   -- string to integer
   --   x, 0x ist Hex
   --   ansonsten Dezimal
   return:  long int

*/

long  str2i  (char *s)
{
 long v;
 
 if (!s) s = "";

 v = strtol (s, NULL, 0);
 return v;

}





/*
   -- str2barray
   -- string to integer (byte array)
   --   x, 0x ist Hex, ansonsten Dezimal oder octal
   --- Input:  1 byte:    0xF0
   ---         multibyte: 0xFE.12.43.4F.6F (etc) (hex)
                          123.255.24 (dec)
   -- return:  <0 = error, 0 = no filter, >0 = count filter bytes
*/

int  str2barray  (char *s, u_char *barray, int max_len)
{
 int  i = 0;
 long v;
 int  base = 10;
 char *endptr = NULL;


 if (!s) s = "";

 // -- get base
 if (*s == '0') {
	base = 8;  // octal
 	if (*s && *(s+1) == 'x') base = 16; // hex
 }

 while (1)  {
	 if ( i >= max_len) break;

	 v = strtol (s, &endptr, base);
	 if ( v < 0 || v > 0xFF) return -1;
	 if (s == endptr) return -1; // illegal char...
	 barray[i++] = v;
	 if (! *endptr) break;   // end of string
	 s = endptr + 1;
 }

 return i;
}







/*
 -- latitude coordinates   (Cell Descriptors)
 -- longitude coordinates   (Cell Descriptors)
 -- ETSI EN 300 468
*/ 

static char *_str_cell_latitude_longitude (long ll, int angle);

char *str_cell_latitude (long latitude)
{
 // cell_latitude: This 16-bit field, coded as a two's complement number,
 // shall specify the latitude of the corner of a spherical rectangle that
 // approximately describes the coverage area of the cell indicated. It shall
 // be calculated by multiplying the value of the latitude field by
 // (90 ° /2^15 ). Southern latitudes shall be considered negative and
 // northern latitudes positive.

 return _str_cell_latitude_longitude (latitude, 90);
}


char *str_cell_longitude (long longitude)
{
 // cell_longitude: This 16-bit field, coded as a two's complement number, shall
 // specify the longitude of the corner of a spherical rectangle that approximately
 // describes the coverage area of the cell indicated. It shall be calculated by
 // multiplying the value of the longitude field by (180 ° /2^15 ). Western
 // longitudes shall be considered negative and eastern longitudes positive.

 return _str_cell_latitude_longitude (longitude, 180);
}


static char *_str_cell_latitude_longitude (long ll, int angle)
{
 long long  x;
 long       g1,g2;
 static     char s[40];	// $$$ not thread safe!

 x = (long long) ll * angle * 1000;
 x = x / (1<<15);

 g1 = x / 1000;
 g2 = x % 1000;
 if (g2 <0) g2 = 0 - g2;

 sprintf (s,"%ld.%03ld degree",g1,g2);
 return s;
}



/*
  -----------------------------------------------------------------------------------
 */




/*
 * -- display MAC-Address format
 *  -- input:  High- and Low Word (each 24bit)
 */

void displ_mac_addr (int v, long mac_H24, long mac_L24)
{

   out (v,"%02x:%02x:%02x",
	   (mac_H24>>16) & 0xFF, (mac_H24>>8) & 0xFF, mac_H24 & 0xFF);
   out (v,":%02x:%02x:%02x",
	   (mac_L24>>16) & 0xFF, (mac_L24>>8) & 0xFF, mac_L24 & 0xFF);

}




/*
 * -- display IP-Address format
 *  -- input: IP-Addr. 
 */

void displ_IPv4_addr (int v, u_long ip)
{
   out (v,"%d.%d.%d.%d",
	(ip>>24) & 0xFF, (ip>>16) & 0xFF, (ip>>8) & 0xFF, ip & 0xFF);
}





struct IPv6ADDR *getIPv6Addr (u_char *b, struct IPv6ADDR *x)
{
 	x->ip[0] = getBits (b, 0,   0, 32);
	x->ip[1] = getBits (b, 0,  32, 32);
	x->ip[2] = getBits (b, 0,  64, 32);
	x->ip[3] = getBits (b, 0,  96, 32);
	return x;
}


/*
 * -- display IPv6-Address format
 *  -- input: IPv6-Addr. 
 */

void displ_IPv6_addr (int v, struct IPv6ADDR *a)
{
   out (v,"%x:%x:%x:%x:%x:%x:%x:%x",
	(a->ip[0]>>16) & 0xFFFF, (a->ip[0]) & 0xFFFF,
	(a->ip[1]>>16) & 0xFFFF, (a->ip[1]) & 0xFFFF,
	(a->ip[2]>>16) & 0xFFFF, (a->ip[2]) & 0xFFFF,
	(a->ip[3]>>16) & 0xFFFF, (a->ip[3]) & 0xFFFF
       );
}







/*
  -----------------------------------------------------------------------------------
 */



/*
 * --  return a bit string for value, len bits
 * --  NOT thread-safe !!!  $$$
 */

char *str_bit32 (u_long value, int bits)
{
   static char bitstr[65];
   char *s = bitstr;

   if (bits > 64) bits = 64;
   s += bits;

   // reverse bit shift to get real order
 
   *s = '\0';
   while (bits-- > 0) {
	   *(--s) = (value & 0x01) ? '1' :'0';
	   value = value >> 1;
   }

   return bitstr;
}





//
//
// -- Length Check Helper
// -- return 1: ok, 0 = len<0
//
int lenCheckErrOut (int v, int len)
{
  const char *err_str="==> Something is seriously wrong (length overrun check)!!!";

  if (len < 0) {
	  out_nl (v,err_str);
	  return 0;
  }
  return 1;

}


