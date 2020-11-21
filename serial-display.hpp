#ifndef serial_display_h
#define serial_display_h

#include <Wire.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiWire.h"

extern SSD1306AsciiWire display;

void displayInit(void);

void serialPlusOled(char *s);
void serialPlusOledDelayed(char *s);

void displayShowCommand(char  c);

bool displaySetting(char  c);

void displayShowTemperature(void);

#endif //serial_display_h
