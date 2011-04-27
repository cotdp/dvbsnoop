/*
$Id: dsmcc_carousel_descriptor.h,v 1.17 2009/11/22 15:36:06 rhabarber1848 Exp $ 


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de (rasc)


 -- Private TAG Space  DSM-CC
 -- DSM-CC Carousel Descriptors 

*/


#ifndef __DSMCC_CAROUSEL_DESCRIPTOR_H
#define __DSMCC_CAROUSEL_DESCRIPTOR_H 


int  descriptorDSMCC_CAROUSEL (u_char *b);

void descriptorDSMCC_type (u_char *b);
void descriptorDSMCC_name (u_char *b);
void descriptorDSMCC_info (u_char *b);
void descriptorDSMCC_module_link (u_char *b);
void descriptorDSMCC_crc32 (u_char *b);
void descriptorDSMCC_location (u_char *b);
void descriptorDSMCC_est_download_time (u_char *b);
void descriptorDSMCC_group_link (u_char *b);
void descriptorDSMCC_compressed_module (u_char *b);
void descriptorDSMCC_subgroup_association (u_char *b);

void descriptorDSMCC_MHP_label (u_char *b);
void descriptorDSMCC_MHP_caching_priority (u_char *b);
void descriptorDSMCC_MHP_content_type (u_char *b);


#endif


