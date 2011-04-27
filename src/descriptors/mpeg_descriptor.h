/*
$Id: mpeg_descriptor.h,v 1.14 2009/11/22 15:36:06 rhabarber1848 Exp $ 


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de  (rasc)

 -- MPEG Descriptors  ISO/IEC 13818-2

*/

#ifndef _MPEG_DESCRIPTOR_H
#define _MPEG_DESCRIPTOR_H 


int   descriptorMPEG (u_char *b);

void  descriptorMPEG_VideoStream (u_char *b);
void  descriptorMPEG_AudioStream (u_char *b);
void  descriptorMPEG_Hierarchy (u_char *b);
void  descriptorMPEG_Registration (u_char *b);
void  descriptorMPEG_DataStreamAlignment (u_char *b);
void  descriptorMPEG_TargetBackgroundGrid (u_char *b);
void  descriptorMPEG_VideoWindow (u_char *b);
void  descriptorMPEG_CA (u_char *b);
void  descriptorMPEG_ISO639_Lang (u_char *b);
void  descriptorMPEG_SystemClock (u_char *b);
void  descriptorMPEG_MultiplexBufUtil (u_char *b);
void  descriptorMPEG_Copyright (u_char *b);
void  descriptorMPEG_MaxBitrate (u_char *b);
void  descriptorMPEG_PrivateDataIndicator (u_char *b);
void  descriptorMPEG_SmoothingBuf (u_char *b);
void  descriptorMPEG_STD (u_char *b);
void  descriptorMPEG_IBP (u_char *b);
	/* 13818-6 , TR 102 006 */
void  descriptorMPEG_Carousel_Identifier (u_char *b);
void  descriptorMPEG_Association_tag (u_char *b);
void  descriptorMPEG_Deferred_Association_tags (u_char *b);

	/* 13818-6  Stream descriptors */
void descriptorMPEG_NPT_reference (u_char *b);
void descriptorMPEG_NPT_endpoint (u_char *b);
void descriptorMPEG_stream_mode (u_char *b);
void descriptorMPEG_stream_event (u_char *b);

	/* MPEG4 */
void  descriptorMPEG_MPEG4_video (u_char *b);
void  descriptorMPEG_MPEG4_audio (u_char *b);
void  descriptorMPEG_IOD (u_char *b);
void  descriptorMPEG_SL (u_char *b);
void  descriptorMPEG_FMC (u_char *b);
void  descriptorMPEG_External_ES_ID (u_char *b);
void  descriptorMPEG_MuxCode (u_char *b);
void  descriptorMPEG_FMXBufferSize (u_char *b);
void  descriptorMPEG_MultiplexBuffer (u_char *b);
void  descriptorMPEG_ContentLabeling (u_char *b);


     /* TV ANYTIME, TS 102 323 */
void descriptorMPEG_TVA_metadata_pointer (u_char *b);
void descriptorMPEG_TVA_metadata (u_char *b);
void descriptorMPEG_TVA_metadata_STD (u_char *b);

     /* H.222.0 AMD3 */
void descriptorMPEG_AVC_video (u_char *b);
void descriptorMPEG_IPMP (u_char *b);
void descriptorMPEG_AVC_timing_and_HRD (u_char *b);

     /* H.222.0 AMD4 */
void descriptorMPEG_MPEG2_AAC_audio (u_char *b);
void descriptorMPEG_FlexMuxTiming (u_char *b);


#endif

