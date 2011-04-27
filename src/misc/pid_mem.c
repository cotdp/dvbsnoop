/*
$Id: pid_mem.c,v 1.3 2009/11/22 15:36:10 rhabarber1848 Exp $



 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de (rasc)


 -- PID Memory for spidering PIDs

*/


#include "dvbsnoop.h"



enum PIDMEM_STATUS { PIDMEM_UNUSED, PIDMEM_STORED, PIDMEM_ISUSED };
static int  pidMEM[MAX_PID+1];




void  init_PidMemory (void)

{
  int i;

  for (i=0; i <= MAX_PID; i++) {
	  pidMEM[i] = PIDMEM_UNUSED;
  }

}



/*
 -- store a pid in PID Memory
 -- return: 1: stored, 0 = already in mem or illegal
*/

int store_PidToMem (int pid)
{

    if (pid >= 0 && pid <= MAX_PID) {
	    if (pidMEM[pid] == PIDMEM_UNUSED) {
		    pidMEM[pid] = PIDMEM_STORED;
		    return 1;
	    }
    }
    return 0;

}



/*
  -- get a Pid from PID Memory
  -- return: <PID> or INVALID_PID = no more PIDs
*/

int get_UnusedPidFromMem (void)
{
  int i;

  for (i=0; i <= MAX_PID; i++) {
	  if (pidMEM[i] == PIDMEM_STORED) {
		return i;
	  }
  }
  return INVALID_PID;
}



/*
  -- mark Pid in PID Memory as retrieved...
*/

void mark_PidMem_as_used (int pid)
{

  if (pid >= 0 && pid <= MAX_PID) {
	pidMEM[pid] = PIDMEM_ISUSED;
  }
  return;
}




// $$$TODO
//
// Future version may store stream type to distinguish between SECTION & PES
// --> Spider may also spider to PES streams
//

