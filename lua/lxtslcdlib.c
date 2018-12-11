
/*
** $Id: lxtslcdlib.c,v 1.65.1.1 2018/07/27 Xtase-fgalliat Exp $
** Xtase LCD library
** Copyright : Xtase-fgalliat

**
linit.c  to open lib
lualib.h to define lib
**



*/

#define lxtslcdlib_c
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
XtsConsole console;

// #define CLR_PINK  8
// #define CLR_GREEN 6
// #define CLR_BLACK 0
// #define CLR_WHITE 1
// -------------------------------------------



static int lcd_cls (lua_State *L) {
	// printf("LCD cls\n");
	console.getScreen()->cls();
	return 1;
}

static int lcd_blitt (lua_State *L) {
	
	// if lua_isint .....
	// if empty => 0
	// if error => auto handled as num_expected
	int mode = (int)luaL_optinteger(L, 1, EXIT_SUCCESS);
	
	// printf("LCD blitt %d\n", mode);
	return 1;
}

static int lcd_cursor (lua_State *L) {
	int x = (int)luaL_optinteger(L, 1, EXIT_SUCCESS);
	int y = (int)luaL_optinteger(L, 2, EXIT_SUCCESS);
	
	console.getScreen()->setCursor(x,y);
	return 1;
}


static int lcd_rgb (lua_State *L) {
	int r = (int)luaL_optinteger(L, 1, EXIT_SUCCESS);
	int g = (int)luaL_optinteger(L, 2, EXIT_SUCCESS);
	int b = (int)luaL_optinteger(L, 3, EXIT_SUCCESS);
	
	lua_pushinteger( L, rgb16(r,g,b) );
	return 1;
}


static int lcd_print (lua_State *L) {
  const char *str = luaL_optstring(L, 1, NULL);
  
  //printf("LCD print :: %s\n", str);
  console.getScreen()->print( (char*)str );
  return 1;
  
  /*
  int stat = system(cmd);
  if (cmd != NULL)
    return luaL_execresult(L, stat);
  else {
    lua_pushboolean(L, stat);  // true if there is a shell 
    return 1;
  }
  */
}

// -= Shapes =-
static int lcd_rect (lua_State *L) {
	int x = (int)luaL_optinteger(L, 1, EXIT_SUCCESS);
	int y = (int)luaL_optinteger(L, 2, EXIT_SUCCESS);
	int w = (int)luaL_optinteger(L, 3, EXIT_SUCCESS);
	int h = (int)luaL_optinteger(L, 4, EXIT_SUCCESS);
	
	int mode  = (int)luaL_optinteger(L, 5, EXIT_SUCCESS);
	int color = (int)luaL_optinteger(L, 6, EXIT_SUCCESS);
	
	
	//printf("LCD rect(%d, %d, %d, %d,  %d, %d)\n", x, y, w, h,  mode, color);
	console.getScreen()->drawRect(x,y,w,h,mode,color);
	return 1;
}

static int lcd_circle (lua_State *L) {
	int x = (int)luaL_optinteger(L, 1, EXIT_SUCCESS);
	int y = (int)luaL_optinteger(L, 2, EXIT_SUCCESS);
	int radius = (int)luaL_optinteger(L, 3, EXIT_SUCCESS);
	
	int mode  = (int)luaL_optinteger(L, 4, EXIT_SUCCESS);
	int color = (int)luaL_optinteger(L, 5, EXIT_SUCCESS);
	
	
	//printf("LCD circle(%d, %d, %d,  %d, %d)\n", x, y, radius,  mode, color);
	console.getScreen()->drawCircle(x,y,radius,mode,color);
	return 1;
}

static int lcd_triangle (lua_State *L) {
	int  x1 = (int)luaL_optinteger(L, 1, EXIT_SUCCESS);
	int  y1 = (int)luaL_optinteger(L, 2, EXIT_SUCCESS);
	
	int  x2 = (int)luaL_optinteger(L, 3, EXIT_SUCCESS);
	int  y2 = (int)luaL_optinteger(L, 4, EXIT_SUCCESS);
	
	int  x3 = (int)luaL_optinteger(L, 5, EXIT_SUCCESS);
	int  y3 = (int)luaL_optinteger(L, 6, EXIT_SUCCESS);
	
	int mode  = (int)luaL_optinteger(L, 7, EXIT_SUCCESS);
	int color = (int)luaL_optinteger(L, 8, EXIT_SUCCESS);
	

	console.getScreen()->drawTriangle( x1, y1, x2, y2, x3, y3, mode, color );
	//printf("LCD triangle\n");
	return 1;
}

static int lcd_line (lua_State *L) {
	int x1 = (int)luaL_optinteger(L, 1, EXIT_SUCCESS);
	int y1 = (int)luaL_optinteger(L, 2, EXIT_SUCCESS);
	int x2 = (int)luaL_optinteger(L, 3, EXIT_SUCCESS);
	int y2 = (int)luaL_optinteger(L, 4, EXIT_SUCCESS);
	
	int color = (int)luaL_optinteger(L, 5, EXIT_SUCCESS);
	
	//printf("LCD line(%d, %d, %d, %d,  %d)\n", x1, y1, x2, y2,  color);
	console.getScreen()->drawLine(x1,y1,x2,y2,color);
	return 1;
}

// -= Images =-
static int lcd_bpp (lua_State *L) {
	const char *filename = luaL_optstring(L, 1, NULL);
	
	int x=0;
	int y=0;
	console.getScreen()->drawBPP( (char*)filename, x, y );
	//printf("LCD bpp\n");
	return 1;
}

static int lcd_pct (lua_State *L) {
	const char *str = luaL_optstring(L, 1, NULL);
	int           x = (int)luaL_optinteger(L, 2, EXIT_SUCCESS);
	int           y = (int)luaL_optinteger(L, 3, EXIT_SUCCESS);
	
	//printf("LCD pct\n");
	console.getScreen()->drawPCT( (char*)str, x, y );
	return 1;
}

static int lcd_sprite (lua_State *L) {
	const char *str = luaL_optstring(L, 1, NULL);
	int           x = (int)luaL_optinteger(L, 2, EXIT_SUCCESS);
	int           y = (int)luaL_optinteger(L, 3, EXIT_SUCCESS);
	
	int           w = (int)luaL_optinteger(L, 4, EXIT_SUCCESS);
	int           h = (int)luaL_optinteger(L, 5, EXIT_SUCCESS);
	
	int          sx = (int)luaL_optinteger(L, 6, EXIT_SUCCESS);
	int          sy = (int)luaL_optinteger(L, 7, EXIT_SUCCESS);
	
	//printf("LCD sprite\n");
	console.getScreen()->drawPCTSprite( (char*)str, x, y, w, h, sx, sy );
	return 1;
}

// -= Backgrounds =-
static int _lcd_fx_array(lua_State *L, int bckMode, int arrayShiftIndex);

static int lcd_fx (lua_State *L) {
	
	int32_t argnum = lua_gettop(L);
  	/* if (1 != argnum) {
    	printf("Function %s expects 1 argument got %d\n", __PRETTY_FUNCTION__, argnum);
    	return 0;
  	}  */
  	
  	if (0 == lua_isinteger(L, 1)) {
    	printf("Missing fx num\n");
    	return 0;
	}
	int bckMode = (int)luaL_optinteger(L, 1, EXIT_SUCCESS);
  	
	if (0 == lua_istable(L, 2)) { // if not a table
		int m1 = (int)luaL_optinteger(L, 2, EXIT_SUCCESS);
		int m2 = (int)luaL_optinteger(L, 3, EXIT_SUCCESS);
		int m3 = (int)luaL_optinteger(L, 4, EXIT_SUCCESS);
		int m4 = (int)luaL_optinteger(L, 5, EXIT_SUCCESS);

		// printf("LCD fx(%d,  %d, %d, %d, %d)\n", bckMode, m1, m2, m3, m4);
		console.getScreen()->drawAnimatedBackground( bckMode, m1, m2, m3, m4 );
    	return 1;
	}
	
	_lcd_fx_array( L, bckMode, 1 );
	
	return 1;
}



static int _lcd_fx_array(lua_State *L, int bckMode, int arrayShiftIndex) {
	luaL_checktype(L, 1+arrayShiftIndex, LUA_TTABLE);
    // let alone excessive arguments (idiomatic), or do:
    lua_settop(L, 1+arrayShiftIndex);

    int a_size = lua_rawlen(L, 1+arrayShiftIndex); // absolute indexing for arguments
    uint8_t *buf = (uint8_t*)malloc((size_t)a_size);

    for (int i = 1; i <= a_size; i++) {
        lua_pushinteger(L, i);
        lua_gettable(L, 1+arrayShiftIndex); // always give a chance to metamethods
        // OTOH, metamethods are already broken here with lua_rawlen()
        // if you are on 5.2, use lua_len()

        if (lua_isnil(L, -1)) { // relative indexing for "locals"
            a_size = i-1; // fix actual size (e.g. 4th nil means a_size==3)
            break;
        }

        if (!lua_isnumber(L, -1)) // optional check
            return luaL_error(L, "item %d invalid (number required, got %s)",
                              i, luaL_typename(L, -1));

        lua_Integer b = lua_tointeger(L, -1);

        if (b < 0 || b > UINT8_MAX) // optional
            return luaL_error(L, "item %d out of range", i);

        buf[i-1] = b; // Lua is 1-based, C is 0-based
        lua_pop(L, 1);
    }
    
    //for(int i=0; i < a_size; i++) {
    ///	printf( "[%d] %d \n", i, buf[i] );
    //}
    
    // printf("LCD fx(%d, [%d bytes stream])\n", bckMode, a_size);
    console.getScreen()->drawAnimatedBackground( bckMode, buf, a_size );
    
    free(buf);

    return 0;
}

// to move
static int lcd_delay (lua_State *L) {
	
	int time = (int)luaL_optinteger(L, 1, EXIT_SUCCESS);
	
	usleep( time * 1000 );
	return 1;
}





static const luaL_Reg xtslcdlib[] = {
	/*
  {"clock",     os_clock},
  {"date",      os_date},
  {"difftime",  os_difftime},
  {"execute",   os_execute},
  {"exit",      os_exit},
  {"getenv",    os_getenv},
  {"remove",    os_remove},
  {"rename",    os_rename},
  {"setlocale", os_setlocale},
  {"time",      os_time},
  {"tmpname",   os_tmpname},
  */
  {"cls",     lcd_cls},
  {"blitt",   lcd_blitt},
  {"print",   lcd_print},
  
  {"cursor",  lcd_cursor},
  {"rgb",  lcd_rgb},

  {"rect",     lcd_rect},
  {"circle",   lcd_circle},
  {"triangle", lcd_triangle},
  {"line",     lcd_line},
  
  {"bpp",     lcd_bpp},
  {"pct",     lcd_pct},
  {"sprite",  lcd_sprite},
  
  {"fx",  lcd_fx},
  
  // to move
  {"delay",  lcd_delay},
  
  {NULL, NULL}
};

/* }====================================================== */



LUAMOD_API int luaopen_xtslcd (lua_State *L) {
  if ( !console.isInited() ) { console.init(); }

  luaL_newlib(L, xtslcdlib);
  return 1;
}

