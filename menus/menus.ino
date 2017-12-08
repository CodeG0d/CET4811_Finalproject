struct Menu {
  char *myname;
  unsigned int len;
  Menu* parent;
  Menu* children;
};

Menu curmenu;
int selection;

boolean pUP = 1;
boolean pDN = 1;
boolean pC  = 1;
boolean pZ  = 1;

void setup() {
  init_menus();
  
  Serial.begin(115200);
  pinMode(A0, INPUT_PULLUP);  //UP
  pinMode(A1, INPUT_PULLUP);  //DN
  pinMode(A4, INPUT_PULLUP);  //CANCEL
  pinMode(A5, INPUT_PULLUP);  //ENTER
}

void loop() {
  menu_nav();
  pUP = digitalRead(A0);
  pDN = digitalRead(A1);
  pC  = digitalRead(A4);
  pZ  = digitalRead(A5);
  delay(100);
}

Menu menu_main;
Menu menu_main_items[4];
Menu menu_startlogging;
Menu menu_reviewlogs;
Menu menu_config;
  Menu menu_controller;
  Menu menu_tachometer;
  Menu menu_friction;
Menu menu_poweroff;




void init_menus(){
  create_menu(menu_startlogging, "Start Logging", menu_main, 0, NULL);
  create_menu(menu_reviewlogs, "Review Logs", menu_main, 0, NULL);
  create_menu(menu_config, "Configuration", menu_main, 3, NULL);
  create_menu(menu_poweroff, "Power Off", menu_main, 4, NULL);
  menu_main_items[0] = menu_startlogging;
  menu_main_items[1] = menu_reviewlogs;
  menu_main_items[2] = menu_config;
  menu_main_items[3] = menu_poweroff;
  create_menu(menu_main, "Main Menu", menu_main, 4, menu_main_items);
  curmenu = menu_main;
  selection = 0;
}

void create_menu(Menu &theMenu, char theName[], Menu &theParent, int theSize, Menu theChildren[]){
  theMenu.myname = theName;
  theMenu.parent = &theParent;
  theMenu.len = theSize;
  theMenu.children = theChildren;
}

void menu_nav(){  
  //Naviate menus C for cancel, Z for enter
  if(!digitalRead(A0) && pUP){
    selection = (selection+1) % curmenu.len;
    printMenu();
  }
  if(!digitalRead(A1) && pDN){
    selection = (selection-1) % curmenu.len;
    printMenu();
  }
  if(!digitalRead(A4) && pC){
    Serial.println("C");
  }
  if(!digitalRead(A5) && pZ){
    Serial.println("Z");
  }
}

void printMenu(){
  Serial.print(curmenu.myname);
  Serial.print(selection);
  Serial.print(" > ");
  //Menu submenu = menu_main_items.children[selection];
  Serial.println(menu_main_items[selection].myname);
}

