/*
 *
 * (c) Vladi Belperchinov-Shabanski "Cade" <cade@biscom.net> 1998-1999  
 * 
 * SEE `README',`LICENSE' OR `COPYING' FILE FOR LICENSE AND OTHER DETAILS!
 *
 * $Id: form_in.h,v 1.2 2001/10/28 13:53:02 cade Exp $
 *
 */


#ifndef _FORM_IN_H_
#define _FORM_IN_H_

#include "unicon.h"
#include "vstring.h"
#include "clusters.h"

extern BSet FI_LETTERS;
extern BSet FI_DIGITS;
extern BSet FI_ALPHANUM;
extern BSet FI_REALS;
extern BSet FI_USERS;
extern BSet FI_MASKS;

extern int EditStrBF; // bakground/foreground
extern int EditStrFH; // first hit color

// allows only FI_USERS chars
int FormInput( int x, int y, const char *prompt, const char *mask, String *strres, void (*handlekey)( int key, String &s, int &pos ) = NULL );
int TextInput( int x, int y, const char *prompt, int maxlen, int fieldlen, String *strres, void (*handlekey)( int key, String &s, int &pos ) = NULL );
int TextInput( int x, int y, const char *prompt, int maxlen, int fieldlen, char *strres, void (*handlekey)( int key, String &s, int &pos ) = NULL );

#endif //_FORM_IN_H_

