
/*
** $Id: lxtswifilib.c,v 1.65.1.1 2018/09/03 Xtase-fgalliat Exp $
** Xtase WIFI library
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

bool _w_connected = false;

// wifi > UP
static int wifi_up (lua_State *L) {
	printf("(WIFI) UP\n");

	_w_connected = true;

	lua_pushboolean(L, _w_connected);

	return 1;
}

// wifi > DOWN
static int wifi_down (lua_State *L) {
	printf("(WIFI) DOWN\n");

	_w_connected = false;

	lua_pushboolean(L, _w_connected);

	return 1;
}

// wifi > RESTART
static int wifi_restart (lua_State *L) {
	printf("(WIFI) RESTART\n");

	_w_connected = true;

	lua_pushboolean(L, _w_connected);

	return 1;
}

// list registered networks (not scanned ones)
static int wifi_list (lua_State *L) {
	char infos[1024];

	strcpy(infos, "Lvb-XXXX"); strcat(infos, ":"); 
	strcat(infos, "AndroidAP"); strcat(infos, ":"); 
	strcat(infos, "AI-Tinker"); strcat(infos, ":"); 

	lua_pushstring(L, infos);
	return 1;
}

// registers a network
static int wifi_new (lua_State *L) {
	const char *ssid = luaL_optstring(L, 1, NULL);
	const char *psk = luaL_optstring(L, 2, NULL);
	
	printf("(WIFI) add conn. : %s > %s\n", ssid, psk);

	lua_pushboolean(L, true);

	return 1;
}

// removes a registered network
static int wifi_remove (lua_State *L) {
	const char *str = luaL_optstring(L, 1, NULL);
	
	printf("(WIFI) remove conn. : %s\n", str);

	lua_pushboolean(L, true);

	return 1;
}

// @ this time : returns a concat str / LATER see for an object
static int wifi_info (lua_State *L) {
	char infos[256];

	strcpy(infos, _w_connected ? "1" : "0" );
	strcat(infos, ":" );
	strcat(infos, _w_connected ? "F??Kbox-XXX" : "NULL" );
	strcat(infos, ":" );
	strcat(infos, _w_connected ? "192.168.1.254" : "0.0.0.0" );

	lua_pushstring(L, infos);
	return 1;
}



static const luaL_Reg xtswifilib[] = {

  {"up",      wifi_up },
  {"down",    wifi_down },
  {"restart", wifi_restart },

  {"list",    wifi_list },
  {"new",     wifi_new },
  {"rm",      wifi_remove },

  {"info",    wifi_info },

  {NULL, NULL}
};

/* }====================================================== */



LUAMOD_API int luaopen_xtswifi (lua_State *L) {
  if ( !console.isInited() ) { console.init(); }

  luaL_newlib(L, xtswifilib);
  return 1;
}

