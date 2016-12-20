// SPI and SD libraries. SPI for connecting SD card to SPI bus. Not sure if we'll use this.
#include <SPI.h>
#include <SD.h>
const int sdPin = 4;
 
// Tare a sensor pin. In this case, temperature
const int temPin = 0;
 
// Delay time between sensor readings in milliseconds
const int delayTime = 5000;
 
// File variable
File tempFile;
 
 
void setup() {
  // Serial output for when connected to computer
  Serial.begin(9600); // I think we're using 9600, not sure
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
 
  Serial.print("Initializing SD card...");
  if(!SD.begin(sdPin)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("Initialization done.");
 
  tempsFile = SD.open("index.html", FILE_WRITE);
 
  if (tempsFile) {
    Serial.println("Printing temperatures");
    tempsFile.println("Printing temperatures:");
    tempsFile.close();
    Serial.println("Done.");
  } else {
    Serial.println("Error opening file in setup.");
  }
 
}
 
void loop() {
  /********************/
  // Open SD card for writing
  tempsFile = SD.open("temps.txt", FILE_WRITE);
 
  if (tempsFile) {
    // Temperature readings
    float voltage, degreesC, degreesF;
    voltage = getVoltage(temPin);
    degreesC = (voltage - 0.5) * 100.0;
    degreesF = degreesC * (9.0/5.0) + 32.0;
 
    // write temps to Serial
    Serial.print("Celsius: ");
    Serial.print(degreesC);
 
    // write temps to SD card
    tempsFile.print("Celsius: ");
    tempsFile.print(degreesC);
 
    // close the file
    tempsFile.close();
  } else {
    Serial.println("Error opening file in loop.");
  }
 
 
  delay(delayTime);
 
}
 
float getVoltage(int pin)
{
  return (analogRead(pin) * 0.004882814);
}
