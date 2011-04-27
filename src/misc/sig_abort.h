/*
$Id: sig_abort.h,v 1.3 2009/11/22 15:36:10 rhabarber1848 Exp $


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de (rasc)


 -- Handle Kill/Interrupt Signals from User/OS
 -- (e.g. Kill -1)

*/


#ifndef __SIG_ABORT_H
#define __SIG_ABORT_H


void initOSSigHandler (void);
int  isSigAbort (void);
void restoreOSSigHandler (void);


#endif


