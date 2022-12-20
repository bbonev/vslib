/****************************************************************************
 *
 *  Copyright (c) 1996-2022 Vladi Belperchinov-Shabanski "Cade" 
 *  http://cade.noxrun.com/  <cade@noxrun.com> <cade@bis.bg> <cade@cpan.org>
 *
 *  SEE `README',`LICENSE' OR `COPYING' FILE FOR LICENSE AND OTHER DETAILS!
 *
 ****************************************************************************/

#include <vstring.h>
#include <wstring.h>
#include "form_in.h"
#include "scroll.h"

int EditStrBF = CONCOLOR( chWHITE, cBLUE );
int EditStrFH = CONCOLOR( cBLACK, cWHITE );

int TextInput( int x, int y, const char *prompt, int maxlen, int fieldlen, VString *strres, void (*handlekey)( int key, VString &s, int &pos ) )
{
  int res = 0;
  int insert = 1;
  VString str = *strres;
  VString tmp;
  int ch;

  ScrollPos scroll;
  scroll.set_min_max( 0, str_len( str ) );
  scroll.set_pagesize( fieldlen );
  scroll.set_pagestep( 0.3 );
  scroll.go( str_len(str) );

  int show = 1;
  int firsthit = 1;
  int opage = -1;
  con_cshow();
  while(1)
    {
    if (opage != scroll.page()) show = 1;
    if (show)
      {
      str_copy( tmp, str, scroll.page(), scroll.pagesize() );
      str_pad( tmp, -scroll.pagesize() );
      tmp = " " + tmp + " ";
      if ( scroll.page() > 0 ) str_set_ch( tmp, 0, '<' );
      if ( scroll.page() + scroll.pagesize() < str_len(str) ) str_set_ch( tmp, str_len(tmp)-1, '>' );
      con_out(x, y, tmp, firsthit ? EditStrFH : EditStrBF );
      show = 0;
      opage = scroll.page();
      }
    con_xy( x + scroll.pos() - scroll.page() + 1 , y );
    ch = con_getch();
    if( ch >= 32 && ch <= 255 && ch != KEY_BACKSPACE && str_len(str) < maxlen - 1 )
      {
      if (firsthit)
        {
        str = "";
        scroll.go(0);
        firsthit = 0;
        }
        if (!insert) str_del( str, scroll.pos(), 1 );
        str_ins_ch( str, scroll.pos(), ch );
        scroll.set_min_max( 0, str_len( str ) );
        scroll.go( scroll.pos() );
        scroll.down();
      show = 1;
      };
    if (firsthit)
      {
      show = 1;
      firsthit = 0;
      }

    if( ch == 27 )
      {
      res = 0;
      break;
      } else
    if( ch == 13 )
      {
      *strres = str;
      res = 1;
      break;
      } else
    if( ch == KEY_CTRL_U )
      {
      scroll.go(0);
      str = "";
      show = 1;
      } else
    if( (ch == KEY_BACKSPACE || ch == 8 ) && (scroll.pos() > 0) )
      {
      scroll.up();
      str_del( str, scroll.pos(), 1 );
      show = 1;
      } else
    if ( ch == KEY_IC    ) insert = !insert; else
    if ( ch == KEY_LEFT  ) scroll.up(); else
    if ( ch == KEY_RIGHT ) scroll.down(); else
    /*
    if ( ch == KEY_PPAGE ) scroll.ppage(); else
    if ( ch == KEY_NPAGE ) scroll.npage(); else
    */
    if ( ch == KEY_HOME || ch == KEY_CTRL_A ) scroll.go(0); else
    if ( ch == KEY_END  || ch == KEY_CTRL_E ) scroll.go(str_len(str)); else
    if ( ( ch == KEY_DC || ch == KEY_CTRL_D ) && scroll.pos() < str_len(str) )
      {
      str_del( str, scroll.pos(), 1 );
      show = 1;
      } else
    if ( handlekey )
      {
      int npos = scroll.pos();
      handlekey( ch, str, npos );
      scroll.set_min_max( 0, str_len( str ) );
      scroll.go( scroll.pos() );
      if (scroll.pos() != npos) scroll.go( npos );
      show = 1;
      }

    scroll.set_min_max( 0, str_len( str ) );
    scroll.go( scroll.pos() );
    }
  con_chide();
  return res;
}

int TextInput( int x, int y, const char *prompt, int maxlen, int fieldlen, char *strres, void (*handlekey)( int key, VString &s, int &pos ) )
{
  VString str = strres;
  int res = TextInput( x, y, prompt, maxlen, fieldlen, &str, handlekey );
  strcpy( strres, str.data() );
  return res;
}

/*** WIDE CHAR STRING VERSION ***********************************************/

int TextInputWS( int x, int y, const char *prompt, int maxlen, int fieldlen, VString *strres, void (*handlekey)( int key, VString &s, int &pos ) )
{
  int res = 0;
  int insert = 1;
  WString str;
  str.set_failsafe( strres->data() );
  WString tmp;
  int ctrl;

  ScrollPos scroll;
  scroll.set_min_max( 0, str_len( str ) );
  scroll.set_pagesize( fieldlen );
  scroll.set_pagestep( 0.3 );
  scroll.go( str_len(str) );

  int show = 1;
  int firsthit = 1;
  int opage = -1;
  con_cshow();
  while(1)
    {
    if (opage != scroll.page()) show = 1;
    if (show)
      {
      str_copy( tmp, str, scroll.page(), scroll.pagesize() );
      str_pad( tmp, -scroll.pagesize() );
      tmp = L" " + tmp + L" ";
      if ( scroll.page() > 0 ) str_set_ch( tmp, 0, L'<' );
      if ( scroll.page() + scroll.pagesize() < str_len(str) ) str_set_ch( tmp, str_len(tmp)-1, L'>' );
      VString str_out = tmp.data();
      con_out( x, y, str_out, firsthit ? EditStrFH : EditStrBF );
      show = 0;
      opage = scroll.page();
      }
    con_xy( x + scroll.pos() - scroll.page() + 1 , y );
    
    wchar_t wch;
    ctrl = con_getwch( &wch );
    if( wch >= 32 && ctrl != KEY_BACKSPACE && str_len(str) < maxlen - 1 )
      {
      if (firsthit)
        {
        str = L"";
        scroll.go(0);
        firsthit = 0;
        }
        if (!insert) str_del( str, scroll.pos(), 1 );
        str_ins_ch( str, scroll.pos(), wch );
        scroll.set_min_max( 0, str_len( str ) );
        scroll.go( scroll.pos() );
        scroll.down();
      show = 1;
      };
    if (firsthit)
      {
      show = 1;
      firsthit = 0;
      }

    if( wch == 27 )
      {
      res = 0;
      break;
      } else
    if( wch == 13 )
      {
      *strres = str.data();
      res = 1;
      break;
      } else
    if( wch == KEY_CTRL_U )
      {
      scroll.go(0);
      str = L"";
      show = 1;
      } else
    if( (ctrl == KEY_BACKSPACE || wch == 8 ) && (scroll.pos() > 0) )
      {
      scroll.up();
      str_del( str, scroll.pos(), 1 );
      show = 1;
      } else
    if ( ctrl == KEY_IC    ) insert = !insert; else
    if ( ctrl == KEY_LEFT  ) scroll.up(); else
    if ( ctrl == KEY_RIGHT ) scroll.down(); else
    /*
    if ( ctrl == KEY_PPAGE ) scroll.ppage(); else
    if ( ctrl == KEY_NPAGE ) scroll.npage(); else
    */
    if ( ctrl == KEY_HOME || ctrl == KEY_CTRL_A || wch == 1 ) scroll.go(0); else
    if ( ctrl == KEY_END  || ctrl == KEY_CTRL_E || wch == 5 ) scroll.go(str_len(str)); else
    if ( ( ctrl == KEY_DC || ctrl == KEY_CTRL_D || wch == 4 ) && scroll.pos() < str_len(str) )
      {
      str_del( str, scroll.pos(), 1 );
      show = 1;
      } else
    if ( handlekey )
      {
      int npos = scroll.pos();
      
      VString hstr = str.data();
      handlekey( wch, hstr, npos );
      str = hstr.data();
      scroll.set_min_max( 0, str_len( str ) );
      scroll.go( scroll.pos() );
      if (scroll.pos() != npos) scroll.go( npos );
      show = 1;
      }

    scroll.set_min_max( 0, str_len( str ) );
    scroll.go( scroll.pos() );
    }
  con_chide();
  return res;
}

int TextInputWS( int x, int y, const char *prompt, int maxlen, int fieldlen, char *strres, void (*handlekey)( int key, VString &s, int &pos ) )
{
  VString str = strres;
  int res = TextInputWS( x, y, prompt, maxlen, fieldlen, &str, handlekey );
  strcpy( strres, str.data() );
  return res;
}

// eof form_in.cpp
