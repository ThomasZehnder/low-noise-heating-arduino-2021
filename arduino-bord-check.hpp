// Check if configured board in Arduino is correct.
// This project is for Arduino Mini Pro

// How to use: Comment out error line see line 29

#if defined(ARDUINO_AVR_UNO)
// Uno pin assignments
//Serial.println("ARDUINO_AVR_UNO");
#error Unsupported board selection. Stop compilation.

#elif defined(ARDUINO_AVR_NANO)
// NANO
//Serial.println("ARDUINO_AVR_NANO");
#error Unsupported board selection. Stop compilation.

#elif defined(ARDUINO_ESP8266_NODEMCU)
// ESP8266_NODEMCU
//Serial.println("ESP8266_NODEMCU");
#error Unsupported board selection. Stop compilation.

#elif defined(ARDUINO_ESP8266_ESP13)
// ESP8266_ESP13 not tested
//Serial.println("ARDUINO_ESP8266_ESP13");
#error Unsupported board selection. Stop compilation.

#elif defined(ARDUINO_AVR_PRO)
// ARDUINO_PRO
//Serial.println("ARDUINO_AVR_PRO");
//#error Unsupported board selection. Stop compilation.

#else
#error Unsupported board selection. Stop compilation.
#endif