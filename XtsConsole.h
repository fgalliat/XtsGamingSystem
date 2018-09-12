#ifndef _XTS_CONSOLE_H_
#define _XTS_CONSOLE_H_ 1

/**
 * 
 * XtsConsole.cpp
 * 
 * Xtase Game Console main API
 * 
 * Xtase - fgalliat @Aug 2018
 * 
 **/

// main architecture settings file
#include "dev/arch.h"

 class Pad {
  private:
    bool _left  = false;
    bool _right = false;
    bool _up    = false;
    bool _down  = false;
    
    bool _bt1 = false;
    bool _bt2 = false;
    bool _btStart = false;
    
  public:
    Pad() {}
    ~Pad() {}
    
    bool left();
    bool right();
    bool up();
    bool down();
    
    bool bt1();
    bool bt2();
    bool start();
    
    bool checkBtns();
};

// ========================================================

#define DIR_UP_PIN     0x00
#define DIR_LEFT_PIN   0x01
#define DIR_RIGHT_PIN  0x02
#define DIR_DOWN_PIN   0x03


#define BTN0_PIN  0x04
#define BTN1_PIN  0x05
#define BTN2_PIN  0x06

#define LED0_PIN  0x07

#define MP3_PIN   0x08

#define LED1_PIN  0x09



class XtsConsole {
  private:
	bool gpioOK = true;

  public:
    XtsConsole() {}
    ~XtsConsole() {}
    
    bool isInited();

    bool init();
    void close();
    
    void shutdown();
    void reset();
    
    SoundCard*   getSoundCard();
    WiredScreen* getScreen();
    // SX1509      getGPIO();
    
    Pad*         readPad();
    Pad*         getPad();

    Power* getPowerManager();
    
    // ===========================
    
    bool  playMp3(char* track);
    bool  playMp3(int track);
    char* getMp3TrackName();
    
    bool stopMp3();
    bool pauseMp3();
    
    // [0..100]
    bool volume(int volume);
    int  getVolume(int volume);
    
    void cls();
    void led(bool state);
    
    // ===========================
    
    // make a WIFI class too !!
    
    bool  startupWIFI()  ;
    bool  shutdownWIFI() ;
    bool  restartWIFI()  ;
    bool  isOnWIFI()     ;
    char* getWIFIInfos()     ;
    char* getWIFIList()      ;
};



#endif