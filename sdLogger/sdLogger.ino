//Writes to new file on reset

#include <SPI.h>
#include <SD.h>

File theFile;

int logCount = 0;

int PIN = A0;
boolean curState;
boolean preState;
unsigned int stateTime = 0;
unsigned long int preReading = 0;
unsigned long int preTrig = 0;

char fileExt[] = ".log";
char filePre[] = "LOG#";

void setup() {
  pinMode(PIN, INPUT_PULLUP);
  Serial.begin(9600);
  while (!Serial) { }

  initSD();
}

void loop() {
  //Log time of each falling edge
  logRotation();
}

void initSD() {
  //Function to initalize SD card
  if (!SD.begin(4)) {
    Serial.println("NO SD");
    return;
  }
  
  //Count up until new file
  while (SD.exists(String(logCount) + fileExt)) {
    logCount++;
  }
  
  //Create and write to file
  theFile = SD.open(String(logCount) + fileExt, FILE_WRITE);
  if (theFile) {
    theFile.println(filePre + String(logCount));
    theFile.close();
    Serial.println("Created" + String(filePre) + String(logCount));
  } else {
    Serial.println(filePre + String(logCount));
  }
  
  Serial.println("SD READY");
}

void logRotation(){
  //Record time of each rotation
  
  //Software debounce
  curState = digitalRead(PIN);
  if(millis() > preReading){
    if(curState != preState){
      stateTime += (millis()-preReading);
    }
    else if(stateTime > 0){
      stateTime -= (millis()-preReading);
    }
  }
  preReading = millis();
  
  //Assume switcing in 100ms to be contact bounce
  //(For 20 in wheel, 100ms = 35.7mph)
  if(stateTime > 100){
    stateTime = 0;
    preState = curState;
    //Record time on falling edge
    if(!curState){
      Serial.println(millis() - preTrig);
      theFile = SD.open(String(logCount) + fileExt, FILE_WRITE);
      if (theFile) {
        theFile.println(millis());
        theFile.close();
      }
      preTrig = millis();
    }
  }
}

