/*
$Id: dvb_descriptor.h,v 1.17 2009/11/22 15:36:06 rhabarber1848 Exp $ 


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de (rasc)


 -- DVB Descriptors  ETSI 300 468

*/


#ifndef _DVB_DESCRIPTOR_H
#define _DVB_DESCRIPTOR_H 


int   descriptorDVB (u_char *b);

void  descriptorDVB_NetName (u_char *b);
void  descriptorDVB_ServList (u_char *b);
void  descriptorDVB_Stuffing (u_char *b);
void  descriptorDVB_SatDelivSys (u_char *b);
void  descriptorDVB_CableDelivSys (u_char *b);
void  descriptorDVB_VBI_Data (u_char *b);
void  descriptorDVB_VBI_Teletext (u_char *b);
void  descriptorDVB_BouquetName (u_char *b);
void  descriptorDVB_Service (u_char *b);
void  descriptorDVB_CountryAvail (u_char *b);
void  descriptorDVB_Linkage (u_char *b);
  void sub_descriptorDVB_Linkage0x08 (u_char *b, int len);
  void sub_descriptorDVB_Linkage0x09 (u_char *b, int len);
  void sub_descriptorDVB_Linkage0x0B (u_char *b, int len);
  void sub_descriptorDVB_Linkage0x0C (u_char *b, int len);
void  descriptorDVB_NVOD_Reference (u_char *b);
void  descriptorDVB_TimeShiftedService (u_char *b);
void  descriptorDVB_ShortEvent (u_char *b);
void  descriptorDVB_ExtendedEvent (u_char *b);
void  descriptorDVB_TimeShiftedEvent (u_char *b);
void  descriptorDVB_Component (u_char *b);
void  descriptorDVB_Mosaic (u_char *b);
void  descriptorDVB_StreamIdent (u_char *b);
void  descriptorDVB_CAIdentifier (u_char *b);
void  descriptorDVB_Content(u_char *b);
void  descriptorDVB_ParentalRating(u_char *b);
void  descriptorDVB_Teletext (u_char *b);
void  descriptorDVB_Telephone(u_char *b);
void  descriptorDVB_LocalTimeOffset (u_char *b);
void  descriptorDVB_Subtitling(u_char *b);
void  descriptorDVB_TerrestDelivSys (u_char *b);
void  descriptorDVB_MultilingNetworkName (u_char *b);
void  descriptorDVB_MultilingBouquetName (u_char *b);
void  descriptorDVB_MultilingServiceName (u_char *b);
void  descriptorDVB_MultilingComponent (u_char *b);
void  descriptorDVB_PrivateDataSpecifier (u_char *b);
void  descriptorDVB_ServiceMove (u_char *b);
void  descriptorDVB_FrequencyList (u_char *b);
void  descriptorDVB_ShortSmoothingBuffer(u_char *b);
void  descriptorDVB_PartialTransportStream(u_char *b);
void  descriptorDVB_DataBroadcast (u_char *b);
void  descriptorDVB_Scrambling(u_char *b);
void  descriptorDVB_DataBroadcastID(u_char *b);
void  descriptorDVB_TransportStream(u_char *b);
void  descriptorDVB_DSNG(u_char *b);
void  descriptorDVB_PDC(u_char *b);
void  descriptorDVB_AC3(u_char *b);
void  descriptorDVB_AncillaryData(u_char *b);
void  descriptorDVB_CellList(u_char *b);
void  descriptorDVB_CellFrequencyLink(u_char *b);
void  descriptorDVB_AnnouncementSupport(u_char *b);
void  descriptorDVB_ApplicationSignalling(u_char *b);
void  descriptorDVB_AdaptationFieldData(u_char *b);
void  descriptorDVB_ServiceIdentifier(u_char *b);
void  descriptorDVB_ServiceAvailability(u_char *b);
		 // TV ANYTIME  TS 102 323
void  descriptorDVB_DefaultAuthority (u_char *b);
void  descriptorDVB_RelatedContent(u_char *b);
void  descriptorDVB_TVA_ID(u_char *b);
void  descriptorDVB_ContentIdentifier(u_char *b);
		 // EN 301 192 v1.4.1  MPE_FEC
void  descriptorDVB_TimesliceFecIdentifier(u_char *b);
void  descriptorDVB_ECM_RepetitionRate(u_char *b);
		 // EN 300 468 v1.7.1
void  descriptorDVB_S2SatelliteDeliverySystem(u_char *b);
void  descriptorDVB_Enhanced_AC3(u_char *b);
void  descriptorDVB_DTS_Audio (u_char *b);
void  descriptorDVB_AAC (u_char *b);
void  descriptorDVB_Extension (u_char *b);



#endif

