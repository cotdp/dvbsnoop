/*
$Id: dvb_descriptor_eicta.h,v 1.1 2008/08/30 19:23:40 obi Exp $ 


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de (rasc)


 -- private DVB Descriptors  eicta.org

*/

#ifndef _EICTA_DVB_DESCRIPTOR_H
#define _EICTA_DVB_DESCRIPTOR_H

void descriptor_PRIVATE_EictaORG_LogicalChannelDescriptor (u_char *b);
void descriptor_PRIVATE_EictaORG_PreferredNameListDescriptor (u_char *b);
void descriptor_PRIVATE_EictaORG_PreferredNameIdentifierDescriptor (u_char *b);
void descriptor_PRIVATE_EictaORG_EacemStreamIdentifierDescriptor (u_char *b);

#endif
