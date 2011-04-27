/*
$Id: userdefs.c,v 1.7 2009/11/22 15:36:17 rhabarber1848 Exp $


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de  (rasc)


  Private Sections & Descriptors
  -- will branch to default user section table or descriptor
  -- or to known specific private data structurs

*/


#include "dvbsnoop.h"
#include "userdefs.h"

#include "descriptors/descriptor.h"
#include "misc/output.h"

#include "default/section_private_default.h"
#include "default/descriptor_private_default.h"



//
// -- How does this work:
// --  Sections tables or descriptors in different scopes (DVB_SI, MHP, etc.)
// --  may have userdefined tables/descriptors.
// --  This may differ or overlap between different providers (e.g. "premiere.de")
// --  so we have a table reference e.g. "premiere.de" to a get-function
// --  to get section tables and descriptor tag table data.
// --  These two tables reference from table_id /descriptor_tag, etc. to a 
// --  decoding function
//





//
// -- Table for getting reference functions for known provider strings/ids
// -- reference functions gets known section & descriptor tag references
//

typedef struct _PRIVATE_PROVIDER_FUNC {
    char     *str;          /* e.g. "premiere.de" */
    void     (*func)();     /* function for getting table & descriptors */
} PRIV_PROVIDER_FUNC;




//
// -- defines for Provider Space descriptors and table references
// -- provider names in lowercase!!
//

#include "eicta.org/eicta_org.h"
#include "nordig.org/nordig_org.h"
#include "premiere.de/premiere_de.h"

static PRIV_PROVIDER_FUNC ppf[] = {
	{ "eicta.org",		getPrivate_EictaORG },
	{ "nordig.org",		getPrivate_NordigORG },
	{ "premiere.de",	getPrivate_PremiereDE },
	{ NULL,			NULL }
};




static char privProviderStr[32] = "";
static void *get_tag_table_for_ProviderStr (int type);







//
// -- Private Section Output
// -- dvb default or known userdef/private section
//

void section_PRIVATE (u_char *b, int len)
{
  PRIV_SECTION_ID_FUNC *t;
  u_int		       table_id;


  // -- get id/function reference table for provider str
  // -- get table for section tables

  t = (PRIV_SECTION_ID_FUNC *) get_tag_table_for_ProviderStr (0);


  // -- reference table for provider found ?
  // -- scan table ids for decode function 

  if (t) {
     table_id =  (u_int) b[0];
     while (t->func && t->table_id) {
       if (t->table_id == table_id) {
	  out_nl (3, "using private provider space: %s",privProviderStr);
          (*(t->func))(b,len);	/* exec decode function */
          return;
       }
       t++;
     }
  }


  // -- no private provider str match
  // -- or table id not found for provider
  // -- --> default userdef section decoding
 
  section_PRIVATE_default (b, len);
}




//
// -- Private Descriptor Output
// -- dvb default or known userdef/private descriptors
//

void descriptor_PRIVATE (u_char *b, DTAG_SCOPE tag_scope)
{
  PRIV_DESCR_ID_FUNC *t;
  u_int	             descr_tag;


  // -- get id/function reference table for provider
  // -- get table for descriptors

  t = (PRIV_DESCR_ID_FUNC *) get_tag_table_for_ProviderStr (1);


  // -- reference table for provider found ?
  // -- scan descriptor tags and tag scopeIDs (DVB_SI, MPEG, etc.)
  // -- for decode function 

  if (t) {
     descr_tag =  (u_int) b[0];
     while (t->func && t->descriptor_tag) {
       if ((t->descriptor_tag == descr_tag) && (t->tag_scope == tag_scope)) {
	  out_nl (3, "using private provider space: %s",privProviderStr);
          (*(t->func))(b);	/* exec decode function */
          return;
       }
       t++;
     }
  }


  // -- no private provider match
  // -- or descriptor tag + descriptor tag scope not  found for
  // -- priviate provider 
  // -- --> default userdef descriptor decoding
 
  descriptor_PRIVATE_default (b);
}






// ------------------------------------------------------------------


//
// -- Set provider str of private descriptors or tables
// -- z.B. "premiere.de"
//

void set_PRIVATE_ProviderStr (char *s)
{
   int i = sizeof (privProviderStr)-1;

   if (! s) s = ""; 
   strncpy (privProviderStr,s,i);
   privProviderStr[i] = '\0';

}




//
// -- list all private provider strings (output)
//

void list_PRIVATE_ProviderStrs (void)
{
  PRIV_PROVIDER_FUNC *t = ppf;

  while (t->str) {
    printf (" %s\n",t->str);
    t++;
  }

  return;
}







//
// get_tag_table_for_ProviderStr    (type=0,1)
// -- get_section_refs_for_...    (type=0)
// -- get_descriptor_refs_for_... (type=1)
// -- return: NULL (if no provider, or default) or ptr to reference tag table
//

static void *get_tag_table_for_ProviderStr (int type)
{
  PRIV_PROVIDER_FUNC *t = ppf;


  if ((!privProviderStr) || privProviderStr[0] == '\0') {
     return NULL;
  }


  while (t->str && t->func) {

    if (! strcmp (t->str, privProviderStr) ) {
	PRIV_SECTION_ID_FUNC *psect;
	PRIV_DESCR_ID_FUNC   *pdesc;

	// -- execute e.g. getPrivate_PremiereDE ( &psect, &pdesc);
        (*(t->func))(&psect, &pdesc);   /* exec decode function */
	return  (type) ? (void *)pdesc : (void *)psect;
    }

    t++;
  }

  return NULL;
}






// $$$ TODO:  change interface mimic (call priv. data decoding):
//       output if data matches for output
//       return: true/false if data was decoded 
//        exec should be done to any standard table/descriptor checking
//        so we can overlay also standard descriptors/table (e.g. if change by provider)
//        --> see descriptor enhancments for e.g. IDSB (ARIB STD-10, japanese)
//
