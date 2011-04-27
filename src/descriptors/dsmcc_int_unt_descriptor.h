/*
$Id: dsmcc_int_unt_descriptor.h,v 1.15 2009/11/22 15:36:06 rhabarber1848 Exp $ 


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de (rasc)


 -- Private TAG Space  DSM-CC   INT, UNT, ...
 -- DSM-CC INT/UNT Descriptors

*/


#ifndef __DSM_INT_UNT_DESCRIPTOR_H
#define __DSM_INT_UNT_DESCRIPTOR_H 


int  descriptorDSMCC_INT_UNT (u_char *b);

void descriptorDSMCC_scheduling (u_char *b);
void descriptorDSMCC_update (u_char *b);
void descriptorDSMCC_ssu_location (u_char *b);
void descriptorDSMCC_message(u_char *b);
void descriptorDSMCC_ssu_event_name (u_char *b);
void descriptorDSMCC_target_smartcard (u_char *b);
void descriptorDSMCC_target_MAC_address (u_char *b);
void descriptorDSMCC_target_serial_number (u_char *b);
void descriptorDSMCC_target_IP_address (u_char *b);
void descriptorDSMCC_target_IPv6_address (u_char *b);
void descriptorDSMCC_ssu_subgroup_association (u_char *b);
void descriptorDSMCC_IP_MAC_platform_name (u_char *b);
void descriptorDSMCC_IP_MAC_platform_provider_name (u_char *b);
void descriptorDSMCC_target_MAC_address_range (u_char *b);
void descriptorDSMCC_target_IP_slash (u_char *b);
void descriptorDSMCC_target_IP_source_slash (u_char *b);
void descriptorDSMCC_target_IPv6_slash (u_char *b);
void descriptorDSMCC_target_IPv6_source_slash (u_char *b);
void descriptorDSMCC_IP_MAC_StreamLocation (u_char *b);
void descriptorDSMCC_ISP_access_mode (u_char *b);


#endif


