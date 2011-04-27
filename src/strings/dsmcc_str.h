/*
$Id: dsmcc_str.h,v 1.32 2009/11/22 15:36:31 rhabarber1848 Exp $ 


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de


 -- dsmcc strings

*/


#ifndef __DSMCC_STR_H
#define __DSMCC_STR_H 


char *dsmccStrDSMCC_CAROUSEL_DescriptorTAG (u_int i);
char *dsmccStrDSMCC_INT_UNT_DescriptorTAG (u_int i);
char *dsmccStrMHP_AIT_DescriptorTAG (u_int i);


char *dsmccStrMHPOrg (u_int id);
char *dsmccStrAction_Type (u_int id);
char *dsmccStrProcessing_order (u_int id);
char *dsmccStrPayload_scrambling_control (u_int id);
char *dsmccStrAddress_scrambling_control (u_int id);
char *dsmccStrLinkage0CTable_TYPE (u_int i);
char *dsmccStrMultiProtEncapsMACAddrRangeField (u_int i);
char *dsmccStrPlatform_ID (u_int id);
char *dsmccStrCarouselType_ID (u_int id);
char *dsmccStrHigherProtocol_ID (u_int id);
char *dsmccStrUpdateType_ID (u_int id);

char *dsmccStr_Command_ID  (u_int id);
char *dsmccStr_SelectMode_ID  (u_int id);
char *dsmccStr_DirectionIndicator (u_int id);

char *dsmccStr_DescriptorType (u_int id);
char *dsmccStr_SpecifierType (u_int id);
char *dsmccStr_AccessMode (u_int id);

char *dsmccStr_UpdateFlag (u_int id);
char *dsmccStr_UpdateMethod (u_int id);
char *dsmccStr_TimeUnits (u_int id);

char *dsmccStr_GroupModuleLinkPosition (u_int id);
char *dsmccStr_compression_method (u_int id);

char *dsmccStr_streamMode (u_int id);
char *dsmccStr_postDiscontinuityIndicator (u_int id);

char *dsmccStrOUI  (u_int id);
char *dsmccStr_LLC_SNAP_prot (u_int id);



char *dsmccStrMHP_application_type (u_int id);
char *dsmccStrMHP_application_id (u_int id);
char *dsmccStrMHP_application_control_code (u_int id);
char *dsmccStrMHP_visibility_state (u_int id);
char *dsmccStrMHP_protocol_id (u_int id);
char *dsmccStrMHP_storage_property (u_int id);
char *dsmccStrMHP_caching_transparency_level (u_int id);


char *dsmccStr_adaptationType (u_int id);
char *dsmccStr_dsmccType (u_int id);
char *dsmccStr_messageID (u_int id);
char *dsmccStr_transactionID_originator (u_int id);


char *dsmccStrIOP_ProfileID (u_int id);
char *dsmccStrBIOP_TAP_Use (u_int id);
char *dsmccStrBIOP_TAP_SelectorType (u_int id);
char *dsmccStrBIOP_EndianType (u_int id);
char *dsmccStrBIOP_TypeID_Alias (u_int id);
char *dsmccStrBIOP_BindingType (u_int id);
char *dsmccStrBIOP_MAGIC (u_int id);


#endif




