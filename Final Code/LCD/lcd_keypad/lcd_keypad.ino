//Code: 
#include <LiquidCrystal.h>
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);//RS,EN,D4,D5,D6,D7
#include <Keypad.h>//header for keypad commands enabling
const byte ROWS = 4; // Four rows
const byte COLS = 4; // Three columns
// Define the Keymap
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
// Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.
byte rowPins[ROWS] = { 22, 24, 26, 28 };
// Connect keypad COL0, COL1 and COL2 to these Arduino pins.
byte colPins[COLS] = { 30, 32, 34, 36 };
//  Create the Keypad
Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
void setup()
{
  for(int k=8;k<14;k++)
  {
    pinMode(k,OUTPUT);//pins 8-14 are enabled as output
  }
  lcd.begin(16, 2);//initializing LCD
}
void loop()
{
  char key = kpd.getKey(); //storing pressed key value in a char
  if (key != NO_KEY)
{
      lcd.print(key); //showing pressed character on LCD
  }
}                
