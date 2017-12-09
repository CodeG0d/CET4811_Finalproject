//Code for wii nunchuck

//SDA A4
//SCL A5


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
char jPos = 5;
char pjPos = 5;

boolean buttZ;
boolean buttC;
boolean pButtZ;
boolean pButtC;

void init_nunchuck() {
  nunchuck.begin();
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

char calcJ(){
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
  
  jPos += '0';

  //Return '0' if no change
  if(jPos == pjPos){
    pjPos = jPos;
    return('0');
  }
  
  pjPos = jPos;
  return(jPos);
}

boolean buttonZclick(){
  //Return true when Z is pressed
  buttZ = nunchuck.checkButtonZ();
  if(pButtZ == buttZ){
    pButtZ = buttZ;
    return(false);
  }
  pButtZ = buttZ;
  return(buttZ);
}

boolean buttonCclick(){
  //Return true when Z is pressed
  buttC = nunchuck.checkButtonC();
  if(pButtC == buttC){
    pButtC = buttC;
    return(false);
  }
  pButtC = buttC;
  return(buttC);
}

