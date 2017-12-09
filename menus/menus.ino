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
Menu menu_main_items[3];
  Menu menu_logging;
  Menu menu_logging_items[3];
    Menu menu_startlogging;
    Menu menu_reviewlogs;
    Menu menu_clearlogs;
  Menu menu_config;
  Menu menu_config_items[3];
    Menu menu_controller;
    Menu menu_tachometer;
    Menu menu_friction;
  Menu menu_poweroff;

void init_menus(){//Create all the menus
  //Create config menu
  menu_config_items[0] = create_menu(menu_controller, "Setup Controller", menu_config, 0, NULL);
  menu_config_items[1] = create_menu(menu_tachometer, "Setup Tachometer", menu_config, 0, NULL);
  menu_config_items[2] = create_menu(menu_friction, "Setup Friction", menu_config, 0, NULL);
  //Create logging menu
  menu_logging_items[0] = create_menu(menu_startlogging, "Start Logging", menu_main, 0, NULL);
  menu_logging_items[1] = create_menu(menu_reviewlogs, "Review Logs", menu_main, 0, NULL);
  menu_logging_items[2] = create_menu(menu_clearlogs, "Clear Logs", menu_main, 0, NULL);
  //Create main menu
  menu_main_items[0] = create_menu(menu_logging, "Logging", menu_main, 3, menu_logging_items);
  menu_main_items[1] = create_menu(menu_config, "Configuration", menu_main, 3, menu_config_items);
  menu_main_items[2] = create_menu(menu_poweroff, "Power Off", menu_main, 0, NULL);
  menu_main = create_menu(menu_main, "Main Menu", menu_main, 3, menu_main_items);
  //inital state
  curmenu = menu_logging;
  selection = 0;
  printMenu();
}

Menu create_menu(Menu &theMenu, char theName[], Menu &theParent, int theSize, Menu theChildren[]){
  theMenu.myname = theName;
  theMenu.parent = &theParent;
  theMenu.len = theSize;
  theMenu.children = theChildren;
  return(theMenu);
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
    curmenu = *curmenu.parent;
    selection = 0;
    printMenu();
  }
  if(!digitalRead(A5) && pZ){
    Serial.println("Z");
    curmenu = curmenu.children[selection];
    selection = 0;
    printMenu();
  }
}

void printMenu(){
  Serial.print(curmenu.myname);
  Serial.print(selection);
  Serial.print(" > ");
  Menu submenu = curmenu.children[selection];
  Serial.println(submenu.myname);
}

