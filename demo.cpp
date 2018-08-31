#include <errno.h>
#include <fcntl.h> 
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "XtsConsole.h"
XtsConsole console;

// ==================================================

// all files outside /MP3 folder 
void playMp3(int track) {
	console.playMp3(track);
	printf("Playing track >> %s <<\n", console.getMp3TrackName() );
} 

// ==============================================

const char* BTN0_ST = "Start";
const char* BTN1_ST = "[1]";
const char* BTN2_ST = "[2]";

const char* DIR_UP_ST = "[  Up   ]";
const char* DIR_LF_ST = "[ Left  ]";
const char* DIR_RT_ST = "[ Right ]";
const char* DIR_DN_ST = "[ Down  ]";

bool checkBtns() {
	Pad* pad = console.readPad();
	
	bool atLeastOne = false;
	bool result = false;
	
	
	     if ( pad->up() )   { printf( "%s ", DIR_UP_ST ); atLeastOne = true; }
	else if ( pad->down() ) { printf( "%s ", DIR_DN_ST ); atLeastOne = true; }
	
	     if ( pad->left() )  { printf( "%s ", DIR_LF_ST ); atLeastOne = true; }
	else if ( pad->right() ) { printf( "%s ", DIR_RT_ST ); atLeastOne = true; }
	
	if ( pad->start() ) { printf( "%s ", BTN0_ST ); atLeastOne = true; result = true; }
	if ( pad->bt1() )   { printf( "%s ", BTN1_ST ); atLeastOne = true; }
	if ( pad->bt2() )   { printf( "%s ", BTN2_ST ); atLeastOne = true; }
	
	if (atLeastOne) { printf( "\n" ); }
	
	return result;
}

// ==============================================

int main(int argc, char const *argv[]) {
	
	if ( !console.init() ) {
		printf("XtsConsole init FAILED !\n");
		return 1;
	}

    //int vol = snd.getVolume();
    //snd.volume(50); // 50%
    
    console.playMp3(22);

	console.cls();
	console.getScreen()->drawBPP( "/BLAST.BPP", 0, 0 );
	console.getScreen()->drawPCT( "/MECHS.PCT", 160, 90 );	// draw mecha sprite board
	console.getScreen()->drawRect( 160, 90, 160, 128, MODE_DRAW, CLR_GREEN ); // green border

	console.getScreen()->drawPCTSprite( "/MECHS.PCT", 10, 90, 32, 32, 5, 0 ); // draw small mecha
	console.getScreen()->drawPCTSprite( (char*)NULL, 10, 90+32+4, 64, 64, 5, 64 ); // draw big mecha

    console.getScreen()->drawPixel( 10, 10, rgb16(255, 0, 0) );
    console.getScreen()->drawPixel( 15, 10, rgb16(0, 255, 0) );
    console.getScreen()->drawPixel( 20, 10, rgb16(0, 0, 255) );

    console.getScreen()->drawRect( 15, 20, 50, 50, 1, rgb16(0, 255, 0) );
    
    console.getScreen()->drawLine( 0, 0, 320, 240, rgb16(255, 0, 0) );
    
    console.getScreen()->drawCircle( 160, 120, 60, MODE_FILL, rgb16(255, 0, 150) );
    console.getScreen()->drawCircle( 160, 120, 60, MODE_DRAW, rgb16(0, 255, 150) );
    
    console.getScreen()->drawTriangle(160-30, 120-30, 160+30, 120-30, 160, 120+30, MODE_DRAW, rgb16(0,0,255) );

	// screen.drawBPP( NULL, 0, 0 ); // that works !
	console.getScreen()->println("Hello World -= DEMO =- ! ~&#{}@");
	console.getScreen()->print(3.14f);

	while( true ) {
		if ( checkBtns() ) {
			break;
		}
		// printf("E\n");
		delay(50);
	}

	/*
	if ( gpioOK ) {
		gpio.digitalWrite(LED0_PIN, HIGH);
		while( gpio.digitalRead( MP3_PIN ) == LOW ) {
			if ( checkBtns() ) { break; }
			delay(100);
		}
		gpio.digitalWrite(LED0_PIN, LOW);
	
		while( !checkBtns() ) {
			delay(100);
		}
		
		snd.stop();
	}
	*/

    console.close();
printf("G\n");
    return 0;
}
