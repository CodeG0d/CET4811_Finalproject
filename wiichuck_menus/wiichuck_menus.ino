//Demo for navigating menus with nunchuck
//Results are printed to serial monitor
//
//  Stick UP - Navigate UP
//  Stick DN - Navigate DOWN
//         Z - Confirm
//         C - Cancel

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
  printMenu();
}

void loop() {
  calibrateDeadzone();
  nunchuck.readData();

  //Send commands to navigate menus
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
