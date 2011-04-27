/*
$Id: dvbsnoop.c,v 1.34 2009/11/22 15:36:05 rhabarber1848 Exp $

 DVBSNOOP

 a dvb sniffer and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2005   Rainer.Scherg@gmx.de

*/


#include "dvbsnoop.h"

#include "misc/cmdline.h"
#include "misc/hexprint.h"
#include "misc/pkt_time.h"
#include "misc/pid_mem.h"
#include "misc/sig_abort.h"

#include "dvb_api/dmx_sect.h"
#include "dvb_api/dmx_pes.h"
#include "dvb_api/dmx_ts.h"
#include "dvb_api/dmx_tspidscan.h"
#include "dvb_api/dmx_tspidbandwidth.h"
#include "dvb_api/fe_signal.h"
#include "dvb_api/fe_info.h"






int main(int argc, char **argv)

{

  OPTION  opt;
  int     err = 0;


  /*
    -- init options and cmdline parsing
  */

  init_PidMemory ();


  if (! cmdline_options (argc,argv, &opt) ) return (-1);

  setMaxVerboseLevel (opt.printdecode);
  setHexPrintMode    (opt.printhex);



  indent (0);
  if (! opt.binary_out) {
     if (! opt.hide_copyright) {
        out_nl (1, "%s -- %s ", DVBSNOOP_PROG_VERSION, DVBSNOOP_URL);
     }

     if (! opt.inpPidFile) {
	if (opt.pid != DUMMY_PID) {
		out_nl (9, "   PID   : %d (0x%04x)",opt.pid,opt.pid);
	}
	if ((opt.packet_mode == SECT) && (opt.filterLen > 0)) {		// filter are only for sections

		int i;
		out (9, "   Filter: 0x");
		for (i=0; i < opt.filterLen; i++) {
			out (9,"%02x ",opt.filter[i]);
		}
		out_NL (9);
		out (9, "   Mask  : 0x");
		for (i=0; i < opt.filterLen; i++) {
			out (9,"%02x ",opt.mask[i]);
		}
		out_NL (9);
		out_nl (9, "   Max. Filtersize: %d",DMX_FILTER_SIZE);

	}
	out_nl (9, "   DEMUX : %s",opt.devDemux);
	out_nl (9, "   DVR   : %s",opt.devDvr);
	out_nl (9, "   FRONTEND: %s",opt.devFE);
     }
  }



  initOSSigHandler ();
  init_receive_time ();


	  switch (opt.packet_mode) {
		case SECT:
			err = doReadSECT (&opt);
			break;

		case PS:
		case PES:
			err = doReadPES (&opt);
			break;

		case TS:
			err = doReadTS (&opt);
			break;

		case PIDSCAN:
			err = ts_pidscan (&opt);
			break;

		case PIDBANDWIDTH:
			err = ts_pidbandwidth (&opt);
			break;

		case SCAN_FE_SIGNAL:
			err = do_SignalStrength (&opt);
			break;

		case SCAN_FE_INFO:
			err = do_FE_Info (&opt);
			break;

		default:
			fprintf (stderr,"unknown snoop type (this should never happen).\n");
			break;

	  }




 if ( isSigAbort() ) {
	 out_nl (1,"... aborted (Signal: %d)",isSigAbort());
 }
 restoreOSSigHandler();
 return err;

}






