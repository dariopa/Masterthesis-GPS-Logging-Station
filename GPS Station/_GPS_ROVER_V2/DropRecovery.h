#ifndef dr
#define dr

#if (ARDUINO>=100)
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <SD.h>

// Global variables
// A bit hacky, but needs to be instantiated as global variables, otherwise it won't work! Issue due to PROGMEM. 
const char UBLOX_INIT[] PROGMEM = {
  // Disable NMEA
  0xB5, 0x62, 0x06, 0x01, 0x08, 0x00, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x24, // GxGGA off
  0xB5, 0x62, 0x06, 0x01, 0x08, 0x00, 0xF0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x2B, // GxGLL off
  0xB5, 0x62, 0x06, 0x01, 0x08, 0x00, 0xF0, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x32, // GxGSA off
  0xB5, 0x62, 0x06, 0x01, 0x08, 0x00, 0xF0, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x39, // GxGSV off
  0xB5, 0x62, 0x06, 0x01, 0x08, 0x00, 0xF0, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x04, 0x40, // GxRMC off
  0xB5, 0x62, 0x06, 0x01, 0x08, 0x00, 0xF0, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x05, 0x47, // GxVTG off

  // Disable UBX
  0xB5, 0x62, 0x06, 0x01, 0x08, 0x00, 0x02, 0x15, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x26, 0x46, // RXM-RAWX off
  0xB5, 0x62, 0x06, 0x01, 0x08, 0x00, 0x02, 0x13, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x24, 0x38, // RXM-SFRBX off

  // Rate
  // 0xB5, 0x62, 0x06, 0x08, 0x06, 0x00, 0xE8, 0x03, 0x01, 0x00, 0x01, 0x00, 0x01, 0x39, //(1Hz)
  0xB5, 0x62, 0x06, 0x08, 0x06, 0x00, 0xD0, 0x07, 0x01, 0x00, 0x01, 0x00, 0xED, 0xBD, // (0.5Hz)
  // 0xB5, 0x62, 0x06, 0x08, 0x06, 0x00, 0xB8, 0x0B, 0x01, 0x00, 0x01, 0x00, 0xD9, 0x41, // (0.33Hz)
};

const char UBLOX_INIT_RAWX[] PROGMEM = {
  // Disable UBX
  0xB5, 0x62, 0x06, 0x01, 0x08, 0x00, 0x02, 0x15, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x26, 0x46, // RXM-RAWX off
  0xB5, 0x62, 0x06, 0x01, 0x08, 0x00, 0x02, 0x13, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x24, 0x38, // RXM-SFRBX off

  // Enable UBX
  0xB5, 0x62, 0x06, 0x01, 0x08, 0x00, 0x02, 0x15, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x27, 0x4B, // RXM-RAWX on
  0xB5, 0x62, 0x06, 0x01, 0x08, 0x00, 0x02, 0x13, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x25, 0x3D, // RXM-SFRBX on
};

// Classes
class SettingGPS {
  public:
    // Constructor
    SettingGPS();

    // Methods
    void GpsInit();
    void RawxConfig();
    // Variables
    int buffer_length;
};

class SettingSD {
  public:
    // Constructor
    SettingSD();

    // Methods
    void SdInit();
    void OpenFile(File dir);

    // Variables
    File bmsFile; // Declare file where BMS data will be written onto.
    File gpsFile; // Declare file where GPS data will be written onto.
    File root; // Declare root of store data.
};

class SettingBMS {
  public:
    // Constructor
    SettingBMS();

    // Methods
    float Temperature();
    float Voltage();

    // Variables
    float temperature; // Variable to store temperature value
    int analog_value; // Analog voltage value that Arduino reads
    float real_voltage; // Real measured voltage
    float MaxVoltageBattery; // Maximum voltage on battery when charged
    float MaxVoltageArduino; // Maximum voltage Arduino should read
    float LowVoltage; // Lowest acceptable voltage
    float Vpp; // Volts per point <-> accuracy of measurement
    float VoltageRatio; // Ratio to mathematically upscale voltage

};

class SettingTPL {
  public:
    // Contstructor
    SettingTPL();

    // Method
    void TPLInit();
    bool TPLMeasureTime(unsigned long current_time, unsigned long start_time, unsigned long measurment_time);
    void TPLToggle();

    // Variable
    unsigned long start_time;
    unsigned long current_time;
};


#endif
