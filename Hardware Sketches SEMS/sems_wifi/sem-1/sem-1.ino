#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);
int x = 16;
int d = 16;
void setup()
{
  lcd.init();                      // initialize the lcd 
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  while(x != 0){
    lcd.clear();
    lcd.setCursor(x,0);
    lcd.print("Live Efficent");
    lcd.setCursor(x,1);
    lcd.print(" with S.E.M.S");
    x--;
    delay(200);
       }
   delay(2000);
  lcd.clear();
}


void loop()
{
   lcd.setCursor(3,0);
   lcd.print("Volt = 224 ");
   lcd.setCursor(3,1);
   lcd.print("amps = 3.2");
}
