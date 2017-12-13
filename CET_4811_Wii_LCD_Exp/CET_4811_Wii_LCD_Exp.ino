#include <WiiChuck.h>
#include <Wire.h>

#include <Adafruit_LiquidCrystal.h>

Adafruit_LiquidCrystal lcd(0);

void setup() {
  Serial.begin(115200);

  // set up the LCD's number of rows and columns: 
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("hello, world!");
}


void loop() {

  delay(50);

    // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd.print(millis()/1000);

  //lcd.setBacklight(HIGH);
  //delay(500);
  //lcd.setBacklight(LOW);
  //delay(500);
}
