//Writes to new file on reset

#include <SPI.h>
#include <SD.h>

File theFile;
SdVolume volume;
SdFile root;

int logCount = 0;

void setup() {
  Serial.begin(9600);
  while (!Serial) { }

  initSD();

  while(SD.exists(String(logCount) + ".log")){
    logCount++;
  }

  theFile = SD.open(String(logCount) + ".log", FILE_WRITE);
  if (theFile) {
    Serial.print("Creating Log" + logCount);
    theFile.println("Log#" + String(logCount));
    theFile.close();
    Serial.println("Done!");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }  
  
}

void loop() {
  
}

void initSD(){
  //Function to initalize SD card
  Serial.print("Initializing SD card...");
  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");
}

