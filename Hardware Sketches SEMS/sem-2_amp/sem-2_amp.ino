#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include "ACS712.h"

LiquidCrystal_I2C lcd(0x27,20,4);
ACS712 sensor(ACS712_30A, A1);
int x = 16;

void setup()
{
  lcd.init();                      // initialize the lcd 
  lcd.init();
  Serial.begin(9600);//baud rate at which arduino communicates with Laptop/PC
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

  sensor.calibrate();
}


void loop() //method to run the source code repeatedly
{
 float I = sensor.getCurrentDC();
  lcd.setCursor(2,0);
  // Send it to serial
  lcd.print(String("I = ") + I + " A");
  
  // Wait one second before the new cycle
  delay(500);
  lcd.clear();

}
