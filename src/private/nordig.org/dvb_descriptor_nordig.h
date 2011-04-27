/*
$Id: dvb_descriptor_nordig.h,v 1.3 2009/11/22 15:36:18 rhabarber1848 Exp $ 


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de (rasc)


 -- private DVB Descriptors  nordig.org

*/


#ifndef _NORDIG_DVB_DESCRIPTOR_H
#define _NORDIG_DVB_DESCRIPTOR_H 


void descriptor_PRIVATE_NordigORG_LogicChannelDescriptor (u_char *b);
void descriptor_PRIVATE_NordigORG_ContentProtectionDescriptor (u_char *b);


#endif

