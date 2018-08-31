#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
//#include <pthread.h>
#include <iostream>
#include <unistd.h> // usleep()

// ______________________________________
/*
#include "../../cur_arch.h"
//#include "../../gba/libGBA.h"
Screen screen;
Joypad joypad;
InputDevState* inputState = NULL;
*/

#include "../XtsConsole.h"
XtsConsole console;

#define Zzz(a) delay(a)

// ______________________________________

#include "Logger.h"
#include "GameBoyConsole.h"

/*
// TMP
#define WHITE 0xFFFFFFFF
#define BLACK 0xFF000000
#define LT_GRAY 0xFFAAAAAA
#define GRAY 0xFF999999


#define WHITE16 (31)<<11 | (31) << 6 | (31)
#define LT_GRAY16 (20)<<11 | (20) << 6 | (20)
#define GRAY16 (10)<<11 | (10) << 6 | (10)
#define BLACK16 0
*/
#define WHITE16 CLR_WHITE
#define LT_GRAY16 rgb16(190, 190, 190)
#define GRAY16 rgb16(120, 120, 120)
#define BLACK16 CLR_BLACK


const int GB_SCREEN_WIDTH = 160;
const int GB_SCREEN_HEIGHT = 144;

bool dirty = true;

// void setPixel(int addr, int color);
// void setPixel(int x, int y, int color) {
//   	setPixel( y*GB_SCREEN_WIDTH + x, color);
// }

GameBoyConsole* gbconsole = NULL;

// _________________________________________________

unsigned short VRAM[ GB_SCREEN_WIDTH*GB_SCREEN_HEIGHT ];
unsigned short old_VRAM[ GB_SCREEN_WIDTH*GB_SCREEN_HEIGHT ];

// void setPixel(int addr, int color) {
// /*
//   old_VRAM[addr] = VRAM[addr];
//   //memcpy( old_VRAM, VRAM, 160*144 );
//   
//   if ( color == 16777215 ) { color = WHITE16; }
//   else if ( color == 0 ) { color = BLACK16; }
//   else if ( color == -16777216)  { color = LT_GRAY16; }
//   else if ( color == -1)  { color = GRAY16; }
//   else { printf("%d\n", color); }
// 
//   
//     VRAM[ addr ] = color;
//   
//   
//   //if ( old_VRAM[addr] != VRAM[addr] ) {
// 	dirty = true;
//   //}
//   */
// }

void setScreenDirty() {
  dirty = true;
}

void setPixelIndexed(int addr, int color) {
  old_VRAM[addr] = VRAM[addr];
  
  if ( color == 0 ) { VRAM[ addr ] = WHITE16; }
  else if ( color == 1 ) { VRAM[ addr ] = LT_GRAY16; }
  else if ( color == 2 ) { VRAM[ addr ] = GRAY16; }
  else if ( color == 3 ) { VRAM[ addr ] = BLACK16; }
  else printf("%d\n", color);
  
  
  //printf("@%d, %d\n", addr,color);
  
  //if (old_VRAM[addr] != VRAM[addr]) 
 //   dirty = true;
}





void screen_init() {
	/*
        //initMath();
        screen.open();
        
        inputState = NULL; // else joypad insn't centered !!!
				joypad.open();
				
				screen.prepareArea();
	*/
	
	console.init();
        
}

// _________________________________________________

// /!\ BEWARE : 'KEY_UP' & co. are defined in <input.h>
#define _KEY_UP 1
#define _KEY_DOWN 2
#define _KEY_LEFT 4
#define _KEY_RIGHT 8

#define _KEY_L 16
#define _KEY_R 32
#define _KEY_A 64
#define _KEY_B 128

#define _KEY_X 129 // beware can't mask those on 8bit
#define _KEY_Y 130
#define _KEY_MENU 131

#define NO_KEY 0

int cpt=0;
	
int pad_getkey() {
	
  int key = NO_KEY;
  Pad* pad = console.readPad();
  
  if ( pad->left() )  { key |= _KEY_LEFT;  gbconsole->KEYS_PRESSED[2] = true; } else { gbconsole->KEYS_PRESSED[2] = false; }
  if ( pad->right() ) { key |= _KEY_RIGHT; gbconsole->KEYS_PRESSED[3] = true; } else { gbconsole->KEYS_PRESSED[3] = false; }
  
  if ( pad->up() )   { key |= _KEY_UP;   gbconsole->KEYS_PRESSED[0] = true; } else { gbconsole->KEYS_PRESSED[0] = false; }
  if ( pad->down() ) { key |= _KEY_DOWN; gbconsole->KEYS_PRESSED[1] = true; } else { gbconsole->KEYS_PRESSED[1] = false; }
  
  int A_PRS = 4;
  int B_PRS = 5;
  if ( pad->bt1() ) { key |= _KEY_A; gbconsole->KEYS_PRESSED[4] = true; } else { gbconsole->KEYS_PRESSED[4] = false; }
  if ( pad->bt2() ) { key |= _KEY_B; gbconsole->KEYS_PRESSED[5] = true; } else { gbconsole->KEYS_PRESSED[5] = false; }
  
  int START_PRS = 6;
  if ( pad->start() ) { key |= _KEY_MENU; gbconsole->KEYS_PRESSED[START_PRS] = true; } else { gbconsole->KEYS_PRESSED[START_PRS] = false; }

/*
    if ( (inputState = joypad.readInputFrame( inputState )) != NULL) {
    	// { 38, 40, 37, 39, 88, 90, 10, 16, 32 }
    	// up, dn, lt, rt, x, z, ??, shift, space
    	
      if ( inputState->xAxis < 90 ) { key |= _KEY_LEFT; console->KEYS_PRESSED[2] = true; } else { console->KEYS_PRESSED[2] = false; }
       if ( inputState->xAxis > 160 ) { key |= _KEY_RIGHT; console->KEYS_PRESSED[3] = true; } else { console->KEYS_PRESSED[3] = false; }

      if ( inputState->yAxis < 90 ) { key |= _KEY_UP; console->KEYS_PRESSED[0] = true; } else { console->KEYS_PRESSED[0] = false; }
       if ( inputState->yAxis > 160 ) { key |= _KEY_DOWN; console->KEYS_PRESSED[1] = true; } else { console->KEYS_PRESSED[1] = false; }

      if ( inputState->L1 == 1 ) { key |= _KEY_A; console->KEYS_PRESSED[4] = true; } else { console->KEYS_PRESSED[4] = false; }
      if ( inputState->L2 == 1 ) { key |= _KEY_B; console->KEYS_PRESSED[5] = true; } else { console->KEYS_PRESSED[5] = false; }
      
      if ( inputState->X == 1 )    { key |= _KEY_X;    console->KEYS_PRESSED[7] = true; } else { console->KEYS_PRESSED[7] = false; }
      if ( inputState->Y == 1 )    { key |= _KEY_Y;    console->KEYS_PRESSED[8] = true; } else { console->KEYS_PRESSED[8] = false; }
      if ( inputState->MENU == 1 ) { key |= _KEY_MENU; console->KEYS_PRESSED[6] = true; } else { console->KEYS_PRESSED[6] = false; }

      if ( inputState->quitBtn == 1 ) { printf("dirty kill\n"); exit(0); }

    }
*/
    Zzz(20);

    #ifdef _WIN32
      if ( cpt%50==0 ) {
    	printf("Hey Windows : I'm not dead !\n");
      }
      cpt++;
    #endif

	if ( key != 0 ) {
		printf("Hit a button !!!!!\n");
	}

return key;
}

int pad_waitkey() {
	int key = NO_KEY;
	while( (key = pad_getkey()) == NO_KEY ) { Zzz(50); }
	return key;
}


// )))))))))))))))))))))))))))))))

void *keyThread(void *argument){
      //char* msg;
      //msg = (char*)argument;
      //std::cout<<msg<<std::endl;
  
  
  while( true ) {
    //readStick();
    pad_waitkey(); 
    Zzz(100);
  }
  
}


//extern int SCREEN_WIDTH;
//extern int SCREEN_HEIGHT;

void drawGBScreen() {
  //if ( !dirty ) { return; }
  //screen.prepareArea(true);

  int zoom = 2;
  int cx = (SCREEN_WIDTH - GB_SCREEN_WIDTH*zoom)/2;
  int cy = (SCREEN_HEIGHT - GB_SCREEN_HEIGHT*zoom)/2;
  
  int addr,cyy;
  for(int y=0; y < GB_SCREEN_HEIGHT; y++) {
    addr = (y*GB_SCREEN_WIDTH)+0;
    cyy = cy+y*zoom;
    for(int x=0; x < GB_SCREEN_WIDTH; x++) {
      //addr = (y*160)+x;
      addr++;
      //if ( old_VRAM[addr] != VRAM[addr] ) {
      if ( true ) {
        //screen.fillRect16bpp( cx+x*zoom, cyy, zoom, zoom, VRAM[ addr ]);
        
        //console.getScreen()->drawPixel( cx+x, cyy, VRAM[ addr ] );
        console.getScreen()->drawPixel( cx+x, cy+y, VRAM[ addr ] );
        
        
        
        //screen.setRGB16bpp(cx+x*zoom, cyy, WHITE16 );
        
      }
    }
    //printf("\n");
  }
  
  /*
  screen.flushArea();
  screen.flipArea();
  */
  
  dirty = false;
}


void *drawThread(void *argument){
  
  while( true ) {
    drawGBScreen();
    Zzz(50);
    //printf("d\n");
  }
  
}


void *startGame(void *argument) {
  gbconsole->changeRom( (char*) argument);
  return NULL;
}

// (((((((((((((((((((((((((((((((


int main(int argc, char** argv) { // new (c++) signature needed w/ SDL

 screen_init();
 
 //screen.fillArea( 0,0,0 );
 console.cls();
 
 memset(VRAM, BLACK16, GB_SCREEN_HEIGHT*GB_SCREEN_WIDTH);
 memset(old_VRAM, BLACK16, GB_SCREEN_HEIGHT*GB_SCREEN_WIDTH);

    //// moa little anim
		//for (int i = 0; i < GB_SCREEN_HEIGHT; i++) {
		//	for (int j = 0; j < GB_SCREEN_WIDTH; j++) {
		//		setPixel(j, i, WHITE);
		//	}
		//}
		//for (int i = 0; i < GB_SCREEN_WIDTH; i++) {
		//	setPixel(i, GB_SCREEN_HEIGHT / 2, BLACK);
		//}
		
		// ============================
		
		gbconsole = new GameBoyConsole();
    gbconsole->init();
    Logger_debug("load rom");
    
    if ( argc < 2 ) { printf("I need a rom !\n"); exit(1); }
    
  pthread_t thread1, thread2, thread3;
  int i1,i2,i3;
  
  //i1 = pthread_create( &thread1, NULL, startGame, (void*) argv[1]);
  //console->changeRom( (char*) argv[1]);
  if ( !false ) {
  	i3 = pthread_create( &thread3, NULL, startGame, (void*) argv[1]);
  	
  	
    while(true) {
    	drawGBScreen();
      Zzz(90);
      pad_getkey();
    }  	
  	
  	pthread_join(thread3,NULL);
  } else {
  	i1 = pthread_create( &thread1, NULL, keyThread, (void*) NULL);
    i2 = pthread_create( &thread2, NULL, drawThread, (void*) NULL);
  
	  startGame( (void*)argv[1]);
	}

// TODO in another thread : pollForQuit()

//pthread_join(thread2,NULL);
//screen.close();
//pthread_join(thread2,NULL);

/*
screen.close();
joypad.close();
*/

console.close();

}
