
/*
** $Id: lxtspadlib.c,v 1.65.1.1 2018/08/29 Xtase-fgalliat Exp $
** Xtase PAD library
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


// see loslib.c
static void setboolfield (lua_State *L, const char *key, int value) {
  if (value < 0)  /* undefined? */
    return;  /* does not set field */
  lua_pushboolean(L, value);
  lua_setfield(L, -2, key);
}


/*
** Set all fields from structure 'Pad' in the table on top of the stack
*/
#define NB_OF_FIELDS 7

static void setallfields (lua_State *L, Pad *pad) {
  setboolfield(L, "up", pad->up() );
  setboolfield(L, "down", pad->down() );
  setboolfield(L, "left", pad->left() );
  setboolfield(L, "right", pad->right() );

  setboolfield(L, "start", pad->start() );
  setboolfield(L, "A", pad->bt1() );
  setboolfield(L, "B", pad->bt2() );

  setboolfield(L, "changed", pad->hasChanged() );
  setboolfield(L, "atLeastOne", pad->atLeastOne() );
}

static int pad_read (lua_State *L) {
	Pad* pad = console.readPad();

	lua_createtable(L, 0, NB_OF_FIELDS);  /* NB_OF_FIELDS = number of fields */
	setallfields(L, pad);

	return 1;
}


static int pad_get (lua_State *L) {
	Pad* pad = console.getPad();

	lua_createtable(L, 0, NB_OF_FIELDS);  /* NB_OF_FIELDS = number of fields */
	setallfields(L, pad);

	return 1;
}





static const luaL_Reg xtspadlib[] = {
  {"read",  pad_read},
  {"get",   pad_get},
  
  {NULL, NULL}
};

/* }====================================================== */



LUAMOD_API int luaopen_xtspad (lua_State *L) {
  if ( !console.isInited() ) { console.init(); }

  luaL_newlib(L, xtspadlib);
  return 1;
}

