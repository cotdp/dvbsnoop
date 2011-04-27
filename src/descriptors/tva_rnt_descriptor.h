/*
$Id: tva_rnt_descriptor.h,v 1.3 2009/11/22 15:36:06 rhabarber1848 Exp $ 


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de (rasc)


 -- Private TAG Space  TS 102 323  TV-Anytime 
 -- RNT Descriptors

*/


#ifndef __TVA_RNT_DESCRIPTOR_H
#define __TVA_RNT_DESCRIPTOR_H


int  descriptorTVA (u_char *b);

void descriptorTVA_RAR_over_DVB_stream (u_char *b);
void descriptorTVA_RAR_over_IP_stream (u_char *b);
void descriptorTVA_RNT_scan (u_char *b);


#endif


