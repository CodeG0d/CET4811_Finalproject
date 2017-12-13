#include <Adafruit_LiquidCrystal.h>
//Create lcd object
//Data
//Clock
//Latch
Adafruit_LiquidCrystal lcd(12,13,5);

void init_lcd() {
  Serial.begin(115200);

  // set up the LCD's number of rows and columns: 
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("hello, world!");
}


void lcd_print() {

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
