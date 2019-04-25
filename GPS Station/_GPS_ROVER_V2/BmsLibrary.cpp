#include "DropRecovery.h"
#include <OneWire.h>
#include <DallasTemperature.h>

SettingBMS::SettingBMS() {
  // Anything required when instantiating an object, goes here.
}

float SettingBMS::Bms() {

  // Temperature
  OneWire oneWire(5); // Setup a oneWire instance to communicate with any OneWire devices on pin 5 on Arduino Board (not just Maxim/Dallas temperature ICs)
  DallasTemperature sensors(&oneWire); // Pass oneWire reference to Dallas Temperature.
  sensors.begin(); // Start up the library. IC Default 9 bit.
  sensors.requestTemperatures(); // Send the command to get temperatures
  temperature = sensors.getTempCByIndex(0); // Read the temperature
  delay(5);

  // Voltage
  analog_value = analogRead(A0);
  real_voltage = (analog_value * Vpp) * VoltageRatio;
  delay(5);

  return temperature, real_voltage; // doesn't work like that, have to implement pointer
  
}
