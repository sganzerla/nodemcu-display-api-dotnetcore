#include <LiquidCrystal.h>

#define RS D2
#define EN D3
#define d4 D5
#define d5 D6
#define d6 D7
#define d7 D8

LiquidCrystal lcd(RS, EN, d4, d5, d6, d7);

void setup() {
                         // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
                      // Print a message to the LCD.
  lcd.print("hello, world!");
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd.print(millis() / 1000);
}
