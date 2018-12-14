/**
 * Xtase - fgalliat @Aug2018
 * SubSystem
 * Architecture definition
 */

#include "./serial/Serial.h"
#include "./sound/SoundCard.h"

#ifdef NEW_SERIAL_GPIO
#include "./gpio/arduino/ArduinoGPIO.h"
#else
#include "./gpio/sx1509/SparkFunSX1509.h"
#endif

#include "./screen/wiredSPI/WiredScreen.h"

#include "./wifi/Wifi.h"

#include "./pwr/Power.h"
