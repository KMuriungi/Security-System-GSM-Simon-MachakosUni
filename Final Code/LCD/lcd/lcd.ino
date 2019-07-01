#include<LiquidCrystal.h>  // Including LCD Library
LiquidCrystal lcd(9, 8, 14,15, 16, 17);


byte heart[8] = // Designing the HEART Symbol ( Initialize the Function)
{
  0b00000,
  0b01010,
  0b11111,
  0b11111,
  0b11111,
  0b01110,
  0b00100,
  0b00000
};

void setup()
{
  
  lcd.begin(16,2);
  lcd.createChar(1, heart); // Initializing the Symbol Creation Function in LCD
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.write(1);lcd.write(1);lcd.write(1);
  lcd.print(" System ");
  lcd.write(1);lcd.write(1);lcd.write(1);
  lcd.setCursor(0,1);
  lcd.write(1);lcd.write(1);
  lcd.print(" Ready ");
  lcd.write(1);lcd.write(1);
  
  delay(1000);
}

void loop()
  {
    lcd.setCursor(0,0);
  lcd.write(1);lcd.write(1);
  lcd.print("System Ready");
   lcd.write(1);lcd.write(1);
    lcd.setCursor(0, 1);
    lcd.write(1);
    delay(1000);
    lcd.setCursor(1, 1);
    lcd.write(1);
    delay(1000);
    lcd.setCursor(2, 1);
    lcd.write(1);
    delay(1000);
    lcd.setCursor(3, 1);
    lcd.write(1);
    delay(1000);
    lcd.setCursor(4, 1);
    lcd.write(1);
    delay(1000);
    lcd.setCursor(5, 1);
    lcd.write(1);
    delay(1000);
    lcd.setCursor(6, 1);
    lcd.write(1);
    delay(1000);
    lcd.setCursor(7, 1);
    lcd.write(1);
    delay(1000);
    lcd.setCursor(8, 1);
    lcd.write(1);
    delay(1000);
    lcd.setCursor(9, 1);
    lcd.write(1);
    delay(1000);
    lcd.setCursor(10, 1);
    lcd.write(1);
    delay(1000);
    lcd.setCursor(11, 1);
    lcd.write(1);
    delay(1000);
    lcd.setCursor(12, 1);
    lcd.write(1);
    delay(1000);
    lcd.setCursor(13, 1);
    lcd.write(1);
    delay(1000);
    lcd.setCursor(14, 1);
    lcd.write(1);
    delay(1000);
    lcd.setCursor(15, 1);
    lcd.write(1);
    delay(1000);
    lcd.setCursor(0,1);
    lcd.clear();
  }
