//Code for menus

Menu curmenu;
int selection;

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

void init_menus() { //Create all the menus
  //Create config menu
  menu_config_items[0] = create_menu(menu_controller, "Setup Controller", menu_config, 0, NULL);
  menu_config_items[1] = create_menu(menu_tachometer, "Setup Tachometer", menu_config, 0, NULL);
  menu_config_items[2] = create_menu(menu_friction, "Setup Friction", menu_config, 0, NULL);
  //Create logging menu
  menu_logging_items[0] = create_menu(menu_startlogging, "Start Logging", menu_logging, 0, NULL);
  menu_logging_items[1] = create_menu(menu_reviewlogs, "Review Logs", menu_logging, 0, NULL);
  menu_logging_items[2] = create_menu(menu_clearlogs, "Clear Logs", menu_logging, 0, NULL);
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

Menu create_menu(Menu &theMenu, char theName[], Menu &theParent, int theSize, Menu theChildren[]) {
  theMenu.myname = theName;
  theMenu.parent = &theParent;
  theMenu.len = theSize;
  theMenu.children = theChildren;
  return (theMenu);
}

void menu_nav(char command) {
  //Navigate menus (use SF notation)

  switch (command) {
    case 'C':  //Cancel
      curmenu = *curmenu.parent;
      selection = 0;
      printMenu();
      break;
    case 'Z':  //Confirm
      if (curmenu.len == 0) {
        break;
      }
      curmenu = curmenu.children[selection];
      selection = 0;
      printMenu();
      break;
    case '8':  //UP
      if (curmenu.len == 0) {
        break;
      }
      selection = (selection + curmenu.len - 1) % curmenu.len;
      printMenu();
      break;
    case '2':  //DOWN
      if (curmenu.len == 0) {
        break;
      }
      selection = (selection + 1) % curmenu.len;
      printMenu();
      break;
    case '4':  //LEFT
      break;
    case '7':  //RIGHT
      break;
  }
}

void printMenu() {
  Serial.print(curmenu.myname);
  Serial.print(selection);
  Serial.print(" > ");
  Menu submenu = curmenu.children[selection];
  Serial.println(submenu.myname);
}

