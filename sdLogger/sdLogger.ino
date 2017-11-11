//Writes to new file on reset

#include <SPI.h>
#include <SD.h>

File theFile;
SdVolume volume;
SdFile root;

int logCount = 0;

int PIN = A0;
boolean pinState;

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
  if (pinState && !digitalRead(PIN)) {
    Serial.println("Pressed!");
    theFile = SD.open(String(logCount) + ".log", FILE_WRITE);
    if (theFile) {
      theFile.println(millis());
      theFile.close();
    }
  }
  pinState = digitalRead(PIN);
  delay(50);
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

