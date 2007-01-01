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

#include <sys/time.h>

#include "./XtsConsole.h"

// ==================================================

// ==================================================
static WiredScreen screen;

static Serial Serial1("/dev/ttyS2", 9600);
static SoundCard snd(&Serial1);

#ifndef NEW_SERIAL_GPIO
static auto gpio = SX1509();
#else
static auto gpio = GpioOverArduino(&Serial1);
#endif

static Pad pad = Pad();

static WiFi wifi = WiFi();

static Power pwr = Power();

// ==================================================

static bool _consoleINITED = false;

static bool _gpioOK = false;

bool Pad::left() { return this->_left; }
bool Pad::right() { return this->_right; }
bool Pad::up() { return this->_up; }
bool Pad::down() { return this->_down; }

bool Pad::bt1() { return this->_bt1; }
bool Pad::bt2() { return this->_bt2; }
bool Pad::start() { return this->_btStart; }

// #define PAD_TIME_CHECK 1

#ifdef PAD_TIME_CHECK
long long xts_lastTime = 0;
#endif

bool Pad::checkBtns()
{
	if (!_gpioOK)
	{
		return false;
	}

#ifdef NEW_SERIAL_GPIO
	char *banks = gpio.readAllPins();
	if (banks == NULL)
	{
		return false;
	}

	this->_btStart = gpio.isAButtonPressed(banks, BTN0_PIN);
	this->_bt1 = gpio.isAButtonPressed(banks, BTN1_PIN);
	this->_bt2 = gpio.isAButtonPressed(banks, BTN2_PIN);

	this->_up = gpio.isAButtonPressed(banks, DIR_UP_PIN);
	this->_left = gpio.isAButtonPressed(banks, DIR_LEFT_PIN);
	this->_right = gpio.isAButtonPressed(banks, DIR_RIGHT_PIN);
	this->_down = gpio.isAButtonPressed(banks, DIR_DOWN_PIN);

#else
#ifdef XTSCONSOLE

	uint8_t bankA = gpio.readBankA();

	this->_btStart = (bankA & (1 << BTN0_PIN)) == LOW;
	this->_bt1 = (bankA & (1 << BTN1_PIN)) == LOW;
	this->_bt2 = (bankA & (1 << BTN2_PIN)) == LOW;

	this->_up = (bankA & (1 << DIR_UP_PIN)) == LOW;
	this->_left = (bankA & (1 << DIR_LEFT_PIN)) == LOW;
	this->_right = (bankA & (1 << DIR_RIGHT_PIN)) == LOW;
	this->_down = (bankA & (1 << DIR_DOWN_PIN)) == LOW;

#else

	this->_btStart = gpio.digitalRead(BTN0_PIN) == LOW;
	this->_bt1 = gpio.digitalRead(BTN1_PIN) == LOW;
	this->_bt2 = gpio.digitalRead(BTN2_PIN) == LOW;

	this->_up = gpio.digitalRead(DIR_UP_PIN) == LOW;
	this->_left = gpio.digitalRead(DIR_LEFT_PIN) == LOW;
	this->_right = gpio.digitalRead(DIR_RIGHT_PIN) == LOW;
	this->_down = gpio.digitalRead(DIR_DOWN_PIN) == LOW;

#endif
#endif

	return true;
}

// =======================

SoundCard *XtsConsole::getSoundCard() { return &snd; }
WiredScreen *XtsConsole::getScreen() { return &screen; }
//SX1509      XtsConsole::getGPIO() { return gpio; }

Pad *XtsConsole::readPad()
{

#ifdef PAD_TIME_CHECK
	if (xts_lastTime == 0)
	{
		xts_lastTime = now();
	}

	long long xts_curTime = now();

	printf("pad ms : %lld \n", (xts_curTime - xts_lastTime));
	xts_lastTime = xts_curTime;
#endif

	pad.checkBtns();
	return &pad;
}
Pad *XtsConsole::getPad() { return &pad; }

Power *XtsConsole::getPowerManager() { return &pwr; }

bool XtsConsole::isInited() { return _consoleINITED; }


void __splash(bool start) {
	screen.cls();
	screen.drawPCT( "/BOOT.PCT", (320-160)/2, (240-128)/2 );
}

bool XtsConsole::init()
{
	
	screen.init();
	// -== Boot Splash ==-
	__splash(true);


	if (this->isLocked())
	{
		// need to re-init screen each time (arietta cf malloc / desktop cf WindowSDLPtr)
		// screen.init(); // done upper

#ifndef NEW_SERIAL_GPIO
		// // what to do for GPIO (on arrieta via I2C !!!!!) ????
		this->gpioOK = gpio.begin(0x3E) != 0;
#else
		this->gpioOK = gpio.init();
#endif
		_gpioOK = this->gpioOK;

		_consoleINITED = true;
		return true;
	}

	pwr.init(); // BEWARE !!!!!!!

	// screen.init(); // done upper

#ifndef NEW_SERIAL_GPIO
	this->gpioOK = gpio.begin(0x3E) != 0;
#else
	// Cf reset must first before Sound...
	this->gpioOK = gpio.init(true);
#endif
	_gpioOK = this->gpioOK;

	snd.init();
	snd.volume(45); // max 100

	if (this->gpioOK)
	{
#ifndef NEW_SERIAL_GPIO
		gpio.pinMode(DIR_UP_PIN, INPUT_PULLUP);
		gpio.pinMode(DIR_LEFT_PIN, INPUT_PULLUP);
		gpio.pinMode(DIR_RIGHT_PIN, INPUT_PULLUP);
		gpio.pinMode(DIR_DOWN_PIN, INPUT_PULLUP);

		gpio.pinMode(BTN0_PIN, INPUT_PULLUP);
		gpio.pinMode(BTN1_PIN, INPUT_PULLUP);
		gpio.pinMode(BTN2_PIN, INPUT_PULLUP);

		gpio.pinMode(MP3_PIN, INPUT);

		gpio.pinMode(LED0_PIN, OUTPUT);
		gpio.pinMode(LED1_PIN, OUTPUT);
		gpio.digitalWrite(LED0_PIN, LOW);
		gpio.digitalWrite(LED1_PIN, LOW);
#else
		gpio.setOutputState(LED0_PIN, false);
#endif
	}

	this->led(true);

	writeConsoleLockFile(CONSOLE_STATUS_STARTED);

	_consoleINITED = true;

	return true;
}

static void __xtsc_doClose(XtsConsole *console)
{
	// -== Halt Splash ==-
	__splash(false);
	
	console->getSoundCard()->stop();
	
	if (!console->isLocked())
	{
		console->getSoundCard()->close();

		console->led(false);
		//gpio.close();
	}
	console->getScreen()->close();
}

void XtsConsole::led(bool state)
{
	if (this->gpioOK)
	{
#ifndef NEW_SERIAL_GPIO
		gpio.digitalWrite(LED0_PIN, state ? HIGH : LOW);
#else
		gpio.setOutputState(LED0_PIN, state);
#endif
	}
}

// ===========================

void XtsConsole::close()
{
	__xtsc_doClose(this);
	pwr.exit();
}

void XtsConsole::shutdown()
{
	__xtsc_doClose(this);
	pwr.halt();
}
void XtsConsole::reset()
{
	__xtsc_doClose(this);
	pwr.reboot();
}

// ===========================

long long XtsConsole::now()
{
	struct timeval te;
	gettimeofday(&te, NULL);										 // get current time
	long long milliseconds = te.tv_sec * 1000LL + te.tv_usec / 1000; // calculate milliseconds
	// printf("milliseconds: %lld\n", milliseconds);
	return milliseconds;
}

void XtsConsole::delay(int time)
{
	::delay(time);
}

// ===========================

// all files outside /MP3 folder
bool XtsConsole::playMp3(char *track)
{
	snd.play(atoi(track));
	return true;
}
bool XtsConsole::playMp3(int track)
{
	snd.play(track);
	return true;
}
char *XtsConsole::getMp3TrackName() { return snd.getTrackName(); }

bool XtsConsole::stopMp3() { snd.stop(); }
bool XtsConsole::pauseMp3() { snd.pause(); }

// [0..100]
bool XtsConsole::volume(int volume)
{
	if (volume < 0 || volume > 100)
	{
		return false;
	}
	// snd.volume(volume * 100 / 30);
	snd.volume(volume);
	return true;
}
int XtsConsole::getVolume(int volume) { return snd.getVolume() /* * 100 / 30 */; }

void XtsConsole::cls() { screen.cls(); }

// ===========================

bool XtsConsole::startupWIFI() { return wifi.up(); }
bool XtsConsole::shutdownWIFI()
{
	wifi.down();
	return true;
}
bool XtsConsole::restartWIFI() { return wifi.restart(); }
bool XtsConsole::isOnWIFI() { return wifi.isConnected(); }
char *XtsConsole::getWIFIInfos() { return wifi.getInfos(); }
char *XtsConsole::getWIFIList() { return wifi.getList(); }
