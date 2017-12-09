#include <WiiChuck.h>
#include <Wire.h>

Nunchuck nunchuck(SDA, SCL);

struct Menu {
  char *myname;
  unsigned int len;
  Menu* parent;
  Menu* children;
};

void setup() {
  init_menus();
  nunchuck.begin();
  Serial.begin(115200);
  
}

void loop() {
  calibrateDeadzone();
  nunchuck.readData();
  char stick = calcJ();
  if (stick != '0') {
    menu_nav(stick);
  }
  if(buttonZclick()){
    menu_nav('Z');
  }
  if(buttonCclick()){
    menu_nav('C');
  }
  delay(50);
}
