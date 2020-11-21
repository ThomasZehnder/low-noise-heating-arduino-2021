#include "Arduino.h"
#include "low-noise-heater-defines.hpp"
#include "serial-led.hpp"
#include "serial-display.hpp"

char pinOutputs[4];
char selectedPinOutput = 0;

void ledInit(void)
{
  pinOutputs[0] = PIN_OUTPUT_0;
  pinOutputs[1] = PIN_OUTPUT_1;
  pinOutputs[2] = PIN_OUTPUT_2;
  pinOutputs[3] = PIN_OUTPUT_3;

  int i;
  // initialize digital pin LED_BUILTIN as an output.
  for (i = 0; i < 4; i++)
  {
    pinMode(pinOutputs[i], OUTPUT);
    digitalWrite(pinOutputs[i], LOW); // turn the LED off by making the voltage LOW

    // initial demo flashing
    ledPulse();
    selectedPinOutput = (1 + i) % 4;
  }
}

void ledPulse(void)
{
  digitalWrite(pinOutputs[selectedPinOutput], HIGH); // turn the LED on (HIGH is the voltage level)
  delay(100);                                        // wait
  digitalWrite(pinOutputs[selectedPinOutput], LOW);  // turn the LED on (HIGH is the voltage level)
  delay(100);
}


void ledCommand(char c)
{
if (c == 'o')
  {
    digitalWrite(pinOutputs[selectedPinOutput], HIGH); // turn the LED on (HIGH is the voltage level)
    serialPlusOled("o = off");
  }
  else if (c == 'x')
  {
    digitalWrite(pinOutputs[selectedPinOutput], LOW); // turn the LED on (HIGH is the voltage level)
    serialPlusOled("x = on");
  }
  else if (c == 'a')
  {
    analogWrite(pinOutputs[selectedPinOutput], 256/4); // 25%
    serialPlusOled("a = 25%");
  }  
  else if (c == 'b')
  {
    analogWrite(pinOutputs[selectedPinOutput], 256/2); // 50%
    serialPlusOled("b = 50%");
  }
    else if (c == 'c')
  {
    analogWrite(pinOutputs[selectedPinOutput], 256/4*3); // 75%
    serialPlusOled("c = 75%");
  }
  else if (c == 'p')
  {
    ledPulse();
    serialPlusOled("p = 100ms puls");
  }
  else if (c == 'd')
  {
    delay(100);
    serialPlusOled("d = 100ms delay");
  }
  else if (c == '0')
  {
    serialPlusOled("select led 0");
    selectedPinOutput = 0;
  }
  else if (c == '1')
  {
    serialPlusOled("select led 1");
    selectedPinOutput = 1;
  }
  else if (c == '2')
  {
    serialPlusOled("select led 2");
    selectedPinOutput = 2;
  }
  else if (c == '3')
  {
    serialPlusOled("select led 3");
    selectedPinOutput = 3;
  }
  else if (c == '\r')
  {
    //Serial.println(".r.\r");
  }
  else if (c == '\n')
  {
    ///Serial.println(".n.\n");
  }
  else
  {
    Serial.print("Command: ");
    Serial.print(c);
    Serial.print(",");
    Serial.print(c, HEX);
    Serial.println(" not implemented");
  }
}
