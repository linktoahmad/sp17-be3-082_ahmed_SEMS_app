#include <WiFiManager.h> 
#include <DoubleResetDetector.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <PZEM004Tv30.h>
#include <FirebaseArduino.h>


#define FIREBASE_HOST "sems-6fa94.firebaseio.com"
#define FIREBASE_AUTH "je45PSiFWO2eMYnqAyGc6e8p6gAuJAhc3pERfppk"

#define DRD_TIMEOUT 10
#define DRD_ADDRESS 0

DoubleResetDetector drd(DRD_TIMEOUT, DRD_ADDRESS);
LiquidCrystal_I2C lcd(0x27, 16, 2);
PZEM004Tv30 pzem(D5, D6);

void setup() {
  WiFiManager wifiManager;
  Serial.begin(115200);
  lcd.begin(16,2);
  lcd.init();
  lcd.backlight();
  Serial.begin(115200);


   lcd.print("Welcome SEMS");
   delay(500);
   lcd.clear();
   
   if (drd.detectDoubleReset()) {
    lcd.print("Reset Detected");
    delay(500);
    lcd.clear();
    wifiManager.resetSettings();
    lcd.print("connect to sems");
    lcd.setCursor(0,1);
    lcd.print("goto boards.io");
    delay(500);
    wifiManager.autoConnect("SEMS ioT Meter");
    lcd.print("SEMS Connected!");
    delay(500);
    lcd.clear();
  } else {
    wifiManager.autoConnect("SEMS ioT Meter");      
    lcd.print("SEMS Connected!");
    delay(500);
    lcd.clear();
  }

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}


void loop() {
 
    float voltage = pzem.voltage();
    if( !isnan(voltage) ){
        Firebase.setFloat("/sems006/volt", voltage);
    } else {
        Serial.println("Error reading voltage");
    }

    float current = pzem.current();
    if( !isnan(current) ){
        Firebase.setFloat("/sems006/amps", current);
    } else {
        Serial.println("Error reading current");
    }

    float power = pzem.power();
    if( !isnan(power) ){
        Firebase.setFloat("/sems006/watt", power);
    } else {
        Serial.println("Error reading power");
    }

    float energy = pzem.energy();
    if( !isnan(energy) ){
        Firebase.setFloat("/sems006/unit", energy);
    } else {
        Serial.println("Error reading energy");
    }

   /* float frequency = pzem.frequency();
    if( !isnan(frequency) ){
        Serial.print("Frequency: "); Serial.print(frequency, 1); Serial.println("Hz");
    } else {
        Serial.println("Error reading frequency");
    }

    float pf = pzem.pf();
    if( !isnan(pf) ){
        Serial.print("PF: "); Serial.println(pf);
    } else {
        Serial.println("Error reading power factor");
    }
    */

    lcd.clear();
    lcd.print("V:");lcd.print(voltage);lcd.print(" A:");lcd.print(current);
    lcd.setCursor(0,1);
    lcd.print("Kwh: ");lcd.print(energy);

    Serial.print("V: ");
    Serial.println(voltage);
    Serial.println("Amp: ");
    Serial.println(current);
    Serial.println("Kwh: ");
    Serial.println(energy);
    
   delay(1000);
}
