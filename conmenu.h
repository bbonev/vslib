#ifndef _CONMENU_H_
#define _CONMENU_H_

#include <clusters.h>

struct  ToggleEntry
{
  int  key;
  char name[64];
  int  *data;
  char **states;
};

struct ConMenuInfo
{
  ConMenuInfo() { defaults(); }
  void defaults() { cn = 112; ch = 47; ti = 95; bo = ec = ac = 0; }
 
  int cn; // normal color
  int ch; // highlight color
  int ti; // title color
 
  int bo; // should view borders?
 
  int ec; // exit char (used by con_menu_box)
  int ac; // alternative confirm (used by menu box)

  int st; // scroll type -- 1 dynamic and 0 normal/static
  char hide_magic[32];
};

extern ConMenuInfo con_default_menu_info;

int con_toggle_box( int x, int y, const char *title, ToggleEntry* toggles, ConMenuInfo *menu_info );
int con_menu_box( int x, int y, const char *title, PSZCluster *sc, int hotkeys, ConMenuInfo *menu_info );

/* show full screen pszcluster list (w/o last two lines of the screen) */
int con_full_psz_box( int x, int y, const char *title, PSZCluster *sc, ConMenuInfo *menu_info );

#endif //_CONMENU_H_
