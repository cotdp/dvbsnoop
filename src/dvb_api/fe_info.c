/*
$Id: fe_info.c,v 1.8 2009/11/22 15:36:07 rhabarber1848 Exp $


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de  (rasc)


 -- FrontProcessor Info
 --  DVB-API 

*/


#include <stdint.h>
#include <sys/time.h>
#include <errno.h>


#include "dvbsnoop.h"
#include "fe_info.h"
#include "fe_misc.h"
#include "misc/cmdline.h"
#include "misc/output.h"

#include "dmx_error.h"
#include "dvb_api.h"


#if DVB_API_VERSION == 1

  // -- not supported in DVB-API 1
  
  int  do_FE_Info (OPTION *opt)
  {
	 fprintf (stderr,"FE_info function not supported in DVB-API 1\n");
	 return 1;
  }


#else




int  do_FE_Info (OPTION *opt)

{
  int        fd_fe = 0;



  if (opt->inpPidFile) {
	fprintf (stderr,"Error: FileMode not possible...\n");
	return -1;
  } 


  if((fd_fe = open(opt->devFE,O_RDONLY)) < 0){
     IO_error(opt->devFE);
     return -1;
  }



   indent (0);
   out_NL (2);
   out_nl (2,"---------------------------------------------------------");
   out_nl (2,"FrontEnd Info...");
   out_nl (2,"---------------------------------------------------------");
   out_NL (2);

   out_nl (2,"Device: %s",opt->devFE);
   out_NL (2);

  print_FE_BasicCapabilities (3, fd_fe);
  print_FE_CurrentParameters (2, fd_fe);

  close(fd_fe);
  return 0;
}





#endif  // DVB-API Check





