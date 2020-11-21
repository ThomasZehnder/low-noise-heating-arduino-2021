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
#include "arduino-bord-check.hpp"
#include "low-noise-heater-defines.hpp"
#include "serial-help.hpp"
#include "serial-key.hpp"
#include "serial-display.hpp"
#include "serial-led.hpp"
#include "temp-sensor.hpp"

char c = 0;

bool serialToOledOn = false;

char operationMode = 'A';

void setup()
{
  // setup OLED display 
  // SCL to arduino pin A5
  // SDA to arduino pin A4
  displayInit();

  // initialize serial: baud rate fix to 115200
  serialInit(115200);


  // initialize led's
  ledInit();

  // initialize keys
  keyInit();

  // initialize temeratue sensors
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

    if (operationMode == OM_TEMPMESSUREMENT)
    {
      serialOutTemperatureCsv();
    }
    else
    {
      serialOutTemperatureDev();
    }

    displayShowTemperature();
  }

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
