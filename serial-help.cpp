#include "Arduino.h"
#include "serial-display.hpp"
#include "serial-key.hpp"

void help()
{
  int additionalDelay = 0;
  while (keyPressed(0)) {additionalDelay=2000;}; // wait on key0
  while (keyPressed(1)) {additionalDelay=2000;}; // wait on key1
  serialPlusOledDelayed("Out Commands");
  serialPlusOledDelayed("x,o = off/on");
  serialPlusOledDelayed("d = 100ms delay");
  serialPlusOledDelayed("p = 100ms puls");
  serialPlusOledDelayed("a,b,c = 25%,50%,75% on");
  serialPlusOledDelayed("0..3 = select output (modal)");
  serialPlusOledDelayed("h = this help");
  
  delay(1000+additionalDelay);
  
  while (keyPressed(0)) {}; // wait on key0
  while (keyPressed(1)) {}; // wait on key1
  serialPlusOledDelayed("Display Commands");
  serialPlusOledDelayed("^ = switch to led command");
  serialPlusOledDelayed("@ = switch to oled output");
  serialPlusOledDelayed("# = big font");
  serialPlusOledDelayed("| = small font");
  serialPlusOledDelayed("& = clear display");
  serialPlusOledDelayed("\\ = new line");
  
  delay(1000+additionalDelay);

}
