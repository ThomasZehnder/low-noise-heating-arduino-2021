#include "Arduino.h"
#include "low-noise-heater-defines.hpp"
#include "serial-display.hpp"
#include "temp-sensor.hpp"

SSD1306AsciiWire display;

// SCL to arduino pin A5 
// SDA to arduino pin A4

void displaySetup(void) {
  Wire.begin();
  Wire.setClock(400000L);
  display.begin(&Adafruit128x64, I2C_ADDRESS);
  display.setScrollMode(SCROLL_MODE_AUTO);

  display.setFont(fixed_bold10x15);
  display.clear();
  display.println("LOW Noise");



  display.setFont(System5x7);
  display.println(String("Heater V")+VERSION);

  
  display.print("Build: ");
  display.println(__DATE__);
  display.print("     / ");
  display.println(__TIME__);
  display.setFont(System5x7);
}

void serialPlusOled(char *s)
{
  Serial.println(s);
  display.println(s);
}

void serialPlusOledDelayed(char *s)
{
  serialPlusOled(s);
  delay(50);
}


void displayShowCommand(char c)
{
  if (c != '\n') //avoid unnecessary line for LF
  {
    display.print("Command: ");
    display.print((int)c);
    display.print(" > ");
    display.println(c);
  }
}

bool displaySetting(char  c)
{
  if (c == '#')
  {
    display.setFont(fixed_bold10x15);
    return true;
  }
  else if (c == '|')
  {
    display.setFont(System5x7);
    return true;
  }
  else if (c == '&')
  {
    display.clear();
    return true;
  }  
  else if (c == '\\')
  {
    display.println("");
    return true;
  }
  return false;
}

int x = 120;

void displayShowTemperature(void)
{
      x++;
     // https://github.com/greiman/SSD1306Ascii/blob/master/doc/MainPage/SSD1306mainpage.h
    display.setCursor(64, 0);
    display.print(x);

    
    display.setFont(lcdnums12x16); // https://github.com/greiman/SSD1306Ascii/blob/master/doc/MainPage/SSD1306mainpage.h
    display.setCursor(0, 2);
    display.print(getTemp(0));
    display.setCursor(72, 2);
    display.setFont(lcd5x7);
    display.print("o");
    display.setFont(fixed_bold10x15);
    display.print("C");
    
    display.setFont(fixed_bold10x15); // https://github.com/greiman/SSD1306Ascii/blob/master/doc/MainPage/SSD1306mainpage.h
    display.setCursor(0, 4);
    display.print(getTemp(1));
    display.setFont(Callibri11);
    display.setCursor(72, 4);
    display.setFont(lcd5x7);
    display.print("o");
    display.setFont(fixed_bold10x15);
    display.print("C");
}