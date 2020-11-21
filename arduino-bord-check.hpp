// Check if configured board in Arduino is correct.
// This project is for Arduino Mini Pro 

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