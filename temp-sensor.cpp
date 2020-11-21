// Include the libraries we need
#include "Arduino.h"
#include "temp-sensor.hpp"
#include "Wire.h"
#include "OneWire.h"

#define DS18B20_PIN 2

OneWire ds(DS18B20_PIN);

// maximum sensors on the bus
#define M 4

// actual sensors detected
byte m = 0;

// addresses
byte addr[M][8];

//temp for asynchronous reading
float temp[M];

//local prototypes
void show_id(byte m);

void setup_tempsense()
{
  m = 0;
  while (ds.search(addr[m]))
  {
    Serial.print("Found address ");
    Serial.print(m, DEC);
    Serial.print(":  ");
    show_id(m);
    Serial.println();
    if (OneWire::crc8(addr[m], 7) != addr[m][7])
    {
      Serial.println("CRC is not valid!");
      return;
    }
    if (addr[m][0] != 0x28)
    {
      Serial.println("Device is not a DS18B20 family device.");
      return;
    }
    m++;
  }

  Serial.println("No more addresses.");
  ds.reset_search();
}

void show_id(byte m)
{
  for (byte i = 6; i >= 1; i--)
  {
    Serial.print(addr[m][i] >> 4, HEX);
    Serial.print(addr[m][i] & 15, HEX);
  }
}

// asynchronous start conversion
int start_conversion(byte i)
{
  // The DallasTemperature library can do all this work for you!

  ds.reset();
  ds.select(addr[i]);
  ds.write(0x44); // start conversion, with parasite power on at the end
}

// asynchronous read result
int read_conversion_result(byte i)
{
  byte present = ds.reset();
  ds.select(addr[i]);
  ds.write(0xBE); // Read Scratchpad

  byte data[9];
  for (byte i = 0; i < 9; i++) // we need 9 bytes
  {
    data[i] = ds.read();
  }
  int temp = (data[1] << 8) | data[0]; // just want temperature
  return temp;
}

void tempSensorSetup(void)
{
  // start serial port
  Serial.println("Dallas Temperature IC Control Library Demo");

  setup_tempsense();

  for (byte i = 0; i < M; i++)
  {
    temp[i] = 0.0;
  }
}

float getTemp(char index)
{
  return temp[index];
}

/*
   Main function, calls the temperatures in a loop.
*/
int counter = 0;
int oldTime, actTime;

bool tempSensorLoop(void)
{

  //Call every 500ms
  actTime = millis();
  if (actTime - oldTime > 0)
  {
    oldTime = actTime + 500;

    // read all the results
    for (byte i = 0; i < m; i++)
    {
      int t = read_conversion_result(i);
      float centigrade = ((float)t) * 0.0625;
      temp[i] = centigrade;
    }

    // start all the conversions
    for (byte i = 0; i < m; i++)
    {
      start_conversion(i);
    }

    return true;
  }
  return false;
}

void serialOutTemperatureDev(void)
{
  counter++;
  Serial.println(counter);

  // read all the results
  for (byte i = 0; i < m; i++)
  {
    Serial.print("dev ");
    show_id(i);
    Serial.print(":  ");

    Serial.print(temp[i]);
    Serial.println("°C");
  }
  Serial.println();
}

void serialOutTemperatureCsv(void)
{
  counter++;
  Serial.print(counter);

  Serial.print(",");

  Serial.print(millis()/1000.0);

  // read all the results
  for (byte i = 0; i < m; i++)
  {
    Serial.print(",");
    show_id(i);

    Serial.print(",");
    Serial.print(temp[i]);
  }
  Serial.println();
}