//Writes to new file on reset

#include <SPI.h>
#include <SD.h>

File theFile;

int logCount = 0;

float bikeSpeed;
float wheelRaidus = 10;
float TAU = 6.283185307;


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
  
  //Assume switcing within 50ms to be contact bounce
  //(For 20 in wheel, 50ms = 71.4mph)
  if(stateTime > 50){
    stateTime = 0;
    preState = curState;
    //Record time on falling edge
    if(!curState){
      //Print speed
      unsigned long int t = millis() - preTrig;
      //Calculate Speed
      bikeSpeed = TAU*wheelRaidus/t * 3600000.0/63360.0;
      Serial.print(bikeSpeed);
      Serial.print("\t");
      Serial.println(t);
      theFile = SD.open(String(logCount) + fileExt, FILE_WRITE);
      if (theFile) {
        theFile.println(millis());
        theFile.close();
      }
      preTrig = millis();
    }
  }
}

