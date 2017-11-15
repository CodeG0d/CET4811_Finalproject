//Writes to new file on reset

#include <SPI.h>
#include <SD.h>

File theFile;
SdVolume volume;
SdFile root;

int logCount = 0;

int PIN = A0;
boolean curState;
boolean preState;
unsigned int stateCount = 0;
unsigned long int preReading = 0;
unsigned long int preTrig = 0;

void setup() {
  pinMode(PIN, INPUT_PULLUP);
  Serial.begin(9600);
  while (!Serial) { }

  initSD();

  //Count up until new file
  while (SD.exists(String(logCount) + ".log")) {
    logCount++;
  }
  
  //Create and write to file
  theFile = SD.open(String(logCount) + ".log", FILE_WRITE);
  if (theFile) {
    Serial.println("Creating Log#" + String(logCount));
    theFile.println("Log#" + String(logCount));
    theFile.close();
    Serial.println("Done!");
  } else {
    Serial.println("Log#" + String(logCount));
  }
}

void loop() {
  //Log time of each falling edge
  logRotation();
}

void initSD() {
  //Function to initalize SD card
  Serial.print("Initializing SD card...");
  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");
}

void logRotation(){
  //Record time of each rotation
  
  //Software debounce
  curState = digitalRead(PIN);
  if(millis() > preReading){
    if(curState != preState){
      stateCount += (millis()-preReading);
    }
    else if(stateCount > 0){
      stateCount -= (millis()-preReading);
    }
  }
  preReading = millis();
  //Assume switcing in 100ms to be contact bounce
  //(For 20 in wheel, 100ms = 35.7mph)
  if(stateCount > 100){
    stateCount = 0;
    preState = curState;
    //Record time on falling edge
    if(!curState){
      Serial.println(millis() - preTrig);
      theFile = SD.open(String(logCount) + ".log", FILE_WRITE);
      if (theFile) {
        theFile.println(millis());
        theFile.close();
      }
      preTrig = millis();
    }
  }
}

