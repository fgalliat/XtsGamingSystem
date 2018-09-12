
/*
** $Id: lxtspwrlib.c,v 1.65.1.1 2018/09/03 Xtase-fgalliat Exp $
** Xtase POWER Managment library
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

// battery time from discharging > in minutes (5min accurate)
static int pwr_time (lua_State *L) {
	int time = console.getPower()->getTime();

	lua_pushinteger(L, time);

	return 1;
}

// reset the battery timer > 
static int wifi_down (lua_State *L) {
	console.getPower()->resetTime();

	lua_pushboolean(L, true);

	return 1;
}

// halt the system
static int pwr_halt (lua_State *L) {
	console.halt();

	lua_pushboolean(L, true);

	return 1;
}

// reboot the system
static int pwr_reboot (lua_State *L) {
	console.reboot();

	lua_pushboolean(L, true);

	return 1;
}

// exit the system > return to bash
static int pwr_exit (lua_State *L) {
	console.exit();

	lua_pushboolean(L, true);

	return 1;
}


static const luaL_Reg xtspwrlib[] = {

  {"time",      pwr_time },  // time from discharging battery (5min accurate)
  {"resetTime", pwr_resetTime },
  
  {"halt",      pwr_halt },   // halt system
  {"reboot",    pwr_reboot }, // reboot system
  {"exit",      pwr_exit },   // return to bash

  {NULL, NULL}
};

/* }====================================================== */



LUAMOD_API int luaopen_xtspwr (lua_State *L) {
  if ( !console.isInited() ) { console.init(); }

  luaL_newlib(L, xtspwrlib);
  return 1;
}

