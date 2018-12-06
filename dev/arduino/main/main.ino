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
 * output message coding
 * input for led (...)
 * may be DFPlayer driving .... (I/O cmds)
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
// SX_LED1 is an output so seen as '0' (or inv. logic ?)
// [BANK A][BANK B]
// 1111101000000000 => here means Bt [2] pressed

// BT0 UP
// BT1 RIGHT
// BT2 LEFT
// BT3 DOWN
// BT4 START
// BT5 [2] ~~ not working very well / see soldering...
// BT6 [1]

#include <Wire.h>           // Include the I2C library (required)
#include <SparkFunSX1509.h> // Include SX1509 library

// SX1509 I2C address (set by ADDR1 and ADDR0 (00 by default):
const byte SX1509_ADDRESS = 0x3E; // SX1509 I2C address
SX1509 io;                        // Create an SX1509 object to be used throughout

void setup()
{
    pinMode(BUILTIN_LED, OUTPUT);
    digitalWrite(BUILTIN_LED, LOW);

    Serial.begin(9600);

    Serial.println("begin...");

    if (!io.begin(SX1509_ADDRESS))
    {
        digitalWrite(BUILTIN_LED, HIGH);
        Serial.println("Failed to communicate.");
        while (1)
            ;
    }

    Serial.println("Able to communicate.");

    io.pinMode(SX_LED0, OUTPUT);
    io.digitalWrite(SX_LED0, HIGH);

    io.pinMode(SX_BTN0, INPUT_PULLUP);
    io.pinMode(SX_BTN1, INPUT_PULLUP);
    io.pinMode(SX_BTN2, INPUT_PULLUP);
    io.pinMode(SX_BTN3, INPUT_PULLUP);
    io.pinMode(SX_BTN4, INPUT_PULLUP);
    io.pinMode(SX_BTN5, INPUT_PULLUP);
    io.pinMode(SX_BTN6, INPUT_PULLUP);
}

bool states[16];

void loop()
{

    // static bool states[16];
    // @ least one state has changed
    bool atLeastOne = false;
    bool curOne;

    for (int i = 0; i < 16; i++)
    {
        curOne = io.digitalRead(i) == HIGH; // read pin per pin instead full BANK !
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

    delay(5);
}