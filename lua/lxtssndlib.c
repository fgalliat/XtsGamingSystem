
/*
** $Id: lxtssndlib.c,v 1.65.1.1 2018/08/29 Xtase-fgalliat Exp $
** Xtase SND library
** Copyright : Xtase-fgalliat

**
linit.c  to open lib
lualib.h to define lib
**

*/

#define lxtssndlib_c
#define LUA_LIB

#include "lprefix.h"


#include <errno.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "lua.h"

#include "lauxlib.h"
#include "lualib.h"

// -------------------------------------------
#include <stdint.h>
#include <unistd.h> // for usleep()


#include "../XtsConsole.h"
// declared in LCD lib
extern XtsConsole console;
// -------------------------------------------



static int snd_pause (lua_State *L) {
	console.getSoundCard()->pause();
	return 1;
}

static int snd_stop (lua_State *L) {
	console.getSoundCard()->stop();
	return 1;
}

static int snd_prev (lua_State *L) {
	console.getSoundCard()->prev();
	return 1;
}

static int snd_next (lua_State *L) {
	console.getSoundCard()->next();
	return 1;
}

static int snd_play (lua_State *L) {
	int track = (int)luaL_optinteger(L, 1, EXIT_SUCCESS);
	
	console.getSoundCard()->play(track);
	// lua_pushboolean(L, stat);  // true if there is a shell 
	return 1;
}


// static int lcd_print (lua_State *L) {
//   const char *str = luaL_optstring(L, 1, NULL);
  
//   //printf("LCD print :: %s\n", str);
//   console.getScreen()->print( (char*)str );
//   return 1;
  
//   /*
//   int stat = system(cmd);
//   if (cmd != NULL)
//     return luaL_execresult(L, stat);
//   else {
//     lua_pushboolean(L, stat);  // true if there is a shell 
//     return 1;
//   }
//   */
// }

// -= Volume =-
static int snd_setVolume (lua_State *L) {
	int vol = (int)luaL_optinteger(L, 1, EXIT_SUCCESS);
	console.getSoundCard()->volume(vol);
	return 1;
}

static int snd_getVolume (lua_State *L) {
	int vol = console.getSoundCard()->getVolume();
	lua_pushinteger(L, vol);
	return 1;
}

static int snd_isPlaying (lua_State *L) {
	bool play = console.getSoundCard()->isPlaying();
	lua_pushboolean(L, play);
	return 1;
}

// -= Current Track =-

static int snd_trackNb (lua_State *L) {
	int trck = console.getSoundCard()->getTrackNb();
	lua_pushinteger(L, trck);
	return 1;
}

static int snd_trackNum (lua_State *L) {
	int trck = console.getSoundCard()->getTrackNum();
	lua_pushinteger(L, trck);
	return 1;
}

static int snd_trackName (lua_State *L) {
	char* trck = console.getSoundCard()->getTrackName();
	lua_pushstring(L, trck);
	return 1;
}



static const luaL_Reg xtssndlib[] = {

  {"play",   snd_play },
  {"pause",  snd_pause },
  {"stop",   snd_stop },
  {"next",   snd_next },
  {"prev",   snd_prev },

  {"setvolume",  snd_setVolume },
  {"getvolume",  snd_getVolume },
  {"isPlaying",  snd_isPlaying },

  {"getTrackNb",   snd_trackNb   },
  {"getTrackNum",  snd_trackNum  },
  {"getTrackName", snd_trackName },

  // {"getTrackNames", snd_trackNames },
  
  {NULL, NULL}
};

/* }====================================================== */



LUAMOD_API int luaopen_xtssnd (lua_State *L) {
  if ( !console.isInited() ) { console.init(); }

  luaL_newlib(L, xtssndlib);
  return 1;
}

