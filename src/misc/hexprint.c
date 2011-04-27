/*
$Id: hexprint.c,v 1.11 2009/11/22 15:36:10 rhabarber1848 Exp $


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2007   Rainer.Scherg@gmx.de (rasc)

*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>



#include "dvbsnoop.h"
#include "hexprint.h"
#include "output.h"



/*
 -- global static data

*/


int HexPrintmode = 0;



static void printhexdump_buf (int verbose, u_char *buf, int len);
static void printhexdump2_buf (int verbose, u_char *buf, int len);





/*
   -- print-modus setzen
*/

void setHexPrintMode (int i)

{
  HexPrintmode = i;
}






/*
  - print buffer as Hex Printout
*/

void printhex_buf (int verbose, u_char *buf, int n)

{

   switch (HexPrintmode) {

      case 0:
	return;
	break;

      case 1:
	printhexdump_buf (verbose,buf,n);
	break;

      case 2:
	printhexline_buf (verbose,buf,n);
	break;

      case 3:
	printasciiline_buf (verbose,buf,n);
	break;

      case 4:
	printhexdump2_buf (verbose,buf,n);
	break;


      default:
	printhexdump_buf (verbose,buf,n);
	break;
   }

   return;
}




/*
 -- multi line dump HEX+ASCII
  0000:  42 f1 59 04 41 f1 00 00 00 01 ff 2e e3 ff 80 1f 
  0000:   B  .  Y  .  A  .  .  .  .  .  .  .  .  .  .  . 

*/
static void printhexdump_buf (int verbose, u_char *buf, int n)
{
 int i, j;
 u_char c;
 int WID=16;

j = 0;
while (j*WID < n) {

 out (verbose,"  %04x:  ",j*WID);
 for (i=0; i<WID; i++) {
   if ( (i+j*WID) >= n) break;
   c = buf[i+j*WID];
   out (verbose,"%02x ",(int)c);
 }
 out_NL (verbose);

 out (verbose,"  %04x:  ",j*WID);
 for (i=0; i<WID; i++) {
   if ( (i+j*WID) >= n) break;
   c = buf[i+j*WID];
   out (verbose," %c ",isprint((int)c) ?c:'.');
 }
 out_NL (verbose);
 
 j++;

}


}




/*
 -- single line dump HEX
   42 f1 59 04 41 f1 00 00 00 01 ff 2e e3 ff 80 1f 4
*/
void printhexline_buf (int verbose, u_char *buf, int n)
{
 int i;

 for (i=0; i<n; i++) {
   out (verbose,"%02x ",(int)buf[i]);
 }
 out_NL (verbose);
}




/*
 -- single line ascii
    B.Y.A...........H...RTL World...RTL. Television.
*/
void printasciiline_buf (int verbose, u_char *buf, int n)
{
 int    i;
 u_char c;

 for (i=0; i<n; i++) {
   c = buf[i];
   out (verbose,"%c",isprint((int)c) ?c:'.');
 }
 out_NL (verbose);
}



/*
 -- single line dump HEX+ASCII
    0000:  40 f2 f4 00 01 c1 01 01  f0 00 f2 e7 04 31 00 01   @............1..

*/
static void printhexdump2_buf (int verbose, u_char *buf, int n)
{
 int    i, j;
 int    k;
 u_char c;
 int    WID=16;

j = 0;
while (j*WID < n) {

 out (verbose,"  %04x:  ",j*WID);

 for (i=0; i<WID; i++) {
   if ( (i+j*WID) >= n) break;
   c = buf[i+j*WID];
   out (verbose,"%02x ",(int)c);
   if ((i+1)%8 == 0) out (verbose," ");
 }

 for (k=i; k<WID; k++) {
   out (verbose, "   ");   // filler
   if ((k+1)%8 == 0) out (verbose," ");
 }

 out (verbose," ");

 for (i=0; i<WID; i++) {
   if ( (i+j*WID) >= n) break;
   c = buf[i+j*WID];
   out (verbose,"%c",isprint((int)c) ?c:'.');
 }
 out_NL (verbose);

 
 j++;

}


}




