#include <WiiChuck.h>
#include <Wire.h>

//SDA A4
//SCL A5

Nunchuck nunchuck(SDA, SCL);
int aX;
int aY;
int aZ;
byte data[] = {0,0,0,0,0,0,0x00,0x0A};

void setup() {

  Serial.begin(115200);
  Serial.println("Starting WiiChuck Generic Controller Demo");

  nunchuck.begin();
}


void loop() {
  delay(50);
  nunchuck.readData();   // Read inputs and update maps
  
  nunchuck.printInputs(Serial); // Print all inputs
  
  aX = nunchuck.getAccelX();
  aY = nunchuck.getAccelY();
  aZ = nunchuck.getAccelZ();

  data[0] = (byte)(aX>>8 & 0x00FF);
  data[1] = (byte)(aX    & 0x00FF);
  data[2] = (byte)(aY>>8 & 0x00FF);
  data[3] = (byte)(aY    & 0x00FF);
  data[4] = (byte)(aZ>>8 & 0x00FF);
  data[5] = (byte)(aZ    & 0x00FF);
  data[6] = 0xFF;
  data[7] = 0x00;

  //Serial.print(aX);
  //Serial.print('\t');
  //Serial.print(aY);
  //Serial.print('\t');
  //Serial.print(aZ);
  //Serial.print('\n');
  //Serial.write(data,8);
  
}
