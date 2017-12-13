rm #include <WiiChuck.h>
#include <Wire.h>

#include "Adafruit_LiquidCrystal.h"
Adafruit_LiquidCrystal lcd(0);

#if defined(ARDUINO_ARCH_ESP8266)
#define SDA D2
#define SCL D1
#endif
// This works with the Guitar Hero World Tour (Wii) Drums

Classic classic(SDA, SCL);

void setup() {


  Serial.begin(115200);
  Serial.println("Starting WiiChuck Generic Controller Demo");

  classic.begin();

  classic.addMap(new Classic::joyXLeft(D5,200,128,10)); // Servo max zero min cooldown
                                                           // cooldown: hold value for x ms.
                                                           
  classic.addMap(new Classic::joyXLeft(D6,200,128,10)); // Servo max zero min cooldown
                                                           // cooldown: hold value for x ms.                                                           
  classic.printMaps(Serial);

  // set up the LCD's number of rows and columns: 
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("hello, world!");
}


void loop() {

  classic.readData();   // Read inputs and update maps
  classic.printInputs(Serial); // Print all inputs
  
  delay(50);

    // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd.print(millis()/1000);

  lcd.setBacklight(HIGH);
  delay(500);
  lcd.setBacklight(LOW);
  delay(500);
}
