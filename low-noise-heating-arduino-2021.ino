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

char pinOutputs[4];
char selectedPinOutput = 0;

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
  pinOutputs[0] = LED_BUILTIN;
  pinOutputs[1] = 5;
  pinOutputs[2] = 6;
  pinOutputs[3] = 7;
  pinKey[0] = 11; //D11;
  pinKey[1] = 12; //D12;

  // SCL to arduino pin A5
  // SDA to arduino pin A4

#if defined(ARDUINO_AVR_UNO)
  // Uno pin assignments
  //serialPlusOled("ARDUINO_AVR_UNO");
  #error Unsupported board selection. Stop compilation.

#elif defined(ARDUINO_AVR_NANO)
  // NANO
  //serialPlusOled("ARDUINO_AVR_NANO");
  #error Unsupported board selection. Stop compilation.



#elif defined(ARDUINO_ESP8266_NODEMCU)
  // ESP8266_NODEMCU
  //serialPlusOled("ESP8266_NODEMCU");
  #error Unsupported board selection. Stop compilation.


#elif defined(ARDUINO_ESP8266_ESP13)
  // ESP8266_ESP13 not tested
  //serialPlusOled("ARDUINO_ESP8266_ESP13");
  #error Unsupported board selection. Stop compilation.

#elif defined(ARDUINO_AVR_PRO)
  // ARDUINO_PRO
  serialPlusOled("ARDUINO_AVR_PRO");

  pinOutputs[0] = LED_BUILTIN;
  pinOutputs[1] = 10;
  pinOutputs[2] = 11;
  pinOutputs[3] = 12;
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

void loop()
{
  keyEdgeDetect(serialToOledOn);

  //true if new conversion was started
  if (tempSensorLoop())
  {

    serialOutTemperatureCsv();

    displayShowTemperature();
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
