/*
$Id: dsmcc_str.c,v 1.40 2009/11/22 15:36:31 rhabarber1848 Exp $


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de


 -- DSM-CC -Strings

*/

#include "dvbsnoop.h"
#include "dsmcc_str.h"
#include "strtable_misc.h"

/*
  -- DSM-CC CAROUSEL Descriptors
  -- Private Tag Space  (DII, DSI)
  -- see  EN 301 192 
  -- ... shows  in DVB-descriptor lower ranges
 */

char *dsmccStrDSMCC_CAROUSEL_DescriptorTAG (u_int i)
{
  STR_TABLE  Table[] = {
     {  0x00, 0x00,  "reserved" },
     {  0x01, 0x01,  "type_descriptor" },
     {  0x02, 0x02,  "name_descriptor" },
     {  0x03, 0x03,  "info_descriptor" },
     {  0x04, 0x04,  "module_link_descriptor" },
     {  0x05, 0x05,  "CRC32_descriptor" },
     {  0x06, 0x06,  "location_descriptor" },
     {  0x07, 0x07,  "estimated_download_time_descriptor" },
     {  0x08, 0x08,  "group_link_descriptor" },
     {  0x09, 0x09,  "compressed_module_descriptor" },
     {  0x0A, 0x0A,  "subgroup_association_descriptor" },
     {  0x0B, 0x6F,  "reserved for future use by DVB" },
     {  0x70, 0x70,  "label_descriptor" },		// MHP
     {  0x71, 0x71,  "caching_priority_descriptor" },	// MHP
     {  0x72, 0x7F,  "reserved MHP" },
     {  0x80, 0xFF,  "private_descriptor" },
     {  0,0, NULL }
  };

  return findTableID (Table, i);
}




/*
  -- DSM-CC  INT (UNT, SSU-UNT) Descriptors
  -- Private INT, UNT, SSU-UNT Tag Space
  -- see  EN 301 192 // TS 102 006
 */

char *dsmccStrDSMCC_INT_UNT_DescriptorTAG (u_int i)
{
  STR_TABLE  Table[] = {
     {  0x00, 0x00,  "reserved" },
     {  0x01, 0x01,  "scheduling_descriptor" },
     {  0x02, 0x02,  "update_descriptor" },
     {  0x03, 0x03,  "ssu_location_descriptor" },
     {  0x04, 0x04,  "message_descriptor" },
     {  0x05, 0x05,  "ssu_event_name_descriptor" },
     {  0x06, 0x06,  "target_smartcard_descriptor" },
     {  0x07, 0x07,  "target_MAC_address_descriptor" },
     {  0x08, 0x08,  "target_serial_number_descriptor" },
     {  0x09, 0x09,  "target_IP_address_descriptor" },
     {  0x0A, 0x0A,  "target_IPv6_address_descriptor" },
     {  0x0B, 0x0B,  "ssu_subgroup_association_descriptor" },
     {  0x0C, 0x0C,  "IP/MAC_platform_name_descriptor" },
     {  0x0D, 0x0D,  "IP/MAC_platform_provider_name_descriptor" },
     {  0x0E, 0x0E,  "target_MAC_address_range_descriptor" },
     {  0x0F, 0x0F,  "target_IP_slash_descriptor" },
     {  0x10, 0x10,  "target_IP_source_slash_descriptor" },
     {  0x11, 0x11,  "target_IPv6_slash_descriptor" },
     {  0x12, 0x12,  "target_IPv6_source_slash_descriptor" },
     {  0x13, 0x13,  "IP/MAC_stream_location_descriptor" },
     {  0x14, 0x14,  "ISP_access_mode_descriptor" },
     {  0x15, 0x3F,  "reserved" },
//   {  0x40, 0x7F,  "DVB-SI scope" },  Telphone, private_data_spec, use: dvb scope
     {  0x80, 0xFE,  "user_private_descriptor" },
     {  0xFF, 0xFF,  "reserved" },
     {  0,0, NULL }
  };

  return findTableID (Table, i);
}




/*
  -- MHP  AIT Descriptors
  -- Private Tag Space  (AIT)
  -- see   TS 102 812
 */

char *dsmccStrMHP_AIT_DescriptorTAG (u_int i)
{
  STR_TABLE  Table[] = {
     {  0x00, 0x00,  "Application descriptor" },
     {  0x01, 0x01,  "Application name descriptor" },
     {  0x02, 0x02,  "Transport protocol descriptor" },
     {  0x03, 0x03,  "DVB-J application descriptor" },
     {  0x04, 0x04,  "DVB-J application location descriptor" },
     {  0x05, 0x05,  "External application authorisation descriptor" },
     {  0x06, 0x06,  "Routing Descriptor IPv4" },
     {  0x07, 0x07,  "Routing Descriptor IPv6" },
     {  0x08, 0x08,  "DVB-HTML application descriptor" },
     {  0x09, 0x09,  "DVB-HTML application location descriptor" },
     {  0x0A, 0x0A,  "DVB-HTML application boundary descriptor" },
     {  0x0B, 0x0B,  "Application icons descriptor" },
     {  0x0C, 0x0C,  "Pre-fetch descriptor" },
     {  0x0D, 0x0D,  "DII location descriptor" },
     {  0x0E, 0x0E,  "delegated application descriptor" },
     {  0x0F, 0x0F,  "Plug-in descriptor" },
     {  0x10, 0x10,  "Application storage descriptor" },
     {  0x15, 0x15,  "Simple application location descriptor" },     
     {  0x11, 0x5E,  "reserved to MHP" },
     {  0x5F, 0x5F,  "private data specifier descriptor" },
#include "identifiers/mhpAITDescriptors.h"
  };

  return findTableID (Table, i);
}








/*
  --  MHP Organisations
*/

char *dsmccStrMHPOrg (u_int id)

{
  STR_TABLE  TableIDs[] = {
	// --{ MHP Organisation ID, MHP Organisation ID,   "Organisation Supplying MHP Applications" },
	#include "identifiers/mhpOrganisationID.h"
  };


  return findTableID (TableIDs, id);
}




/*
  --  Action Type (Linkage) EN 301 192 7.6.x
  --  ETSI TS 102006  $$$ TODO (is there a conflict?)
*/

char *dsmccStrAction_Type (u_int id)

{
  STR_TABLE  TableIDs[] = {
	{ 0x00, 0x00,   "reserved" },
	{ 0x01, 0x01,   "location of IP/MAC streams in DVB networks // System Software Update" },
	{ 0x02, 0xff,   "reserved" },
      {  0,0, NULL }
  };


  return findTableID (TableIDs, id);
}



/*
  --  Processing Order (INT)   EN 301 192
*/

char *dsmccStrProcessing_order (u_int id)

{
  STR_TABLE  TableIDs[] = {
	{ 0x00, 0x00,   "first action" },
	{ 0x01, 0xfe,   "subsequent actions (ascending)" },
	{ 0xff, 0xff,   "no ordering implied" },
      {  0,0, NULL }
  };


  return findTableID (TableIDs, id);
}



/*
  --  Payload scrambling control (INT)   EN 301 192
  --  Address scrambling control (INT)   EN 301 192
*/

// $$$ TODO  according to mpeg/ scrambling control?

char *dsmccStrPayload_scrambling_control (u_int id)

{
  STR_TABLE  TableIDs[] = {
	{ 0x00, 0x00,   "unscrambled" },
	{ 0x01, 0x03,   "defined by service" },
      {  0,0, NULL }
  };


  return findTableID (TableIDs, id);
}


char *dsmccStrAddress_scrambling_control (u_int id)

{
  STR_TABLE  TableIDs[] = {
	{ 0x00, 0x00,   "unscrambled" },
	{ 0x01, 0x03,   "defined by service" },
      {  0,0, NULL }
  };


  return findTableID (TableIDs, id);
}




/*
 * -- LinkageDescriptor0x0C Table_type  EN301192
 *
 */

char *dsmccStrLinkage0CTable_TYPE (u_int i)

{
  STR_TABLE  Table[] = {
     {  0x00, 0x00,  "not defined" },
     {  0x01, 0x01,  "NIT" },
     {  0x02, 0x02,  "BAT" },
     {  0x03, 0xFF,  "reserved" },
     {  0,0, NULL }
  };

  return findTableID (Table, i);
}





/*
 * -- MultiProtocolEncapsulationMACAddressRangeField
 * -- EN 301 192
 */

char *dsmccStrMultiProtEncapsMACAddrRangeField (u_int i)

{
  STR_TABLE  Table[] = {
     {  0x00, 0x00,  "reserved" },
     {  0x01, 0x01,  "6" },
     {  0x02, 0x02,  "6,5" },
     {  0x03, 0x03,  "6,5,4" },
     {  0x04, 0x04,  "6,5,4,3" },
     {  0x05, 0x05,  "6,5,4,3,2" },
     {  0x06, 0x06,  "6,5,4,3,2,1" },
     {  0x07, 0x07,  "reserved" },
     {  0,0, NULL }
  };

  return findTableID (Table, i);
}







/*
  --  Platform ID    ETR 162
*/

char *dsmccStrPlatform_ID (u_int id)

{
  STR_TABLE  TableIDs[] = {
	  /* $$$ TODO   Platform ID ETR 162 ... */
      {  0,0, NULL }
  };


  return findTableID (TableIDs, id);
}




/*
  --  Carousel Type ID    EN 301 192
*/

char *dsmccStrCarouselType_ID (u_int id)

{
  STR_TABLE  TableIDs[] = {
	{ 0x00, 0x00,   "reserved" },
	{ 0x01, 0x01,   "one layer carousel" },
	{ 0x02, 0x02,   "two layer carousel" },
	{ 0x03, 0x03,   "reserved" },
      	{  0,0, NULL }
  };


  return findTableID (TableIDs, id);
}




/*
  --  Higher Protocol ID    EN 301 192
*/

char *dsmccStrHigherProtocol_ID (u_int id)

{
  STR_TABLE  TableIDs[] = {
	{ 0x00, 0x00,   "reserved" },
	{ 0x01, 0x01,   "dGNSS data" },
	{ 0x02, 0x02,   "TPEG" },
	{ 0x03, 0x0F,   "reserved" },
      	{  0,0, NULL }
  };


  return findTableID (TableIDs, id);
}



/*
  --  Update Type Table    TR 102 006
*/

char *dsmccStrUpdateType_ID (u_int id)

{
  STR_TABLE  TableIDs[] = {
	{ 0x00, 0x00,   "proprietary update solution" },
	{ 0x01, 0x01,   "standard update carousel via broadcast" },
	{ 0x02, 0x02,   "system software update with notification table (UNT) via broadcast" },
	{ 0x03, 0x03,   "system software update using return channel with UNT" },
	{ 0x04, 0x0F,   "reserved" },
      	{  0,0, NULL }
  };


  return findTableID (TableIDs, id);
}







/*
  --  Command_ID
  --  also  dsmcc_discriminator
  --  e.g. from ITU H.222.0 Annex B
  --  
*/

char *dsmccStr_Command_ID  (u_int id)

{
  STR_TABLE  TableIDs[] = {
	{ 0x00, 0x00,   "forbidden" },
	{ 0x01, 0x01,   "control" },
	{ 0x02, 0x02,   "Acknownledge" },
	{ 0x03, 0x7F,   "reserved" },
	{ 0x80, 0x80,   "DSMCC_program_stream_descriptor_list" },
	{ 0x81, 0xFF,   "reserved" },
      	{  0,0, NULL }
  };

  return findTableID (TableIDs, id);
}



/*
  --  Command_ID
  --  e.g. from ITU H.222.0 Annex B
  --  
*/

char *dsmccStr_SelectMode_ID  (u_int id)

{
  STR_TABLE  TableIDs[] = {
	{ 0x00, 0x00,   "forbidden" },
	{ 0x01, 0x01,   "storage" },
	{ 0x02, 0x02,   "retrieval" },
	{ 0x03, 0x1F,   "reserved" },
      	{  0,0, NULL }
  };

  return findTableID (TableIDs, id);
}



/*
  --  direction_indicator
  --  e.g. from ITU H.222.0 Annex B
  --  
*/

char *dsmccStr_DirectionIndicator (u_int id)

{
  STR_TABLE  TableIDs[] = {
	{ 0x00, 0x00,   "Forward" },
	{ 0x01, 0x01,   "Backward" },
      	{  0,0, NULL }
  };

  return findTableID (TableIDs, id);
}



/*
  -- DSM-CC (UNT) (Compatibility) Descriptor type 
  --  e.g. from ISO 13818-6 // TS 102006
  --  
*/

char *dsmccStr_DescriptorType (u_int id)

{
  STR_TABLE  TableIDs[] = {
	{ 0x00, 0x00,   "Pad descriptor" },
	{ 0x01, 0x01,   "System Hardware descriptor" },
	{ 0x02, 0x02,   "System Software descriptor" },
	{ 0x03, 0x3F,   "ISO/IEC 13818-6 reserved" },
	{ 0x40, 0x7F,   "DVB reserved" },
	{ 0x80, 0xFF,   "User defined" },
      	{  0,0, NULL }
  };

  return findTableID (TableIDs, id);
}




/*
  -- DSM-CC (UNT) Specifier type 
  --  e.g. from ISO 13818-6 // TS 102006
  --  
*/

char *dsmccStr_SpecifierType (u_int id)
{
  STR_TABLE  TableIDs[] = {
	{ 0x00, 0x00,   "ISO/IEC 13818-6 reserved" },
	{ 0x01, 0x01,   "IEEE OUI" },
	{ 0x02, 0xFF,   "ISO/IEC 13818-6 reserved" },
      	{  0,0, NULL }
  };

  return findTableID (TableIDs, id);
}




/*
  -- DSM-CC (INT) AccessMode
  --  e.g. from ISO 13818-6 // EN 301 192
  --  
*/

char *dsmccStr_AccessMode (u_int id)

{
  STR_TABLE  TableIDs[] = {
	{ 0x00, 0x00,   "not used" },
	{ 0x01, 0x01,   "dialup" },
	{ 0x02, 0xFF,   "reserved" },
      	{  0,0, NULL }
  };

  return findTableID (TableIDs, id);
}




/*
  -- DSM-CC (INT) Update_flag
  --  e.g. from ISO 13818-6 // TS 102 006
  --  
*/

char *dsmccStr_UpdateFlag (u_int id)

{
  STR_TABLE  TableIDs[] = {
	{ 0x00, 0x00,   "to be activated manually" },
	{ 0x01, 0x01,   "may be performed automatically" },
	{ 0x02, 0x03,   "reserved" },
      	{  0,0, NULL }
  };

  return findTableID (TableIDs, id);
}



/*
  -- DSM-CC (INT) Update_method
  --  e.g. from ISO 13818-6 // TS 102 006
  --  
*/

char *dsmccStr_UpdateMethod (u_int id)

{
  STR_TABLE  TableIDs[] = {
	{ 0x00, 0x00,   "immediate update: performed whatever the IRD state" },
	{ 0x01, 0x01,   "IRD available: the update is available in the stream; it will be taken into account when it does not interfere with the normal user operation" },
	{ 0x02, 0x02,   "next restart: the update is available in the stream; it will be taken into account at the next IRD restart" },
	{ 0x03, 0x07,   "reserved" },
	{ 0x08, 0x0E,   "private use" },
	{ 0x0F, 0x0F,   "reserved" },
      	{  0,0, NULL }
  };

  return findTableID (TableIDs, id);
}



/*
  -- DSM-CC (INT) Time Units
  --  e.g. from ISO 13818-6 // TS 102 006
  --  
*/

char *dsmccStr_TimeUnits (u_int id)

{
  STR_TABLE  TableIDs[] = {
	{ 0x00, 0x00,   "second" },
	{ 0x01, 0x01,   "minute" },
	{ 0x02, 0x02,   "hour" },
	{ 0x03, 0x03,   "day" },
      	{  0,0, NULL }
  };

  return findTableID (TableIDs, id);
}



/*
  -- DSM-CC  Module Link Position
  --  e.g. from ISO 13818-6 // EN 301 192
  --  
*/

char *dsmccStr_GroupModuleLinkPosition (u_int id)

{
  STR_TABLE  TableIDs[] = {
	{ 0x00, 0x00,   "first in list" },
	{ 0x01, 0x01,   "intermediate in list" },
	{ 0x02, 0x02,   "last in list" },
      	{  0,0, NULL }
  };

  return findTableID (TableIDs, id);
}


/*
  -- DSM-CC  compression_method
  --  e.g. from ISO 13818-6 // EN 301 192
  --  
*/

char *dsmccStr_compression_method (u_int id)

{
    return (char *) "compression method used, see: RFC 1950";
}




/*
  -- DSM-CC  Stream Mode
  --  ISO 13818-6  (stream desc. 8.5)
  --  
*/

char *dsmccStr_streamMode (u_int id)
{
  STR_TABLE  TableIDs[] = {
	{ 0x00, 0x00,   "Open" },
	{ 0x01, 0x01,   "Pause" },
	{ 0x02, 0x02,   "Transport" },
	{ 0x03, 0x03,   "Transport Pause" },
	{ 0x04, 0x04,   "Search Transport" },
	{ 0x05, 0x05,   "Search Transport Pause" },
	{ 0x06, 0x06,   "Pause Search Transport" },
	{ 0x07, 0x07,   "End of Stream" },
	{ 0x08, 0x08,   "Pre Search Transport" },
	{ 0x09, 0x09,   "Pre Search Transport Pause" },
	{ 0x0A, 0xFF,   "ISO/IEC 13818-6 reserved" },
      	{  0,0, NULL }
  };

  return findTableID (TableIDs, id);
}





/*
  -- DSM-CC  postDiscontinuityIndicator
  --  ISO 13818-6  (stream desc. 8.5)
  --  
*/

char *dsmccStr_postDiscontinuityIndicator (u_int id)
{
  STR_TABLE  TableIDs[] = {
	{ 0x00, 0x00,   "now valid" },
	{ 0x01, 0x01,   "valid at the next system time base discontinuity" },
      	{  0,0, NULL }
  };

  return findTableID (TableIDs, id);
}




/*
  --  OUI  Table    (e.g.: LLC-SNAP  IEEE 802)
  --  real table is very large!!
  --  see: http://standards.ieee.org/regauth/oui/index.shtml
*/

char *dsmccStrOUI  (u_int id)
{
  STR_TABLE  TableIDs[] = {
	{ 0x000000, 0x000000,   "EtherType or routed non-OSI protocol" },
	{ 0x000979, 0x000979,   "ATSC" },  // ATSC a_95
	{ 0x0080c2, 0x0080c2,   "Bridged protocol" },
	{ 0x000000, 0xFFFFFF,  	"http://standards.ieee.org/regauth/oui/" },
      	{  0,0, NULL }
  };

	// http://standards.ieee.org/cgi-bin/ouisearch?hex-id
  return findTableID (TableIDs, id);
}




/*
  -- DSM-CC  LLC SNAP protocol 
*/

char *dsmccStr_LLC_SNAP_prot (u_int id)
{
  STR_TABLE  TableIDs[] = {
	{ 0x0800, 0x0800,   "IP protocol" },
      	{  0,0, NULL }
  };

  return findTableID (TableIDs, id);
}










/*
  -- MHP application type
*/

char *dsmccStrMHP_application_type (u_int id)
{
  STR_TABLE  TableIDs[] = {
	#include "identifiers/mhpApplicationTypeID.h"
  };

  return findTableID (TableIDs, id);
}




/*
  -- MHP application id
*/

char *dsmccStrMHP_application_id (u_int id)
{
  STR_TABLE  TableIDs[] = {
	{ 0x0000, 0x3FFF,   "unsigned applications" },
	{ 0x4000, 0x7FFF,   "signed applications" },
	{ 0x8000, 0xFFFD,   "reserved" },
	{ 0xFFFE, 0xFFFE,   "wildcard value for signed applications of an org." },
	{ 0xFFFF, 0xFFFF,   "wildcard value all applications of an org." },
      	{  0,0, NULL }
  };

  return findTableID (TableIDs, id);
}




/*
  -- MHP application control code
*/

char *dsmccStrMHP_application_control_code (u_int id)
{
  STR_TABLE  TableIDs[] = {
	{ 0x00, 0x00,   "reserved" },
	{ 0x01, 0x01,   "AUTOSTART" },
	{ 0x02, 0x02,   "PRESENT" },
	{ 0x03, 0x03,   "DESTROY" },
	{ 0x04, 0x04,   "KILL" },
	{ 0x05, 0x05,   "PREFETCH" },
	{ 0x06, 0x06,   "REMOTE" },
	{ 0x07, 0xFF,   "reserved" },
      	{  0,0, NULL }
  };

  return findTableID (TableIDs, id);
}




/*
  -- MHP visibility state
*/

char *dsmccStrMHP_visibility_state (u_int id)
{
  STR_TABLE  TableIDs[] = {
	{ 0x00, 0x00,   "application not visible to user and appl. listening api" },
	{ 0x01, 0x01,   "application not visible to user, but visible to appl. listening api" },
	{ 0x02, 0x02,   "reserved" },
	{ 0x03, 0x03,   "application visible to user and appl. listening api" },
      	{  0,0, NULL }
  };

  return findTableID (TableIDs, id);
}




/*
  -- MHP protocol_id  
  -- ETR162
*/

char *dsmccStrMHP_protocol_id (u_int id)
{
  STR_TABLE  TableIDs[] = {
	#include "identifiers/mhpProtocolID.h"
  };

  return findTableID (TableIDs, id);
}




/*
  -- MHP storage property
  -- ETR162
*/

char *dsmccStrMHP_storage_property (u_int id)
{
  STR_TABLE  TableIDs[] = {
	{ 0x00, 0x00,   "broadcast related" },
	{ 0x01, 0x01,   "stand alone" },
	{ 0x02, 0xFF,   "reserved" },
      	{  0,0, NULL }
  };

  return findTableID (TableIDs, id);
}





/*
  -- DSM-CC  MHP caching transparency level
  -- ISO/IEC 13816-6
  -- TS 102 812  v1.2.1 B.2.7
*/

char *dsmccStrMHP_caching_transparency_level (u_int id)
{
  STR_TABLE  TableIDs[] = {
	{ 0x00, 0x00,   "reserved" },
	{ 0x01, 0x01,   "transparent caching" },
	{ 0x02, 0x02,   "semi-transparent caching" },
	{ 0x03, 0x03,   "static caching" },
	{ 0x04, 0xFF,   "reserved" },
      	{  0,0, NULL }
  };

  return findTableID (TableIDs, id);
}








/*
  -- DSM-CC Adaptation Type
  -- ISO/IEC 13816-6
*/

char *dsmccStr_adaptationType (u_int id)
{
  STR_TABLE  TableIDs[] = {
	{ 0x00, 0x00,   "reserved" },
	{ 0x01, 0x01,   "DSM-CC Conditional Access adaptation format" },
	{ 0x02, 0x02,   "DSM-CC User ID adaptation format" },
	{ 0x03, 0x7F,   "reserved" },
	{ 0x80, 0xFF,   "user defined" },
      	{  0,0, NULL }
  };

  return findTableID (TableIDs, id);
}




/*
  -- DSM-CC dsmcc Type
  -- ISO/IEC 13816-6
*/

char *dsmccStr_dsmccType (u_int id)
{
  STR_TABLE  TableIDs[] = {
	{ 0x00, 0x00,   "reserved" },
	{ 0x01, 0x01,   "User-to-Network configuration message" },
	{ 0x02, 0x02,   "User-to-Network session message" },
	{ 0x03, 0x03,   "Download message" },
	{ 0x04, 0x04,   "SDB Channel Change Protocol message" },
	{ 0x05, 0x05,   "User-to- Network pass-thru message" },
	{ 0x06, 0x7F,   "reserved" },
	{ 0x80, 0xFF,   "user defined" },
      	{  0,0, NULL }
  };

  return findTableID (TableIDs, id);
}



/*
  -- DSM-CC Download Message ID
  -- ISO/IEC 13816-6
*/

char *dsmccStr_messageID (u_int id)
{
  STR_TABLE  TableIDs[] = {
	{ 0x1001, 0x1001,   "DownloadInfoRequest" },
	{ 0x1002, 0x1002,   "DownloadInfoIndication (DII)" }, // also: DownloadInfoResponse
	{ 0x1003, 0x1003,   "DownloadDataBlock (DDB)" },
	{ 0x1004, 0x1004,   "DownloadDataRequest" },
	{ 0x1005, 0x1005,   "DownloadCancel" },
	{ 0x1006, 0x1006,   "DownloadServerInitiate (DSI)" },
      	{  0,0, NULL }
  };

  return findTableID (TableIDs, id);
}




/*
  -- DSM-CC TransactionID originator
  -- ISO/IEC 13816-6
  -- TS 102 812  v1.2.1 B.2.7
*/

char *dsmccStr_transactionID_originator (u_int id)
{
  STR_TABLE  TableIDs[] = {
	{ 0x00, 0x00,   "assigned by the client" },
	{ 0x01, 0x01,   "assigned by the server" },
	{ 0x02, 0x02,   "assigned by the network" },
	{ 0x03, 0x03,   "reserved" },
      	{  0,0, NULL }
  };

  return findTableID (TableIDs, id);
}





/*
  -- DSM-CC  IOP ProfileID
  -- ISO/IEC 13816-6
  -- Profile Tags 0x49534F00 - 0x49534F0F (the first 3 octets spell ISO)
  -- TR 101 202 
  -- TS 102 812
*/

char *dsmccStrIOP_ProfileID (u_int id)
{
  STR_TABLE  TableIDs[] = {
	{ 0x49534f00, 0x49534f00,   "TAG_MIN" },
	{ 0x49534f01, 0x49534f01,   "TAG_CHILD" },
	{ 0x49534f02, 0x49534f02,   "TAG_OPTIONS" },
	{ 0x49534f03, 0x49534f03,   "TAG_LITE_MIN" },
	{ 0x49534f04, 0x49534f04,   "TAG_LITE_CHILD" },
	{ 0x49534f05, 0x49534f05,   "TAG_LITE_OPTIONS" },
	{ 0x49534f06, 0x49534f06,   "TAG_BIOP" },
	{ 0x49534f07, 0x49534f07,   "TAG_ONC" },
	{ 0x49534f40, 0x49534f40,   "TAG_ConnBinder" },
	{ 0x49534f41, 0x49534f41,   "TAG_IIOPAddr" },
	{ 0x49534f42, 0x49534f42,   "TAG_Addr" },
	{ 0x49534f43, 0x49534f43,   "TAG_NameId" },
	{ 0x49534f44, 0x49534f44,   "TAG_IntfCode" },
	{ 0x49534f45, 0x49534f45,   "TAG_ObjectKey" },
	{ 0x49534f46, 0x49534f46,   "TAG_ServiceLocation" },
	{ 0x49534f50, 0x49534f50,   "TAG_ObjectLocation" },
	{ 0x49534f58, 0x49534f58,   "TAG_Intf" },
      	{  0,0, NULL }
  };

  return findTableID (TableIDs, id);
}




/*
  -- DSM-CC  BIOP tap use
  -- ISO/IEC 13816-6
*/

char *dsmccStrBIOP_TAP_Use (u_int id)
{
  STR_TABLE  TableIDs[] = {
	{ 0x0000, 0x0000,   "UNKNOWN" },
	{ 0x0001, 0x0001,   "MPEG_TS_UP_USE" },
	{ 0x0002, 0x0002,   "MPEG_TS_DOWN_USE" },
	{ 0x0003, 0x0003,   "MPEG_ES_UP_USE" },
	{ 0x0004, 0x0004,   "MPEG_ES_DOWN_USE" },
	{ 0x0005, 0x0005,   "DOWNLOAD_CTRL_USE" },
	{ 0x0006, 0x0006,   "DOWNLOAD_CTRL_UP_USE" },
	{ 0x0007, 0x0007,   "DOWNLOAD_CTRL_DOWN_USE" },
	{ 0x0008, 0x0008,   "DOWNLOAD_DATA_USE" },
	{ 0x0009, 0x0009,   "DOWNLOAD_DATA_UP_USE" },
	{ 0x000A, 0x000A,   "DOWNLOAD_DATA_DOWN_USE" },
	{ 0x000B, 0x000B,   "STR_NPT_USE" },
	{ 0x000C, 0x000C,   "STR_STATUS_AND_EVENT_USE" },
	{ 0x000D, 0x000D,   "STR_EVENT_USE" },
	{ 0x000E, 0x000E,   "STR_STATUS_USE" },
	{ 0x000F, 0x000F,   "RPC_USE" },
	{ 0x0010, 0x0010,   "IP_USE" },
	{ 0x0011, 0x0011,   "SDB_CTRL_USE" },
	{ 0x0012, 0x0015,   "T120_TAP reserved" },
	{ 0x0016, 0x0016,   "BIOP_DELIVERY_PARA_USE" },
	{ 0x0017, 0x0017,   "BIOP_OBJECT_USE" },
	{ 0x0018, 0x0018,   "BIOP_ES_USE" },
	{ 0x0019, 0x0019,   "BIOP_PROGRAM_USE" },
	{ 0x001A, 0x001A,   "BIOP_DNL_CTRL_USE" },
      	{  0,0, NULL }
  };

  return findTableID (TableIDs, id);
}






/*
  -- BIOP/DSM::TAP  selector_type (MessageSelector)
  -- ISO/IEC 13816-6
  -- ATSC A95, A47
*/

char *dsmccStrBIOP_TAP_SelectorType (u_int id)
{
  STR_TABLE  TableIDs[] = {
	{ 0x0000, 0x0000,   "ISO/IEC reserved" },
	{ 0x0001, 0x0001,   "MessageSelector" },
	{ 0x0109, 0x0109,   "TSFS_Selector" },
      	{  0,0, NULL }
  };

  return findTableID (TableIDs, id);
}



/*
  -- BIOP/DSM::TAP  selector_type (MessageSelector)
  -- ISO/IEC 13816-6
  -- ATSC A95, A47
*/

char *dsmccStrBIOP_EndianType (u_int id)
{
  STR_TABLE  TableIDs[] = {
	{ 0x00, 0x00,   "Big Endian" },
	{ 0x01, 0xFF,   "Little Endian" },
      	{  0,0, NULL }
  };

  return findTableID (TableIDs, id);
}




/*
  -- BIOP   ObjectKind  / TypeID Aliases
  -- ISO/IEC 13816-6
*/

char *dsmccStrBIOP_TypeID_Alias (u_int id)
{
  STR_TABLE  TableIDs[] = {
	{ 0x64697200, 0x64697200,   "dir (DSM::Directory)" },
	{ 0x66696c00, 0x66696c00,   "fil (DSM::File)" },
	{ 0x73726700, 0x73726700,   "srg (DSM::ServiceGateway)" },
	{ 0x73746500, 0x73746500,   "ste (DSM::StreamEvent)" },
	{ 0x73747200, 0x73747200,   "str (BIOP::Stream)" },
      	{  0,0, NULL }
  };

  return findTableID (TableIDs, id);
}





/*
  -- BIOP   BindingType 
  -- e.g. TS 102 812
*/

char *dsmccStrBIOP_BindingType (u_int id)
{
  STR_TABLE  TableIDs[] = {
	{ 0x01, 0x01,   "nobject" },
	{ 0x02, 0x02,   "ncontext" },
      	{  0,0, NULL }
  };

  return findTableID (TableIDs, id);
}




/*
  -- BIOP  "Magic"  ID 
  -- e.g. TS 102 812
*/

char *dsmccStrBIOP_MAGIC (u_int id)
{
  STR_TABLE  TableIDs[] = {
	{ 0x42494F50, 0x42494F50,   "BIOP" },
      	{  0,0, NULL }
  };

  return findTableID (TableIDs, id);
}







