#include "ACS712.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

ACS712 sensor(ACS712_30A, A1);
LiquidCrystal_I2C lcd(0x27,20,4); 

void setup() {
  lcd.init();
  lcd.init();
  lcd.backlight();
  lcd.setCursor(3,0);
 
  
  Serial.begin(9600);
  sensor.calibrate();
}

void loop() {
  float sens = (sensor.getCurrentDC()/1023)*5000;
  float I = ((sens/1000)-2500)/66;
  Serial.println(I);
  lcd.setCursor(0,0);
  lcd.print(I);
  

  delay(1000);
}
