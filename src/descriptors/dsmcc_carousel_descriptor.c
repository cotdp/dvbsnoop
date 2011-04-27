/*
$Id: dsmcc_carousel_descriptor.c,v 1.26 2009/11/22 15:36:06 rhabarber1848 Exp $ 


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de (rasc)


 -- Private TAG Space  DSM-CC
 -- DSM-CC Descriptors
 -- ISO 13818-6  // TR 102 006  //  TS 102 812

*/


#include "dvbsnoop.h"
#include "descriptor.h"
#include "dsmcc_carousel_descriptor.h"
#include "dsmcc_int_unt_descriptor.h"
#include "private/userdefs.h"
#include "strings/dsmcc_str.h"
#include "misc/hexprint.h"
#include "misc/output.h"





/*
  determine descriptor type and print it...
  !!! DSMCC_CAROUSEL descriptors are in a private tag space !!!

  The userInfo field of BIOP::ModuleInfo shall be structured as a
  loop of descriptors which enables the use of Module descriptors
  as defined in DVB Data Carousels.


  return byte length
*/

int  descriptorDSMCC_CAROUSEL (u_char *b)

{
 int len;
 int tag;



  out_NL (4);
  tag = outBit_S2x_NL (4,"DSM-CC_CAROUSEL-DescriptorTag: ",	b,   0,  8,
		(char *(*)(u_long))dsmccStrDSMCC_CAROUSEL_DescriptorTAG); 
  len = outBit_Sx_NL  (4,"descriptor_length: ",	 		b,   8,  8);


  // empty ??
  if (len == 0) return len;

  // print hex buf of descriptor
  printhex_buf (9, b,len+2);



  switch (tag) {

     case 0x01:  descriptorDSMCC_type (b); break;
     case 0x02:  descriptorDSMCC_name (b); break;
     case 0x03:  descriptorDSMCC_info (b); break;
     case 0x04:  descriptorDSMCC_module_link (b); break;
     case 0x05:  descriptorDSMCC_crc32 (b); break;
     case 0x06:  descriptorDSMCC_location (b); break;
     case 0x07:  descriptorDSMCC_est_download_time (b); break;
     case 0x08:  descriptorDSMCC_group_link (b); break;
     case 0x09:  descriptorDSMCC_compressed_module (b); break;
     case 0x0A:  descriptorDSMCC_subgroup_association (b); break;

	// MHP
     case 0x70:  descriptorDSMCC_MHP_label (b); break;
     case 0x71:  descriptorDSMCC_MHP_caching_priority (b); break;
     case 0x72:  descriptorDSMCC_MHP_content_type (b); break;

     default: 
	if (tag < 0x80) {
	    out_nl (0,"  ----> ERROR: unimplemented descriptor (DSM-CC_CAROUSEL context), Report!");
	}
	descriptor_PRIVATE (b,DSMCC_CAROUSEL);
	break;
  } 


  return len+2;   // (descriptor total length)
}








/* 
 * EN 301 192  / TR 102 006
 * private DSM-CC CAROUSEL descriptors
 *
 * 0x00 - 0x0A currently allocated by DVB
 * 0x0B - 0x6F reserved for future use by DVB
 * 0x70 - 0x7F reserved for DVB MHP
 * 0x80 - 0xFF private descriptors 
 *
 * e.g.:
 * The userInfo field of BIOP::ModuleInfo shall be structured as a
 * loop of descriptors which enables the use of Module descriptors
 * as defined in DVB Data Carousels.
 */





/*
  0x01 - type
  ETSI EN 301 192  (ISO 13818-6)
*/

void descriptorDSMCC_type (u_char *b)
{
  int        len;

  // descriptor_tag	= b[0];
  len		        = b[1];

  print_std_ascii (4, "Text: ", b+2, len);
}




/*
  0x02 - name
  ETSI EN 301 192  (ISO 13818-6)
*/

void descriptorDSMCC_name (u_char *b)
{
  int        len;

  // descriptor_tag	= b[0];
  len		        = b[1];

  print_text_468A (4, "Text: ", b+2, len);
}



/*
  0x03 - info
  ETSI EN 301 192  (ISO 13818-6)
*/

void descriptorDSMCC_info (u_char *b)
{
  int        len;
  u_char     ISO639_language_code[4];


  // descriptor_tag	= b[0];
  len		        = b[1];

  getISO639_3 (ISO639_language_code, b+2);
  out_nl (4,"  ISO639_language_code:  %3.3s", ISO639_language_code);

  print_text_468A (4, "Text: ", b+5, len-3);
}


/*
  0x04 - module_link
  ETSI EN 301 192  (ISO 13818-6)
*/

void descriptorDSMCC_module_link (u_char *b)
{

  // descriptor_tag	= b[0];
  // len	        = b[1];
 
  outBit_S2x_NL(4,"position: ",  b,16, 8,
			(char *(*)(u_long)) dsmccStr_GroupModuleLinkPosition);
  outBit_Sx_NL (4,"module_id: ", b,24,16);
}




/*
  0x05 - crc
  ETSI EN 301 192  (ISO 13818-6)
*/

void descriptorDSMCC_crc32 (u_char *b)
{

  // descriptor_tag	= b[0];
  // len	        = b[1];
 
  outBit_Sx_NL (4,"CRC: ", b,16,32);
}



/*
  0x06 - location
  ETSI EN 301 192  (ISO 13818-6)
*/

void descriptorDSMCC_location (u_char *b)
{

  // descriptor_tag	= b[0];
  // len	        = b[1];
 
  outBit_S2Tx_NL (4,"location: ", b,16, 8,
	   "--> refers to component_tag in stream_identifier_descriptor"); 
}


/*
  0x07 - est_download_time
  ETSI EN 301 192  (ISO 13818-6)
*/

void descriptorDSMCC_est_download_time (u_char *b)
{

  // descriptor_tag	= b[0];
  // len	        = b[1];
 
  outBit_S2Tx_NL (4,"est_download_time: ", b,16, 32, "(seconds)");
}




/*
  0x08 - group link
  ETSI EN 301 192  (ISO 13818-6)
*/

void descriptorDSMCC_group_link (u_char *b)
{

  // descriptor_tag	= b[0];
  // len	        = b[1];
 
  outBit_S2x_NL(4,"position: ",  b,16, 8,
			(char *(*)(u_long)) dsmccStr_GroupModuleLinkPosition);
  outBit_Sx_NL (4,"group_id: ", b,24,32);
}



/*
  0x09 -  compressed_module
  ETSI EN 301 192  (ISO 13818-6)
*/

void descriptorDSMCC_compressed_module (u_char *b)
{

  // descriptor_tag	= b[0];
  // len	        = b[1];

  outBit_S2x_NL(4,"compression_method: ",  b,16, 8,
			(char *(*)(u_long)) dsmccStr_compression_method);
  outBit_S2Tx_NL (4,"original_size: ", b,24,32, "(bytes)");

  // Module data stored in the following structure: 
  // zlib structure(){
  //	compression_method 1
  //	flags_check 1
  //	compressed_data n
  // 	check value 4
  // }

}




/*
  0x0A - subgroup_association
  ETSI EN 301 192  (ISO 13818-6)
*/

void descriptorDSMCC_subgroup_association (u_char *b)
{
 descriptorDSMCC_ssu_subgroup_association (b);
}












/*
  0x70 -  MHP label descriptor
  ETSI  TS 102 812  v 1.2.1
*/

void descriptorDSMCC_MHP_label (u_char *b)
{
  int len;

  // tag	= b[0];
  len	        = b[1];

  print_text_UTF8 (4, "label: ", b+2, len);
}



/*
  0x71 -  MHP caching priority descriptor
  ETSI  TS 102 812  v 1.2.1
*/

void descriptorDSMCC_MHP_caching_priority (u_char *b)
{

  // tag	= b[0];
  // len        = b[1];

  outBit_Sx_NL (4,"priority_value: ", 		b, 16, 8);
  outBit_S2x_NL(4,"transparency_level: ",	b, 24, 8,
			(char *(*)(u_long)) dsmccStrMHP_caching_transparency_level);
}




/*
  0x72 -  MHP content type descriptor
  ETSI  TS 102 812  v 1.2.1
*/

void descriptorDSMCC_MHP_content_type (u_char *b)
{
  int  len;

  // tag	= b[0];
  len        = b[1];

  print_text_UTF8 (4, "content_type_data: ", b+2, len);
}






