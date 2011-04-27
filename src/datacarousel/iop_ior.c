/*
$Id: iop_ior.c,v 1.5 2009/11/22 15:36:05 rhabarber1848 Exp $


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de (rasc)

 -- dsmcc  Interoperable Object Reference (IOR)
 -- TR 101 202 v1.2.1  4.7.5.2
 -- TS 102 812

*/

#include "dvbsnoop.h"
#include "iop_ior.h"
#include "biop_tag_tap.h"
#include "dsmcc_misc.h"

#include "misc/output.h"
#include "strings/dsmcc_str.h"

/*
 * dsmcc IOP::IOR ()
 * TR 101 202 v 1.2.1
 * return: length used
 */


int IOP_IOR (int v, u_char *b)
{
   u_char       *b_start = b;
   int		i,x;
   u_long 	n1;



	out_nl (v, "IOP::IOR:");
	indent (+1);


	n1 = outBit_Sx_NL (v,"type_id_length: ",	b,  0, 32);
	print_text_UTF8 (v, "type_id: ", b+4, n1);
	b += 4+n1;


	// alignment gap  (CDR alignment rule), should be 0xFF
	x = n1 % 4;
	if (x) {
		print_databytes (v,"alignment_gap:", b, 4-x);
		b += 4-x;
	}


	n1 = outBit_Sx_NL (v,"taggedProfiles_count: ",	b,  0, 32);
	b += 4;
	for (i=0; i < n1; i++) {
		u_long   n2;

		//  IOP_taggedProfile 
		n2 = IOP_taggedProfile (v, b);
		b += n2;

	}


	indent (-1);

	return b - b_start;
}




/*
 * TR 101 202 v 1.2.1
 * return: len
 */

u_long IOP_taggedProfile (int v, u_char *b)

{
  u_long  len;


	// e.g. BIOPProfileBody
	// e.g. LiteOptionsProfileBody

	len  = BIOP_TAG_dispatch (v,b);
  	return len;
}


