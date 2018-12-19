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

#include <pthread.h>

#include "ArduinoGPIO.h"

extern void delay(int time);

GpioOverArduino::GpioOverArduino(Serial *serial) { this->serial = serial; }
GpioOverArduino::~GpioOverArduino() {}

#define KEY_USE_THREAD 1

#ifdef KEY_USE_THREAD
char _k_buffer[16 + 1 + 1]; //  +1 '\n' +1 '\0'

void *_xts_keyThread(void *argument)
{
    Serial *serial = (Serial *)argument;

    // static char buffer[16 + 1 + 1]; //  +1 '\n' +1 '\0'
    memset(_k_buffer, 0x00, 16 + 0 + 1);

    while (true)
    {
        // --------------------
        serial->writestr("SRM2"); // mode 2 (on demand)

        // TODO : lock Serial.write ....

        delay(80); // less time makes Serial Reading hanging
        // delay(60); // turbo mode works great w/ mario.lua
        int readed = serial->read(_k_buffer, 16 + 1);
        // printf("f:%d bytes read\n", readed);
        // printf("s:%s bytes read\n", buffer);

        if (readed != 16 + 1)
        {
            // printf("Oups %d \n", readed);
            // return NULL;
        }

        delay(5);

        // --------------------
        delay(10);
    }
}
#endif

bool GpioOverArduino::init(bool reset)
{

    // this->serial->writestr("SRM2"); // mode 2 (on demand)

    if (reset)
    {
        printf("Reseting Arduino...\n");
        this->serial->writestr("RST"); // RESET
        delay(3000);
    }

    char garbageFlushRX[128 + 1];
    int readed = this->serial->read(garbageFlushRX, 128);

    // 12 bytes
    // if (readed > 0) {
    this->ok = true;
    // }

    printf("-- %d bytes read\n", readed);
    if (readed > 0)
    {
        printf("-- %s bytes read\n", garbageFlushRX);
    }

#ifdef KEY_USE_THREAD
    pthread_t thread1;
    int i1 = pthread_create(&thread1, NULL, _xts_keyThread, (void *)this->serial);
#endif

    // return this->readAllPins() != NULL;
    return true;

    // this->serial->writestr("SRM0"); // mode 0 (coutinuous stream)
    // this->serial->writestr("SRC");  // SX Read Continue
    // return true;
}

void GpioOverArduino::close()
{
    this->ok = false;
    this->stop();
    this->serial->writestr("RST"); // RESET
    delay(300);
}

void GpioOverArduino::stop()
{
    this->serial->writestr("SRS"); // SX Read Stop
}

char *GpioOverArduino::readAllPins()
{

#ifdef KEY_USE_THREAD
    return _k_buffer;
#endif

    if (!this->ok)
    {
        return NULL;
    }

    static char buffer[16 + 1 + 1]; //  +1 '\n' +1 '\0'
    memset(buffer, 0x00, 16 + 0 + 1);

    this->serial->writestr("SRM2"); // mode 2 (on demand)

    // TODO : lock Serial.write ....

    delay(80); // less time makes Serial Reading hanging
    // delay(60); // turbo mode works great w/ mario.lua
    int readed = this->serial->read(buffer, 16 + 1);
    // printf("f:%d bytes read\n", readed);
    // printf("s:%s bytes read\n", buffer);

    if (readed != 16 + 1)
    {
        // printf("Oups %d \n", readed);
        return NULL;
    }

    delay(5);

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
    if (states == NULL)
    {
        return false;
    }
    static const int BTN0_PIN = 8; // INPUT_PULLUP
    if (pin < 0 || pin >= 16)
    {
        return false;
    }
    return states[pin] == '0';
}

bool GpioOverArduino::isMP3Playing(char *states)
{
    if (states == NULL)
    {
        return false;
    }
    static const int MP3_PIN = 8; // INPUT
    return states[MP3_PIN] == '0';
}

void GpioOverArduino::led(bool state)
{
    static const int LED0_PIN = 7;
    this->setOutputState(LED0_PIN, state);
}
