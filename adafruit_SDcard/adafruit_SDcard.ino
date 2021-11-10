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
 
void setup()
{
  Serial.begin(9600);
  Serial.print("Initializing SD card...");
  // On the Ethernet Shield, CS is pin 4. It's set as an output by default.
  // Note that even if it's not used as the CS pin, the hardware SS pin 
  // (10 on most Arduino boards, 53 on the Mega) must be left as an output 
  // or the SD library functions will not work. 
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
 
void loop()
{
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  
  fName = String(abs(randomNumber)) + "_" + String(millis()/1000) + ".txt";
  //fName = "Testaroo.txt";
  Serial.print(fName);
  myFile = SD.open(fName, FILE_WRITE);
 
  // if the file opened okay, write to it:
  if (myFile) {
    Serial.print("Writing to file: ");
    myFile.println("testing 1, 2, 3.");
  // close the file:
    myFile.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening file");
  }
  delay(2000);
}
