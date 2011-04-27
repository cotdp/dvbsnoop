/*
$Id: sectables.c,v 1.37 2009/11/22 15:36:27 rhabarber1848 Exp $


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de  (rasc)


 -- For more information please see: ISO 13818 (-1) and ETSI 300 468

*/


#include "dvbsnoop.h"
#include "sectables.h"

#include "pat.h"
#include "cat.h"
#include "pmt.h"
#include "tsdt.h"
#include "nit.h"
#include "sdt.h"
#include "st.h"
#include "bat.h"
#include "tdt.h"
#include "tot.h"
#include "rst.h"
#include "dit.h"
#include "sit.h"
#include "eit.h"
#include "mdt.h"
#include "emm_ecm.h"

#include "datacarousel/ait.h"
#include "datacarousel/dsmcc.h"
#include "datacarousel/datagram.h"
#include "datacarousel/ints.h"
#include "datacarousel/unts.h"
#include "datacarousel/mpe_fec.h"

#include "tvanytime/rnt.h"
#include "tvanytime/cs.h"

#include "private/userdefs.h"

#include "testdata/test0x1d.h"

#include "strings/dvb_str.h"
#include "misc/output.h"
#include "misc/hexprint.h"
#include "misc/cmdline.h"
#include "misc/crc32.h"
#include "misc/print_header.h"



void  guess_table (u_char *buf, int len, u_int pid);




//
// -- process SI packet (Sections)
// -- hexdump, decoding
//

void processSI_packet (u_int pid, long pkt_nr, u_char *buf, int len)
{
	
  OPTION *opt  = getOptionPtr();


       indent (0);
       print_packet_header (opt, "SECT", opt->pid, pkt_nr, len);


       if (opt->buffer_hexdump) {
           printhex_buf (0,buf, len);
           out_NL(0);
       }


       // -- decode protocol
       if (opt->printdecode) {
          decodeSI_packet (buf,len ,opt->pid);
          out_nl (3,"==========================================================");
          out_NL (3);
       }

}





/* 
 -- decode Sections buffer by identifying the table IDs
 -- siehe EN 300 468 S.14 
*/

void decodeSI_packet (u_char *buf, int len, u_int pid)

{
  OPTION *opt;
  int    softcrc_fail;


  // nothing to output ?  
  if (getMaxVerboseLevel() < 2) return;


  if (pid != DUMMY_PID) {
	char *s;

  	out (2,"PID:  %u (0x%04x)",pid,pid);

  	s =  dvbstrPID_assignment(pid);
	if (*s) out (2,"  [= assigned for: %s]", s);
	out_NL (2);
	out_NL (2);
  }


  //
  // -- do a soft crc check
  // -- if soft crc fails, ignore packet
  //
  opt = getOptionPtr();
  softcrc_fail = 0;

  if (opt->soft_crc) {
    u_long crc = crc32 ((char *)buf,len);
    if (crc) {
	softcrc_fail = 1;
    }
  }


  if (! softcrc_fail) {

	switch (pid) {

		case  0x01D:	/* Measurement */
			section_TESTDATA  (buf, len);
			break; 

        	default:	// multiple PIDs possible
                	guess_table (buf, len, pid);
			break;

	}

  } else {
	printhex_buf (5,buf,len);
	out_nl (2, "Packet soft CRC failed, skipping packet..."); 
  }


  fflush (stdout);

}







/*
  -- content of packet can not be determined via PID,
  -- so gess from first byte of packet header
*/




typedef struct _TABLE_IF_FUNC {
    u_int    from;          /* e.g. from id 1  */
    u_int    to;            /*      to   id 3  */
    void     (*func)();     /*      function for table decoding */
} TABLE_ID_FUNC;


/*
 * -- Decode mapping table  (TableID --> decode function)
 * -- Crosscheck this with dvb_str, when changing!!!
 */

static TABLE_ID_FUNC table_id_func[] = {

     {  0x00, 0x00,  section_PAT	},
     {  0x01, 0x01,  section_CAT	},
     {  0x02, 0x02,  section_PMT	},
     {  0x03, 0x03,  section_TSDT },
// $$$ TODO     {  0x04, 0x04,  section_14496_SCT },
// $$$ TODO     {  0x05, 0x05,  section_14496_OCT },
     {  0x06, 0x06,  section_MDT },	// Metadata section
// $$$ TODO     {  0x07, 0x07,  section_IPMP_CIT },	// IPMP_Control_Information_section (defined in ISO/IEC13818-11)
     /* res. */
     {  0x3a, 0x3d,  section_DSMCC	},
     {  0x3e, 0x3e,  section_DSMCC_DATAGRAM },
     {  0x40, 0x41,  section_NIT	},
     {  0x42, 0x42,  section_SDT	},
     /* res. */
     {  0x46, 0x46,  section_SDT	},
     /* res. */
     {  0x4A, 0x4A,  section_BAT	},
     {  0x4B, 0x4B,  section_DSMCC_UNT },
     {  0x4C, 0x4C,  section_DSMCC_INT },
     {  0x4E, 0x6E,  section_EIT	},  /*  4 different types */
     {  0x70, 0x70,  section_TDT },
     {  0x71, 0x71,  section_RST },
     {  0x72, 0x72,  section_ST  },
     {  0x73, 0x73,  section_TOT },
     {  0x74, 0x74,  section_MHP_AIT },

     {  0x75, 0x75,  section_TVA_CS },		// TS 102 323
// $$$ TODO
// 0x76 related content section (TS 102 323 [36])
// 0x77 content identifier section (TS 102 323 [36])  (CIT)

     {  0x78, 0x78,  section_MPE_FEC },		// EN 301 192 v1.4.1
     {  0x79, 0x79,  section_TVA_RNT },		// TS 102 323

     /* res. */
     {  0x7E, 0x7E,  section_DIT },
     {  0x7F, 0x7F,  section_SIT },
     {  0x80, 0x8F,  section_EMM_ECM },   /* $$$ Conditional Access Message Section */

     {  0x90, 0xFE,  section_PRIVATE },	 /* opps!? DSM-CC or other stuff?! */
     {  0,0, NULL }
  };






void  guess_table (u_char *buf, int len, u_int pid)

{

  TABLE_ID_FUNC *t = table_id_func;
  u_int		table_id;



  /* -- scan id table for decode function */

  table_id =  (u_int) buf[0];
  while (t->func) {
    if (t->from <= table_id && t->to >= table_id)
       break;
    t++;
  }



  out_nl (2,"Guess table from table id...");

  if (t->func == NULL) {
   	out_SB_NL (2,"Unknown, reserved or not (yet) implemented - TableID: ",table_id);
	out_nl    (2,"--> %s",dvbstrTableID (table_id));
	printhex_buf (5,buf,len);
	return;
  }


  (*(t->func))(buf,len);		/* exec decode function */
  return;
}










