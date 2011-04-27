/*
$Id: packet_mem.c,v 1.5 2009/11/22 15:36:10 rhabarber1848 Exp $


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de



 -- Collect packet data buffer/memory

*/



#include <string.h>
#include <stdlib.h>

#include "dvbsnoop.h"



typedef struct _PACKET_MEM_DATA {
	u_char 	*buf;
	u_long  max_length;	// requested mem length
	u_long	length;		// current length and next_add_pos;
} PACKET_MD;


static PACKET_MD  pmd[] = {
	{ NULL,  0UL, 0UL },
	{ NULL,  0UL, 0UL },
	{ NULL,  0UL, 0UL },
	{ NULL,  0UL, 0UL }
};







//
// -- acquire and initialize packet storage
// -- return: handle or -1 (no avail)
//

int  packetMem_acquire (u_long  requested_length)
{
  int  i;

	// -- is a handle available?

	for (i=0; i<sizeof(pmd)/sizeof(PACKET_MD); i++) {
		if (pmd[i].buf == NULL) {
			pmd[i].buf = malloc (requested_length);
			if (pmd[i].buf == NULL) return -1;
			pmd[i].max_length = requested_length;
			pmd[i].length = 0;
			return i;
		}
	}

	return -1;
}



//
// -- release packet storage
// -- return: handle
//

void packetMem_free (int handle)
{
   if ( (handle >= 0) && (handle < sizeof(pmd)/sizeof(PACKET_MD)) ) {
	free (pmd[handle].buf);
	pmd[handle].buf = NULL;
	pmd[handle].max_length = 0;
	pmd[handle].length = 0;
   }

}



//
// -- clear packet storage for reusage
//

void packetMem_clear (int handle)
{
   if ( (handle >= 0) && (handle < sizeof(pmd)/sizeof(PACKET_MD)) ) {
	pmd[handle].length = 0;
   }

}


//
// -- packet storage  has data
// -- return:  length or 0
//

u_long packetMem_length (int handle)
{
   if ( (handle >= 0) && (handle < sizeof(pmd)/sizeof(PACKET_MD)) ) {
	return pmd[handle].length;
   }

   return 0;
}

//
// -- packet storage  buffer start
// -- return:  bufferstart or NULL
//

u_char *packetMem_buffer_start (int handle)
{
   if ( (handle >= 0) && (handle < sizeof(pmd)/sizeof(PACKET_MD)) ) {
	return pmd[handle].buf;
   }

   return NULL;
}



//
// -- add data to packet storage
// -- copies data to packet storage
// -- return 1: ok  0: fail (illegal handle, no mem, out of storage, etc.)
//

int packetMem_add_data (int handle, u_char *buf, u_long len)
{

   u_long  l;

   if ( (handle >= 0) && (handle < sizeof(pmd)/sizeof(PACKET_MD)) ) {

	   l = pmd[handle].length + len;
	   if (pmd[handle].buf && (l < pmd[handle].max_length)) {
		   if (buf && len) {
			   memcpy (pmd[handle].buf+pmd[handle].length , buf, len);
			   pmd[handle].length += len;

			   return 1;
		   }
		   
	   }
   }

   return 0;
}












