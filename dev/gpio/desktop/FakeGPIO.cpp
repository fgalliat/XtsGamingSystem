//#include <ncurses.h>
#include <SDL2/SDL.h>

#include "../sx1509/SparkFunSX1509.h"

// see screen
extern int pollKey();


void _s_close() {
    /*
    clrtoeol();
    refresh();
    endwin();
    */
}

SX1509::SX1509() {}
/*
SX1509::~SX1509() { _s_close(); }

void SX1509::close() {
    clrtoeol();
    refresh();
    endwin();
}
*/

byte SX1509::begin(byte address, byte resetPin) { init(NULL); }

byte SX1509::init(const char* device) {
    /*
    WINDOW *w = initscr();
    cbreak();
    noecho();
    nodelay(w, TRUE); // prevent getch() from blocking !!!!!!
    */

    return 1;
}



void SX1509::pinMode(byte pin, byte inOut) {}
void SX1509::digitalWrite(byte pin, byte highLow) {}

int __keys = 0;
int __keysCpt = 0;
byte SX1509::digitalRead(byte pin) {
    //return LOW; 
    
    if ( __keysCpt % 7 == 0 )
    __keys = pollKey();

         if ( pin == 0 && __keys == SDLK_UP ) { return LOW; }
    else if ( pin == 1 && __keys == SDLK_LEFT ) { return LOW; }
    else if ( pin == 2 && __keys == SDLK_RIGHT ) { return LOW; }
    else if ( pin == 3 && __keys == SDLK_DOWN ) { return LOW; }

    else if ( pin == 4 && __keys == SDLK_s ) { return LOW; }
    else if ( pin == 5 && __keys == SDLK_d ) { return LOW; }
    else if ( pin == 6 && __keys == SDLK_f ) { return LOW; }

    __keysCpt++;

    return HIGH; 
}

