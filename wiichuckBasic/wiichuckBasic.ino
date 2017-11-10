#include <WiiChuck.h>
#include <Wire.h>

//SDA A4
//SCL A5

Nunchuck nunchuck(SDA, SCL);
int aX;
int aY;
int aZ;

int jX;
int jY;

int jXmin = 128;
int jXmax = 128;
int jYmin = 128;
int jYmax = 128;
int jThresh = 33;
int jPos = 5;
int pjPos = 5;

int dat[] = {5, 5, 5};

byte data[] = {0,0,0,0,0,0,0x00,0x0A};

void setup() {

  Serial.begin(115200);
  Serial.println("Starting WiiChuck Generic Controller Demo");

  nunchuck.begin();
}


void loop() {
  delay(50);
  nunchuck.readData();   // Read inputs and update maps
  
  //nunchuck.printInputs(Serial); // Print all inputs
  
  aX = nunchuck.getAccelX();
  aY = nunchuck.getAccelY();
  aZ = nunchuck.getAccelZ();

  calibrateDeadzone();
  calcJ();
  if(jPos != pjPos){
    Serial.println(jPos);
    dat[0] = dat[1];
    dat[1] = dat[2];
    dat[2] = jPos;
    if(dat[0] == 2 && dat[1] == 3 && dat[2] == 6){
      Serial.println("HADOKEN!");
    }
  }
  pjPos = jPos;
  
//  //Write accelerometer data to Serial port
//  data[0] = (byte)(aX>>8 & 0x00FF);
//  data[1] = (byte)(aX    & 0x00FF);
//  data[2] = (byte)(aY>>8 & 0x00FF);
//  data[3] = (byte)(aY    & 0x00FF);
//  data[4] = (byte)(aZ>>8 & 0x00FF);
//  data[5] = (byte)(aZ    & 0x00FF);
//  data[6] = 0xFF;
//  data[7] = 0x00;
//  Serial.print(aX);
//  Serial.print('\t');
//  Serial.print(aY);
//  Serial.print('\t');
//  Serial.print(aZ);
//  Serial.print('\n');
//  Serial.write(data,8);
  
}

void calibrateDeadzone(){
  if(jX < jXmin){
    jXmin = jX;
  }
  if(jX > jXmax){
    jXmax = jX;
  }
  if(jY < jYmin){
    jYmin = jY;
  }
  if(jY > jYmax){
    jYmax = jY;
  }
}

int calcJ(){
  //Calculate and return joystick postion
  // 7 8 9
  // 4 5 7
  // 1 2 3
  jPos = 5;
  
  jX = nunchuck.getJoyX();
  jY = nunchuck.getJoyY();
  int jXtemp = map(jX,jXmin, jXmax, -100, 100);
  int jYtemp = map(jY,jYmin, jYmax, -100, 100);
  
  if(jXtemp > jThresh){
    jPos += 1;
  }
  if(jXtemp < -jThresh){
    jPos -= 1;
  }
  if(jYtemp > jThresh){
    jPos += 3;
  }
  if(jYtemp < -jThresh){
    jPos -= 3;
  }

  return jPos;
}

