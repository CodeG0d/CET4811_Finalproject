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
int stateCount = 0;
unsigned long int pTrig = 0;

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
  delay(20);
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
  if(curState != preState){
    stateCount++;
  }
  else if(stateCount > 0){
    stateCount--;
  }

  if(stateCount > 5){
    stateCount = 0;
    preState = curState;
    //Record time on falling edge
    if(!curState){
      Serial.println(millis() - pTrig);
      theFile = SD.open(String(logCount) + ".log", FILE_WRITE);
      if (theFile) {
        theFile.println(millis());
        theFile.close();
      }
    }
    pTrig = millis();
  }

}

