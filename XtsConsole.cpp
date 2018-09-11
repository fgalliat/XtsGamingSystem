/**
 * 
 * XtsConsole.cpp
 * 
 * Xtase Game Console main API
 * 
 * Xtase - fgalliat @Aug 2018
 * 
 **/
 

#include <errno.h>
#include <fcntl.h> 
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>



#include "./XtsConsole.h"

// ==================================================


// ==================================================
static WiredScreen screen;

static Serial Serial1("/dev/ttyS2", 9600);
static SoundCard snd( &Serial1 );

static auto gpio = SX1509();


static Pad pad = Pad();

static WiFi wifi = WiFi();

// ==================================================

static bool _consoleINITED = false;

static bool _gpioOK = false;

bool Pad::left()   { return this->_left; }
bool Pad::right()  { return this->_right; }
bool Pad::up()     { return this->_up; }
bool Pad::down()   { return this->_down; }

bool Pad::bt1()    { return this->_bt1; }
bool Pad::bt2()    { return this->_bt2; }
bool Pad::start()  { return this->_btStart; }

bool Pad::checkBtns()  { 
	if ( !_gpioOK ) { return false; }
	
	this->_btStart = gpio.digitalRead( BTN0_PIN ) == LOW;
	this->_bt1 = gpio.digitalRead( BTN1_PIN ) == LOW;
	this->_bt2 = gpio.digitalRead( BTN2_PIN ) == LOW;
	
	this->_up    = gpio.digitalRead( DIR_UP_PIN ) == LOW;
	this->_left  = gpio.digitalRead( DIR_LEFT_PIN ) == LOW;
	this->_right = gpio.digitalRead( DIR_RIGHT_PIN ) == LOW;
	this->_down  = gpio.digitalRead( DIR_DOWN_PIN ) == LOW;
	
	return true;
}

// =======================

    SoundCard*   XtsConsole::getSoundCard() { return &snd; }
    WiredScreen* XtsConsole::getScreen() { return &screen; }
    //SX1509      XtsConsole::getGPIO() { return gpio; }
    
    Pad*         XtsConsole::readPad() { pad.checkBtns(); return &pad; }
    Pad*         XtsConsole::getPad() { return &pad; }


	bool XtsConsole::isInited() { return _consoleINITED; }

    bool XtsConsole::init() {
    	screen.init();
    	
    	snd.init();
    	snd.volume(20); // max 30
    	
    	this->gpioOK = gpio.begin(0x3E) != 0;
    	_gpioOK = this->gpioOK;
    	
    	if ( this->gpioOK ) {
    		gpio.pinMode( DIR_UP_PIN,    INPUT_PULLUP );
			gpio.pinMode( DIR_LEFT_PIN,  INPUT_PULLUP );
			gpio.pinMode( DIR_RIGHT_PIN, INPUT_PULLUP );
			gpio.pinMode( DIR_DOWN_PIN,  INPUT_PULLUP );
			
			gpio.pinMode( BTN0_PIN, INPUT_PULLUP );
			gpio.pinMode( BTN1_PIN, INPUT_PULLUP );
			gpio.pinMode( BTN2_PIN, INPUT_PULLUP );
			
			gpio.pinMode( MP3_PIN, INPUT );
			
			gpio.pinMode( LED0_PIN, OUTPUT ); gpio.pinMode( LED1_PIN, OUTPUT );
			gpio.digitalWrite(LED0_PIN, LOW); gpio.digitalWrite(LED1_PIN, LOW);
    	}
    	
    	this->led(true);
    	
		_consoleINITED = true;

    	return true;
    }
    
    void XtsConsole::led(bool state) {
    	if ( this->gpioOK ) {
    		gpio.digitalWrite(LED0_PIN, state ? HIGH : LOW);
    	}
    }
    
    
    void XtsConsole::close() {
    	snd.close();
    	
    	this->led(false);
    	//gpio.close();
    	
    	screen.close();
    	
    	exit(0); // ??
    }
    
    void XtsConsole::shutdown() { printf("-SHUTDOWN-\n"); }
    void XtsConsole::reset()    { printf("-REBOOT-\n"); }
    

    
    // ===========================

	// all files outside /MP3 folder     
    bool  XtsConsole::playMp3(char* track) { snd.play( atoi(track) ); return true; }
    bool  XtsConsole::playMp3(int track)   { snd.play(track); return true; }
    char* XtsConsole::getMp3TrackName()    { return snd.getTrackName(); }
    
    bool XtsConsole::stopMp3()  { snd.stop(); }
    bool XtsConsole::pauseMp3() { snd.pause(); }
    
    // [0..100]
    bool XtsConsole::volume(int volume)   { if ( volume < 0 || volume > 100 ) { return false; } snd.volume( volume * 100 / 30 ); return true; }
    int XtsConsole::getVolume(int volume) { return snd.getVolume() * 100 / 30; }
    
    void XtsConsole::cls() { screen.cls(); }
    
    // ===========================
    
    // make a WIFI class too !!
    
    bool  XtsConsole::startupWIFI()  { return wifi.up(); }
    bool  XtsConsole::shutdownWIFI() { wifi.down(); return true; }
    bool  XtsConsole::restartWIFI()  { return wifi.restart(); }
    bool  XtsConsole::isOnWIFI()     { return wifi.isConnected(); }
    char* XtsConsole::getWIFIInfos()     { return wifi.getInfos(); }
    char* XtsConsole::getWIFIList()      { return wifi.getList(); }


