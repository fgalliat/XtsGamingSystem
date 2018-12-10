#ifndef __GPIO_ARDUINO__
#define __GPIO_ARDUINO__ 1

#include "../../serial/Serial.h"

class GpioOverArduino
{
private:
  Serial *serial = NULL;
  bool ok = false;

public:
  GpioOverArduino(Serial *serial);
  ~GpioOverArduino();
  bool init();
  void close();
  void stop();
  char *readAllPins();
  void setOutputState(int pin, bool state);
  bool isAButtonPressed(char *states, int pin);
  bool isMP3Playing(char *states);
  void led(bool state);
};

#endif