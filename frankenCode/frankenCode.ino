//setup ADC -> pyranometer
#include <Wire.h>
#include <Adafruit_ADS1X15.h>
Adafruit_ADS1115 ads1115; // Construct an ads1115 - ADC //0x48 default i2c address

//setup iv chip
#include <Adafruit_INA260.h>
Adafruit_INA260 ina260 = Adafruit_INA260(); //0x40 i2c address

//vars
int16_t results; //ADC

void setup() {
  // setup ADC
  Serial.begin(9600);
  // Wait until serial port is opened
  while (!Serial) { delay(10); }
  Serial.println("Hello!");
  
  //Serial.println("Getting differential reading from AIN0 (P) and AIN1 (N)");
  //Serial.println("ADC Range: +/- 0.512V  (1 bit = 0.015625mV)");
  ads1115.setGain(GAIN_EIGHT);      // 8x gain   +/- 0.512V  1 bit = 0.015625mV

  //check for sensors
  if (!ads1115.begin()) {
    Serial.println("Failed to initialize ADS.");
    while (1);
  }
  Serial.println("Found ads1115 chip");
  
  if (!ina260.begin()) {
    Serial.println("Couldn't find INA260 chip");
    while (1);
  }
  Serial.println("Found INA260 chip");
  

}

void loop() {
  // put your main code here, to run repeatedly:
  //ADC RUN CODE
  float multiplier = 0.015625; /* ADS1115  @ +/- 6.144V gain (16-bit results) */

  results = ads1115.readADC_Differential_0_1();

  Serial.print("Differential: "); Serial.print(results); Serial.print("("); Serial.print(results * multiplier); Serial.println("mV)");

  delay(1000);

  //IV Chip run code
  Serial.print("Current: ");
  Serial.print(ina260.readCurrent());
  Serial.println(" mA");

  Serial.print("Bus Voltage: ");
  Serial.print(ina260.readBusVoltage());
  Serial.println(" mV");

  Serial.print("Power: ");
  Serial.print(ina260.readPower());
  Serial.println(" mW");

  Serial.println();
  delay(1000);
}
