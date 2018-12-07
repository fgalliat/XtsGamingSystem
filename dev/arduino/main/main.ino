/*************************************************************
 * Xtase - fgalliat @Dec 2018
 * 
 * GPIO expander Manager
 * Because of wiring SX on AriettaG25 causes too much kernel errors
 * 
 * needs :
 * switch ON/OFF led {7}
 * read GameGear pad buttons (up,left,right,down, 1,2,Start) {0..6}
 * read DFPlayer "playing" line {8}
 * read new add. buttons [Start bis] & [Select] {9,10}
 * 5 lines free
 * 
 * TODOs :
 * 2x new buttons reading
 * may be DFPlayer driving .... (I/O cmds + GPIO line)
 * 
 * CMD set :
 * INF    - Infos
 * RST    - reset module & devices (only soft for now...)
 * SW70   - Switch Off GPIO-LED
 * SW71   - Switch On GPIO-LED
 * 
 * based on :
SparkFun SX1509 I/O Expander Example: digital in (digitalRead)
Jim Lindblom @ SparkFun Electronics
Original Creation Date: September 21, 2015
https://github.com/sparkfun/SparkFun_SX1509_Arduino_Library

Hardware Hookup:
	SX1509 Breakout ------ Arduino
	      GND -------------- GND
	      3V3 -------------- 3.3V
		  SDA ------------ SDA (A4)
		  SCL ------------ SCL (A5)

Development environment specifics:
	IDE: Arduino 1.8.7
	Hardware Platform: Arduino ProMini 328P 3.3v 8MHz
	SX1509 Breakout Version: v2.0

Distributed as-is; no warranty is given.
*************************************************************/

#define BUILTIN_LED 13

// SX1509 Pins:
#define SX_BTN0 0
#define SX_BTN1 1
#define SX_BTN2 2
#define SX_BTN3 3
#define SX_BTN4 4
#define SX_BTN5 5
#define SX_BTN6 6
#define SX_LED0 7
#define SX_MP30 8
#define SX_BTNA 9
#define SX_BTNB 10

// SX_BTNx are pull_up so these are pressed when '0'
// SX_LED1 is an output so seen as '0'
// [BANK A][BANK B]
// 1111101000000000 => here means Bt [2] pressed

#define UNDEFINED -1

const int pins[16][2] = {
    // mode | init state
    {INPUT_PULLUP, UNDEFINED}, // 0 - UP
    {INPUT_PULLUP, UNDEFINED}, // 1 - RIGHT
    {INPUT_PULLUP, UNDEFINED}, // 2 - LEFT
    {INPUT_PULLUP, UNDEFINED}, // 3 - DOWN
    {INPUT_PULLUP, UNDEFINED}, // 4 - START
    {INPUT_PULLUP, UNDEFINED}, // 5 - [2] ~~ not working very well / see soldering...
    {INPUT_PULLUP, UNDEFINED}, // 6 - [1]
    {OUTPUT, HIGH},            // 7 - LED 0
    {INPUT, UNDEFINED},        // 8 - DFPlayer usage
    {INPUT_PULLUP, UNDEFINED}, // 9 - BT A
    {INPUT_PULLUP, UNDEFINED}, // A - BT B
    {UNDEFINED, UNDEFINED},    // B - N/C
    {UNDEFINED, UNDEFINED},    // C - N/C
    {UNDEFINED, UNDEFINED},    // D - N/C
    {UNDEFINED, UNDEFINED},    // E - N/C
    {UNDEFINED, UNDEFINED},    // F - N/C
};

bool states[16];

const char *pinIDs = "0123456789ABCDEF";
int getPinID(char ch)
{
    for (int i = 0; i < 16; i++)
    {
        if (pinIDs[i] == ch)
        {
            return i;
        }
    }
    return -1;
}

#include <Wire.h>           // Include the I2C library (required)
#include <SparkFunSX1509.h> // Include SX1509 library

// SX1509 I2C address (set by ADDR1 and ADDR0 (00 by default):
const byte SX1509_ADDRESS = 0x3E; // SX1509 I2C address
SX1509 io;                        // Create an SX1509 object to be used throughout

// -==================-
bool OK_SX1509 = false;
bool OK_DFPLAY = false;
// -==================-
#define MODE_NO_PROXY 0
#define MODE_SMARTKEY_PROXY 1
#define MODE_SERIAL_PROXY 2
int serialMode = MODE_NO_PROXY;
// -==================-

// builtin led
void bled(bool state)
{
    digitalWrite(BUILTIN_LED, state ? HIGH : LOW);
}

void bblink(int times = 5, int finalState = false, int blinkPeriod = 100)
{
    for (int i = 0; i < times; i++)
    {
        bled(true);
        delay(blinkPeriod);
        bled(false);
        delay(blinkPeriod);
    }
    bled(finalState);
}

// -==================-
void (*resetAVR)(void) = 0; //declare reset function @ address 0

void resetAll()
{
    // stop MP3 playback
    resetAVR();
}
// -==================-

void setup()
{
    // -=== Internal Peripherals ===-
    pinMode(BUILTIN_LED, OUTPUT);
    bled(false);

    Serial.begin(9600);

    // -=== GPIO Peripheral ===-
    OK_SX1509 = false;
    bled(true);
    if (!io.begin(SX1509_ADDRESS))
    {
        // bled(true);
        // Serial.println("Failed to communicate.");
        bblink(5);
    }
    else
    {
        OK_SX1509 = true;
        bled(false);
        // Serial.println("Able to communicate.");

        int mode, state;
        for (int i = 0; i < 16; i++)
        {
            mode = pins[i][0];
            state = pins[i][1];

            if (mode != UNDEFINED)
            {
                io.pinMode(i, mode);
                if (state != UNDEFINED)
                {
                    io.digitalWrite(i, state);
                }
            }
        }
    } // end of SX OK
}

void loop()
{

    if (OK_SX1509 && serialMode == MODE_NO_PROXY)
    {
        // @ least one state has changed
        bool atLeastOne = false;
        bool curOne;

        for (int i = 0; i < 16; i++)
        {
            // read pin per pin instead full BANK ! ;(
            curOne = io.digitalRead(i) == HIGH;
            if (states[i] != curOne)
            {
                // do not store if its an OUTPUT
                if (i != SX_LED0)
                {
                    atLeastOne = true;
                }
            }
            states[i] = curOne;
        }

        if (atLeastOne)
        {
            for (int i = 0; i < 16; i++)
            {
                Serial.print(states[i] ? '1' : '0');
            }
            Serial.println();
        }
    } // end of SX iteration

    // -=== main Serial loop iteration ===-
    if (Serial.available() > 0)
    {
        if (serialMode == MODE_NO_PROXY)
        {
            // regular mode
            static char cmd[3];
            int readed = Serial.readBytes(cmd, 3);
            if (readed == 3)
            {
                if (cmd[0] == 'S' && OK_SX1509)
                {
                    // SX1509 cmd
                    if (cmd[1] == 'W')
                    {
                        // SWF0 -> SX Write pin#F(15) to 0(LOW)
                        int pin = getPinID(cmd[2]);

                        int pinVal = Serial.read() == '0' ? 0 : 1;

                        if (pin > -1)
                        {
                            int mode = pins[pin][0];
                            if (!(mode == INPUT || mode == INPUT_PULLUP))
                            {
                                io.digitalWrite(pin, pinVal ? HIGH : LOW);
                            }
                        }
                    }
                }
                else if (cmd[0] == 'M')
                {
                    // DFPlayer cmd
                    Serial.println("# MP3 commands not yet supported");
                }
                else if (cmd[0] == 'D')
                {
                    // other Serial dummy cmd (SmartKey or full proxy)
                    Serial.println("# DUMMY commands not yet supported");
                }
                else if (cmd[0] == 'R')
                {
                    if (strncmp(cmd, "RST", 3) == 0)
                    {
                        Serial.println("# Reseting");
                        delay(300);
                        resetAll();
                    }
                }
                else if (cmd[0] == 'I')
                {
                    if (strncmp(cmd, "INF", 3) == 0)
                    {
                        Serial.println("# -= Devices Diagnostic =-");
                        Serial.print("# SX1509   ");
                        Serial.println(OK_SX1509 ? "OK" : "NOK");
                        Serial.print("# DFPlayer ");
                        Serial.println(OK_DFPLAY ? "OK" : "NOK");
                        Serial.println("# -EOF-");
                    }
                }
            }
        }
    }

    delay(5);
}