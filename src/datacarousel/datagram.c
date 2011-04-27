/*
$Id: datagram.c,v 1.21 2009/11/22 15:36:05 rhabarber1848 Exp $


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de (rasc)


 --  DATAGRAM section
 --  DSM-CC Data Carousel  EN 301 192 

*/

#include "dvbsnoop.h"
#include "datagram.h"
#include "llc_snap.h"
#include "net_ip/ip.h"
#include "strings/dvb_str.h"
#include "strings/dsmcc_str.h"
#include "misc/hexprint.h"
#include "misc/output.h"


void section_DSMCC_DATAGRAM (u_char *b, int len)
{
 /* EN 301 192 7.x */
// $$$ TODO this differs from ISO/IEC 13818-6:1998 AMD_1_2000_Cor_1_2002

 typedef struct  _DATAGRAM {
    u_int      table_id;
    u_int      section_syntax_indicator;		
    u_int      private_indicator;
    u_int      reserved_1;
    u_int      section_length;

    u_int      MAC_addr6;
    u_int      MAC_addr5;
    u_int      reserved_2;
    u_int      payload_scrambling_control;
    u_int      address_scrambling_control;
    u_int      LLC_SNAP_flag;
    
    u_int      current_next_indicator;
    u_int      section_number;
    u_int      last_section_number;

    u_int      MAC_addr4;
    u_int      MAC_addr3;	// MAC-Bits:  MSB first order
    u_int      MAC_addr2;
    u_int      MAC_addr1;

    // conditional
    // LLC SNAP   according ISO 8802-2

    // N ip datagram bytes
    u_int      ip_datagram_data_bytes;

    // conditional
    u_int      stuffing_bytes;

    // conditional
    unsigned long crc_checksum;
 } DATAGRAM;



 DATAGRAM   d;
 int        len1;


 d.table_id 			 = b[0];
 d.section_syntax_indicator	 = getBits (b, 0, 8, 1);
 d.private_indicator		 = getBits (b, 0, 9, 1);   // $$$ TODO error indicator
 d.reserved_1 			 = getBits (b, 0, 10, 2);
 d.section_length		 = getBits (b, 0, 12, 12);

 d.MAC_addr6			 = getBits (b, 0, 24, 8);
 d.MAC_addr5			 = getBits (b, 0, 32, 8);
 d.reserved_2			 = getBits (b, 0, 40, 2);
 d.payload_scrambling_control	 = getBits (b, 0, 42, 2);
 d.address_scrambling_control	 = getBits (b, 0, 44, 2);
 d.LLC_SNAP_flag		 = getBits (b, 0, 46, 1);

 d.current_next_indicator	 = getBits (b, 0, 47, 1);
 d.section_number 		 = getBits (b, 0, 48, 8);
 d.last_section_number 		 = getBits (b, 0, 56, 8);

 d.MAC_addr4			 = getBits (b, 0, 64, 8);
 d.MAC_addr3			 = getBits (b, 0, 72, 8);
 d.MAC_addr2			 = getBits (b, 0, 80, 8);
 d.MAC_addr1			 = getBits (b, 0, 88, 8);
    	// MAC-Bits:  MSB first ! 
	
 b += 12;
 len1 = d.section_length - 9;


 out_nl (3,"DSM-CC DATAGRAM-decoding....");
 out_S2B_NL (3,"Table_ID: ",d.table_id, dvbstrTableID (d.table_id));
 if (d.table_id != 0x3e) {
   out_nl (3,"wrong Table ID");
   return;
 }


 out_SB_NL (3,"section_syntax_indicator: ",d.section_syntax_indicator);
 out_SB_NL (3,"private_indicator: ",d.private_indicator);
 out_SB_NL (6,"reserved_1: ",d.reserved_1);
 out_SW_NL (5,"Section_length: ",d.section_length);

 out_SB_NL (5,"MACaddrbyte/DevicdID 6: ",d.MAC_addr6);
 out_SB_NL (5,"MACaddrbyte/DeviceID 5: ",d.MAC_addr5);
 out_SB_NL (6,"reserved_2: ",d.reserved_2);

 out_S2B_NL (3,"payload_scrambling_control: ",d.payload_scrambling_control,
		 dsmccStrPayload_scrambling_control(d.payload_scrambling_control));
 out_S2B_NL (3,"address_scrambling_control: ",d.address_scrambling_control,
		 dsmccStrAddress_scrambling_control(d.address_scrambling_control));

 out_SB_NL (3,"LLC_SNAP_flag: ",d.LLC_SNAP_flag);

 out_S2B_NL(3,"current_next_indicator: ",d.current_next_indicator, dvbstrCurrentNextIndicator(d.current_next_indicator));
 out_SB_NL (3,"Section_number: ",d.section_number);
 out_SB_NL (3,"Last_Section_number: ",d.last_section_number);

 out_SB_NL (5,"MACaddrbyte/DeviceID 4: ",d.MAC_addr4);
 out_SB_NL (5,"MACaddrbyte/DeviceID 3: ",d.MAC_addr3);
 out_SB_NL (5,"MACaddrbyte/DeviceID 2: ",d.MAC_addr2);
 out_SB    (5,"MACaddrbyte/DeviceID 1: ",d.MAC_addr1);
 out_nl    (3," => MAC-Address/DeviceID: %02x:%02x:%02x:%02x:%02x:%02x",
		 d.MAC_addr1,d.MAC_addr2,d.MAC_addr3,
		 d.MAC_addr4,d.MAC_addr5,d.MAC_addr6);


 if (d.LLC_SNAP_flag == 0x01) {
	 /*  ISO/IEC 8802-2   */
	 int k;
	 k = llc_snap (4, b);
 } else {
 	 net_IP_data (4, b, len1-4);
 }

 b += (len1 - 4);
 outBit_Sx_NL (5, (d.section_syntax_indicator)
		   ?"CRC: " :"Checksum: ",	b,0,32);
}






/*
$$$ TODO   realtime parameters in MPE

EN 301 192 v1.4.1

9.10 Real time parameters
On an elementary stream where Time Slicing and/or MPE-FEC are used, each MPE section and MPE-FEC section shall
carry real time parameters described in table 42. For the MPE sections, real time parameters are carried within the
MAC_address_4…MAC_address_1, as illustrated in figure 20.

Table 42: Time Slicing and MPE-FEC real time parameters
Syntax Number of bits Identifier
real_time_parameters () {
delta_t 12 uimsbf
table_boundary 1 bslbf
frame_boundary 1 bslbf
address 18 uimsbf
}

delta_t: Usage of this 12-bit field depends on whether Time Slicing is used on the elementary stream.
The following applies when Time Slicing is used (regardless whether MPE-FEC is used or not):
• The field indicates the time (delta-t) to the next Time Slice burst within the elementary stream. The time
information is in all MPE sections and MPE-FEC sections within a burst and the value may differ section by
section. The resolution of the delta-t is 10 ms. Value 0x00 is reserved to indicate that no more bursts will be
transmitted within the elementary stream (e.g. end of service). In such a case, all MPE sections and MPE-FEC
sections within the burst shall have the same value in this field.
EXAMPLE: delta-t value 0xC00 = 3072 indicates the time to the next burst is 30,72 s.
• Delta-t information is the time from the transport packet carrying the first byte of the current MPE section or
MPE-FEC section to the transport packet carrying the first byte of next burst. Therefore the delta-t information
may differ between MPE sections and between MPE-FEC sections within a burst.
• The time indicated by delta-t shall be beyond the end of the maximum burst duration of the actual burst. This
ensures a decoder can always reliably distinguish two sequential bursts within an elementary stream.

...


*/

