/*
$Id: mhp_ait_descriptor.h,v 1.8 2009/11/22 15:36:06 rhabarber1848 Exp $ 


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de (rasc)


 -- Private TAG Space  MHP AIT
 -- MHP AIT Descriptors 

*/


#ifndef __MHP_AIT_DESCRIPTOR_H
#define __MHP_AIT_DESCRIPTOR_H 


int  descriptorMHP_AIT (u_char *b);

void descriptorMHP_AIT_application (u_char *b);
void descriptorMHP_AIT_application_name (u_char *b);
void descriptorMHP_AIT_transport_protocol (u_char *b);
void descriptorMHP_AIT_dvb_j_application (u_char *b);
void descriptorMHP_AIT_dvb_j_application_location (u_char *b);
void descriptorMHP_AIT_external_application_authorisation (u_char *b);
void descriptorMHP_AIT_dvb_html_application (u_char *b);
void descriptorMHP_AIT_dvb_html_application_location (u_char *b);
void descriptorMHP_AIT_dvb_html_application_boundary (u_char *b);
void descriptorMHP_AIT_application_icons (u_char *b);
void descriptorMHP_AIT_pre_fetch (u_char *b);
void descriptorMHP_AIT_DII_location (u_char *b);
void descriptorMHP_AIT_delegated_application (u_char *b);
void descriptorMHP_AIT_plug_in (u_char *b);
void descriptorMHP_AIT_application_storage (u_char *b);
void descriptorMHP_AIT_ip_signalling (u_char *b);



#endif


