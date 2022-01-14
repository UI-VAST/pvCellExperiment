//setup ADC -> pyranometer
#include <Wire.h>
#include <Adafruit_ADS1X15.h>
Adafruit_ADS1115 ads1115; // Construct an ads1115 - ADC //0x48 default i2c address

//vars
int16_t results; //ADC
int16_t solar; //ADC

//setup iv chip
#include <Adafruit_INA260.h>
Adafruit_INA260 ina260 = Adafruit_INA260(); //0x40 i2c address

//Setup Thermistor
int thermistorPin = A2;
int Vo;
float R1 = 99800.0;
float logR2, R2, T;
float c1 = 0.0010285877883511835, c2 = 0.00023919823216667996, c3 = 1.5653681940557232e-7; //https://rusefi.com/Steinhart-Hart.html
#define NUMSAMPLES 5
int samples[NUMSAMPLES];

//sd card
String contents;
#include <SD.h>
 
File myFile;
String fName;
int randomNumber;
/*Connect the 5V pin to the 5V pin on the Arduino
Connect the GND pin to the GND pin on the Arduino
Connect CLK to pin 13 
Connect DO to pin 12 
Connect DI to pin 11 
Connect CS to pin 10 */

void setup() {
  //Setup thermistor
  pinMode(thermistorPin, INPUT); 
  

  // setup ADC
  Serial.begin(9600);
  // Wait until serial port is opened
  while (!Serial) { delay(10); }
  Serial.println("Hello!");
  
  //Serial.println("Getting differential reading from AIN0 (P) and AIN1 (N)");
  //Serial.println("ADC Range: +/- 0.512V  (1 bit = 0.015625mV)");
  ads1115.setGain(GAIN_EIGHT);      // 8x gain   +/- 0.512V  1 bit = 0.015625mV

  //check for sensors
  Serial.println("Checking for sensors");
  ads1115.begin();
  if (!ads1115.begin()) {
    Serial.println("Failed to initialize ADS.");
  }
  
  Serial.println("Found ads1115 chip");
  
  if (!ina260.begin()) {
    Serial.println("Couldn't find INA260 chip");
  }
  Serial.println("Found INA260 chip");

  //SD card
  Serial.print("Initializing SD card...");
  pinMode(10, OUTPUT);
  if (!SD.begin(10)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");
  //Set random seed for file name creation
  randomSeed(analogRead(A0)); // make sure to use unoccupied analog pin
  randomNumber = random(0,999);
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  //ADC RUN CODE
  //Serial.println("HERE");
  float multiplier = 0.015625; /* ADS1115  @ +/- 6.144V gain (16-bit results) */

  results = ads1115.readADC_Differential_0_1();
  solar = results * multiplier * 5;
  //Serial.print("Differential: "); Serial.print(solar); Serial.print("("); Serial.print(results * multiplier); Serial.println("mV)");

  delay(1000);

  //IV Chip run code
  //Serial.print("Current: ");
  //Serial.print(ina260.readCurrent());
  //Serial.println(" mA");

  //Serial.print("Bus Voltage: ");
  //Serial.print(ina260.readBusVoltage());
  //Serial.println(" mV");

  //Serial.println();
  delay(1000);
  T = pollThermistor();

  //write to sd card
  contents = String(millis()/1000) + "," + String(ina260.readBusVoltage()) + "," + String(ina260.readCurrent()) + "," + String(solar) + "," + String(T) ;
  Serial.println(contents);
  writeToFile();
  
}

float pollThermistor(){
  uint8_t i;
  float average;
 
  // take N samples in a row, with a slight delay
  for (i=0; i< NUMSAMPLES; i++) {
   samples[i] = analogRead(thermistorPin);
   delay(15);
  }
 
  // average all the samples out
  average = 0;
  for (i=0; i< NUMSAMPLES; i++) {
     average += samples[i];
  }
  Vo = average / NUMSAMPLES;

  
  R2 = R1 / (1023.0 / (float)Vo - 1.0);
  R2 = (R1 * Vo)/(1023.0-Vo);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
  T = T - 273.15;
  //T = (T * 9.0)/ 5.0 + 32.0; 

  Serial.print("Temperature: "); 
  Serial.print(T);
  Serial.println(" C"); 

  delay(1000);
  return T;
}

void writeToFile()
{
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  
  fName = String(abs(randomNumber)) + "_" + String(millis()/1000) + ".txt";
  
  Serial.print(fName);
  myFile = SD.open(fName, FILE_WRITE);
 
  // if the file opened okay, write to it:
  if (myFile) {
    Serial.print("Writing to file: ");
    myFile.println(contents);
  // close the file:
    myFile.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening file");
  }
  delay(2000);
}
