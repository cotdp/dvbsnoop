/*
$Id: output.c,v 1.13 2009/11/22 15:36:10 rhabarber1848 Exp $


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de (rasc)


 --  Output Module

*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>


#include "dvbsnoop.h"
#include "output.h"


/*
  -- Module Global Vars
*/

static int  max_verbose_level = 0;
static int  col0 = 0;		//2

static int  indent_level = 0;
int   table_indent [] = {0,4,8,12,15,18,21,24,27,30};

#define MAX_INDENT_LEVEL  ( (sizeof(table_indent)/sizeof(int)) - 1)






/*
   -- set indent-level
   -- and sends a '\r' to reset indent prints
   - +1 = indent plus one level
   - -1 = unindent one level
   -  0 = reset to Level 0 
*/

void indent (int v)

{
  if (v == 0) indent_level  = 0;
  else        indent_level += v;

  if (indent_level < 0)
     indent_level = 0;
  if (indent_level >= MAX_INDENT_LEVEL)
     indent_level = MAX_INDENT_LEVEL;

//2  fputc ('\r',stdout);
//2  print_indent();
//    out_nl2 (0);
}



/*
 -- set max verbosity level
 -- 0 = highest, 9 = lowest level
 -- print message upto (including) this verbosity level
*/

void setMaxVerboseLevel (int v)
{
  max_verbose_level = v;
}

int getMaxVerboseLevel ()
{
 return max_verbose_level;
}




/*
  -- output special printf
  -- out_nl will append \n at the end of the output
*/

void out(int verbose, const char *msgfmt,...)
{
  va_list args;

  if (verbose <= max_verbose_level) {
     print_indent(); //2
     va_start (args,msgfmt);
     vfprintf (stdout, msgfmt, args);
     va_end   (args);
  }
}


void out_nl(int verbose, const char *msgfmt,...)
{
  va_list args;

  if (verbose <= max_verbose_level) {
     print_indent();  //2
     va_start (args,msgfmt);
     vfprintf (stdout, msgfmt, args);
     va_end   (args);

     out_nl2(verbose);
  }
}


/*
  -- just print a NL
*/

void  out_nl2 (int verbose)
{
  if (verbose <= max_verbose_level) {
     fputc ('\n',stdout);
     col0 = 1; //2
//2     print_indent();
  }

}


void print_indent (void)

{
 int i;

 if (! col0)  return; //2

 for (i=0; i<table_indent[indent_level]; i++) {
   fputc (' ',stdout);
 }

 col0 = 0; //2
}



