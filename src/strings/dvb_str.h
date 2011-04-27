/*
$Id: dvb_str.h,v 1.36 2009/11/22 15:36:31 rhabarber1848 Exp $ 


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de


 -- dvb strings

*/



#ifndef __DVB_STR_H
#define __DVB_STR_H 



char *dvbstrPID_assignment (u_int id);
char *dvbstrTableID (u_int id);
char *dvbstrMPEGDescriptorTAG (u_int tag);
char *dvbstrDVBDescriptorTAG (u_int tag);
char *dvbstrCurrentNextIndicator (u_int flag);
char *dvbstrWEST_EAST_FLAG (u_int tag);
char *dvbstrPolarisation_FLAG (u_int tag);
char *dvbstrModulationCable_FLAG(u_int flag);
char *dvbstrModulationSAT_FLAG (u_int tag);
char *dvbstrRollOffSAT_FLAG (u_int flag);
char *dvbstrFECinner_SCHEME (u_int tag);
char *dvbstrFECouter_SCHEME (u_int tag);
char *dvbstrLinkage_TYPE(u_int tag);
char *dvbstrHandover_TYPE(u_int tag);
char *dvbstrOrigin_TYPE(u_int tag);
char *dvbstrService_TYPE(u_int tag);
char *dvbstrStream_TYPE(u_int tag);
char *dvbstrStream_TYPE_SHORT (u_int flag);
char *dvbstrAudio_TYPE(u_int tag);
char *dvbstrCASystem_ID(u_int id);
char *dvbstrDataBroadcast_ID(u_int flag);
char *dvbstrOriginalNetwork_ID (u_int i);
char *dvbstrNetworkIdent_ID(u_int id);
char *dvbstrBroadcast_ID(u_int id);
char *dvbstrTeletext_TYPE(u_int id);
char *dvbstrTerrBandwidth_SCHEME(u_int id);
char *dvbstrTerrConstellation_FLAG(u_int id);
char *dvbstrTerrHierarchy_FLAG(u_int id);
char *dvbstrTerrCodeRate_FLAG(u_int id);
char *dvbstrTerrGuardInterval_FLAG(u_int id);
char *dvbstrTerrTransmissionMode_FLAG(u_int id);
char *dvbstrTerrPriority (u_int i);
char *dvbstrTerrTimeSlicingIndicator (u_int i);
char *dvbstrTerrMPE_FEC_Indicator (u_int i);
char *dvbstrTerr_DVBH_service_indication (u_int i);
char *dvbstrAspectRatioInfo_FLAG(u_int id);
char *dvbstrHierarchy_TYPE(u_int id);
char *dvbstrRunningStatus_FLAG (u_int id);
char *dvbstrDataStreamVIDEOAlignment_TYPE (u_int id);
char *dvbstrDataStreamAUDIOAlignment_TYPE (u_int id);
char *dvbstrDataService_ID (u_int id);
char *dvbstrContent_Component_TYPE (u_int id);
char *dvbstrLogCellPresInfo_TYPE(u_int id);
char *dvbstrCellLinkageInfo_TYPE(u_int id);
char *dvbstrTextCharset_TYPE(u_int id);
char *dvbstrContentNibble_TYPE(u_int id);
char *dvbstrParentalRating_TYPE(u_int id);
char *dvbstrDelivSysCoding_TYPE(u_int id);
char *dvbstrShortSmoothingBufSize_TYPE(u_int id);
char *dvbstrShortSmoothingBufLeakRate_TYPE(u_int id);
char *dvbstrDVB_AC3_ComponentType (u_int i);
char *dvbstrDVB_DTS_Audio_SampleRateCode(u_int i);
char *dvbstrDVB_DTS_Audio_BitRate (u_int i);
char *dvbstrDVB_DTS_Audio_SurroundMode (u_int i);
char *dvbstrDVB_DTS_Audio_ExtendedSurroundFlag (u_int i);
char *dvbstrAncillaryData_ID(u_int id);
char *dvbstrAnnouncement_TYPE(u_int id);
char *dvbstrAnnouncementReference_TYPE(u_int id);


/* -- Transport Stream Stuff */

char *dvbstrTSpid_ID (u_int id);
char *dvbstrTS_AdaptationField_TYPE (u_int id);
char *dvbstrTS_TEI (u_int id);
char *dvbstrTS_PUSI (u_int id);
char *dvbstrTS_ScramblingCtrl_TYPE (u_int id);

/* -- PES stuff */

char *dvbstrPESstream_ID(u_int id);
char *dvbstrPESstream_ID_Extension (u_int i);    // 2004-08-11 H.222.0 AMD2
char *dvbstrPESscrambling_ctrl_TYPE(u_int id);
char *dvbstrPESTrickModeControl (u_int i);
char *dvbstrPESDataIdentifier (u_int i);
char *dvbstrPES_EBUDataUnitID (u_int i);

char *dvbstrTELETEXT_framingcode (u_int i);
char *dvbstrTELETEXT_packetnr (u_int i);
char *dvbstrTELETEXT_lang_code (u_int i);


char *dvbstrVPS_pcs_audio (u_int i);
char *dvbstrVPS_cni_countrycode (u_int i);
char *dvbstrVPS_pty (u_int i);
char *dvbstrVPS_npp (u_int i);

char *dvbstrWSS_aspect_ratio (u_int i);
char *dvbstrWSS_film_bit (u_int i);
char *dvbstrWSS_color_coding_bit (u_int i);
char *dvbstrWSS_helper_bit (u_int i);
char *dvbstrWSS_subtitleTeletext_bit (u_int i);
char *dvbstrWSS_subtitling_mode (u_int i);
char *dvbstrWSS_surround_bit (u_int i);
char *dvbstrWSS_copyright_bit (u_int i);
char *dvbstrWSS_copy_generation_bit (u_int i);


/* -- Div Stuff */

char *dvbstrCountryCode_ID (u_int i);
char *dvbstrPrivateDataSpecifier_ID (u_int i);

char *dvbstrBouquetTable_ID (u_int i);
char *dvbstrStreamContent_Component_TYPE (u_int i);



/* EN 301 192 v1.4.1 updates */

char *dvbstrTimeSlice_bit_used (u_int i);
char *dvbstrMPE_FEC_algo (u_int i);
char *dvbstrMPE_FEC_max_burst_size (u_int i);
char *dvbstrMPE_FEC_frame_rows (u_int i);
char *dvbstrMPE_FEC_max_average_rate (u_int i);
char *dvbstrMPE_FEC_table_frame_boundary (u_int i);


/* TS 102 323 v1.1.1  TV ANYTIME */

char *dvbstrTVA_RunningStatus(u_int i);
char *dvbstrTVA_crid_type (u_int i);
char *dvbstrTVA_crid_location (u_int i);

char *dvbstrTVA_content_id_type (u_int i);



/* H.222.0 AMD1 - AMD3 update */

char *dvbstrMPEG_metadata_application_format (u_int i);
char *dvbstrMPEG_Content_time_base_indicator (u_int i);
char *dvbstrMPEG_metadata_section_frag_indication (u_int i);



/* ISO 13818-2 */

char *dvbstrMPEG_FrameRateCode (u_int i);
char *dvbstrMPEG_PictureCodingType (u_int i);
char *dvbstrMPEG_ExtensionStartCodeIdentifier (u_int i);
char *dvbstrMPEG_ProfileIndication (u_int i);
char *dvbstrMPEG_LevelIndication (u_int i);
char *dvbstrMPEG_ChromaFormat (u_int i);
char *dvbstrMPEG_VideoFormat (u_int i);
char *dvbstrMPEG_ColorPrimaries (u_int i);
char *dvbstrMPEG_TransferCharacteristics (u_int i);
char *dvbstrMPEG_MatrixCoefficients (u_int i);
char *dvbstrMPEG_ScalableMode (u_int i);
char *dvbstrMPEG_Intra_DC_Precision (u_int i);
char *dvbstrMPEG_PictureStructure (u_int i);
char *dvbstrMPEG_Original_Or_Copy (u_int i);


/* TS 101 191 */
char *dvbstrTS_MIP_Syncronization (u_int i);
char *dvbstrTS_MIP_FunctionTag (u_int i);
char *dvbstrTS_MIP_ChannelBandwidth (u_int i);



#endif



