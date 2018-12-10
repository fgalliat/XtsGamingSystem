/**
 * 
 * SX1509 module over Arduino
 * 
 * Xtase - fgalliat @ Dec 2018
 * 
 * default : 9600 bps
 */

#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "ArduinoGPIO.h"

extern void delay(int time);

GpioOverArduino::GpioOverArduino(Serial *serial) { this->serial = serial; }
GpioOverArduino::~GpioOverArduino() {}

bool GpioOverArduino::init()
{

    // this->serial->writestr("SRM2"); // mode 2 (on demand)
    this->serial->writestr("RST"); // RESET
    char garbageFlushRX[128 + 1];
    int readed = this->serial->read(garbageFlushRX, 128);

    return this->readAllPins() != NULL;

    // this->serial->writestr("SRM0"); // mode 0 (coutinuous stream)
    // this->serial->writestr("SRC");  // SX Read Continue
    // return true;
}

void GpioOverArduino::close()
{
    this->stop();
}

void GpioOverArduino::stop()
{
    this->serial->writestr("SRS"); // SX Read Stop
}

char *GpioOverArduino::readAllPins()
{
    this->serial->writestr("SRM2"); // mode 2 (on demand)

    // this->serial->read(....)  16+1 bytes to read (last is \n)
    char buffer[16 + 1 + 1]; // +1 '\n' +1 '\0'
    int readed = this->serial->read(buffer, 16 + 1);
    if (readed != 16 + 1)
    {
        return NULL;
    }
    buffer[16 + 1] = 0x00;
    return buffer;
}

void GpioOverArduino::setOutputState(int pin, bool state)
{
    // this->serial->writestr("SW01"); // SX Write <pin><state>
    static const char *ALPHAB = "0123456789ABCDEF";
    if (pin < 0 || pin >= strlen(ALPHAB))
    {
        return;
    }
    char pinCh = ALPHAB[pin];
    char cmd[4 + 1];
    sprintf(cmd, "SW%c%d", pinCh, state ? 1 : 0);
    this->serial->writestr(cmd);
}

// ===================---

bool GpioOverArduino::isAButtonPressed(char *states, int pin)
{
    static const int BTN0_PIN = 8; // INPUT_PULLUP
    if (pin < 0 || pin >= 16)
    {
        return false;
    }
    return states[pin] == '0';
}

bool GpioOverArduino::isMP3Playing(char *states)
{
    static const int MP3_PIN = 8; // INPUT
    return states[MP3_PIN] == '1';
}

void GpioOverArduino::led(bool state)
{
    static const int LED0_PIN = 7;
    this->setOutputState(LED0_PIN, state);
}
