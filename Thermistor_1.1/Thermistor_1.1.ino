int ThermistorPin = A5;
int Vo;
float R1 = 99800.0;
float logR2, R2, T;
float c1 = 0.0010285877883511835, c2 = 0.00023919823216667996, c3 = 1.5653681940557232e-7; //https://rusefi.com/Steinhart-Hart.html
#define NUMSAMPLES 5
int samples[NUMSAMPLES];

void setup() {
Serial.begin(9600);
pinMode(A0, INPUT); 
analogReference(EXTERNAL); // use AREF for reference voltage
}

void loop() {

  uint8_t i;
  float average;
 
  // take N samples in a row, with a slight delay
  for (i=0; i< NUMSAMPLES; i++) {
   samples[i] = analogRead(ThermistorPin);
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
}
