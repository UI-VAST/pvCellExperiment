#include <Wire.h>
#include <Adafruit_ADS1X15.h>

Adafruit_ADS1115 ads1115; // Construct an ads1115 - ADC //0x48 default i2c address

void setup(void)
{
  Serial.begin(9600);
  Serial.println("Hello!");
  
  Serial.println("Getting differential reading from AIN0 (P) and AIN1 (N)");
  Serial.println("ADC Range: +/- 0.512V  (1 bit = 0.015625mV)");
  ads1115.setGain(GAIN_EIGHT);      // 8x gain   +/- 0.512V  1 bit = 0.015625mV
  
  if (!ads1115.begin()) {
    Serial.println("Failed to initialize ADS.");
    while (1);
  }

  //ads1115.begin(0x49);  // Initialize ads1115 at address 0x49
}

void loop(void)
{
  int16_t results;

  /* Be sure to update this value based on the IC and the gain settings! */
  
  float multiplier = 0.015625; /* ADS1115  @ +/- 6.144V gain (16-bit results) */

  results = ads1115.readADC_Differential_0_1();

  Serial.print("Differential: "); Serial.print(results); Serial.print("("); Serial.print(results * multiplier); Serial.println("mV)");

  delay(1000);
}
