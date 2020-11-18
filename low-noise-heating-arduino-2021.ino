/*
  low-noise-heating-arduino-2021
  V1.00


  Switch on build in LED with serial input 115200 Baud:
  0,1,2,3 = select led, command is modal
  o = off
  x = on
  p = 100ms puls
  f = flash sequence 10 times fast


*/

#include "serial-help.hpp"
#include "serial-key.hpp"
#include "serial-display.hpp"
#include "serial-led.hpp"
#include "temp-sensor.hpp"

char c = 0;

char pinArray[4];
char selectetPin = 0;

bool serialToOledOn = false;

bool valKey[2];
bool valKey_old[2];
int pinKey[2];

void setup()
{
  // setup OLED display
  displaySetup();

  // initialize serial: baud rate fix to 115200, B&R PLC works with USB support and FRM- Library, other baud rates are not supported.

  Serial.begin(115200);
  Serial.println("################################################################");
  Serial.println(" Serial Interface to Led's, OLED Display and Keys (115200 Baud )");
  Serial.println("################################################################");
  Serial.print(__DATE__);
  Serial.print(" / ");
  Serial.println(__TIME__);

  //Default settings IO mapping
  pinArray[0] = LED_BUILTIN;
  pinArray[1] = 5;
  pinArray[2] = 6;
  pinArray[3] = 7;
  pinKey[0] = 11; //D11;
  pinKey[1] = 12; //D12;

  // SCL to arduino pin A5
  // SDA to arduino pin A4

#if defined(ARDUINO_AVR_UNO)
  // Uno pin assignments
  serialPlusOled("ARDUINO_AVR_UNO");
  #error Unsupported board selection. Stop compilation.

#elif defined(ARDUINO_AVR_NANO)
  // NANO
  serialPlusOled("ARDUINO_AVR_NANO");
  #error Unsupported board selection. Stop compilation.



#elif defined(ARDUINO_ESP8266_NODEMCU)
  // ESP8266_NODEMCU
  serialPlusOled("ESP8266_NODEMCU");
  #error Unsupported board selection. Stop compilation.


#elif defined(ARDUINO_ESP8266_ESP13)
  // ESP8266_ESP13 not tested
  serialPlusOled("ARDUINO_ESP8266_ESP13");
  #error Unsupported board selection. Stop compilation.

#elif defined(ARDUINO_AVR_PRO)
  // ARDUINO_PRO
  serialPlusOled("ARDUINO_AVR_PRO");

  pinArray[0] = LED_BUILTIN;
  pinArray[1] = 10;
  pinArray[2] = 11;
  pinArray[3] = 12;
  pinKey[0] = 8; //D11;
  pinKey[1] = 9; //D12;


#else
#error Unsupported board selection. Stop compilation.
#endif

  // initialize leds
  ledInit();

  // initialize keys
  keyInit();

  tempSensorSetup();

  //INTRO Help (also accessable with \h)
  Serial.println("###############################################################");
  help();
  Serial.println("###############################################################");

  display.clear();
  
}
int x = 120;

void loop()
{
  keyEdgeDetect(serialToOledOn);

  //true if new conversion was started
  if (tempSensorLoop())
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



  // share the wait
  delay (50) ;

  // if there's any serial available, read it:
  while (Serial.available() > 0)
  {
    // look wait on input
    c = Serial.read();

    if (c == '^')
    {
      serialToOledOn = false;
      Serial.println("@ send off to OLED");
      display.setFont(System5x7);
    }

    else if (c == '@')
    {
      serialToOledOn = true;
      Serial.println("@ send character to OLED without interpretating until \\");
    }

    else if (displaySetting(c))
    {
      // if char is consumed return Value is true
    }

    else if (serialToOledOn)
    {
      display.print(c);
    }

    else
    {

      displayShowCommand(c);

      if (c == 'h')
      {
        help();
      }
      else
      {
        ledCommand(c);
      }
    }
  }
}
