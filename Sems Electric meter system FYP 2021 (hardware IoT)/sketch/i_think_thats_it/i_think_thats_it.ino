#include <WiFiManager.h> 
#include <DoubleResetDetector.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <PZEM004Tv30.h>
#include <FirebaseArduino.h>
#include <NTPClient.h>
#include <WiFiUdp.h>


#define FIREBASE_HOST "sems-6fa94.firebaseio.com"
#define FIREBASE_AUTH "je45PSiFWO2eMYnqAyGc6e8p6gAuJAhc3pERfppk"

#define DRD_TIMEOUT 10
#define DRD_ADDRESS 0

DoubleResetDetector drd(DRD_TIMEOUT, DRD_ADDRESS);
LiquidCrystal_I2C lcd(0x27, 16, 2);
PZEM004Tv30 pzem(D5, D6);

const long utcOffsetInSeconds = +18000;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "asia.pool.ntp.org", utcOffsetInSeconds);

float temp;
float temp_energy;
float temp_month;



void setup() {
  WiFiManager wifiManager;
  Serial.begin(115200);
  lcd.begin(16,2);
  lcd.init();
  lcd.backlight();
  Serial.begin(115200);


   lcd.print("Welcome SEMS");
   lcd.setCursor(0,1);
   lcd.print("Id sems001");
   delay(2000);
   lcd.clear();
   
   if (drd.detectDoubleReset()) {
    lcd.print("Reset Detected");
    delay(500);
    lcd.clear();
    wifiManager.resetSettings();
    lcd.print("connect to sems");
    lcd.setCursor(0,1);
    lcd.print("goto boards.io");
    delay(2000);
    wifiManager.autoConnect("SEMS ioT Meter");
    lcd.clear();
    lcd.print("SEMS Connected!");
    delay(2000);
    lcd.clear();
  } else {
    lcd.print("connect to sems");
    lcd.setCursor(0,1);
    lcd.print("& goto boards.io");
    wifiManager.autoConnect("SEMS ioT Meter"); 
    lcd.setCursor(1,0);     
    lcd.print("SEMS Connected!");
    lcd.setCursor(0,1);
    lcd.print("- sems001 -");
    delay(2000);
    lcd.clear();
  }

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  timeClient.begin();
  timeClient.update();

  float energy = pzem.energy();
    if( !isnan(energy) ){
        temp_energy = energy;
        temp_month = energy;
        Serial.println("readings form start");
        Serial.println("temp energy");
        Serial.println(temp_energy);
        
    } else {
        Serial.println("Error reading energy");
    }
}



void loop() {
 
    float voltage = pzem.voltage();
    if( !isnan(voltage) ){
        Firebase.setFloat("/sems001/volt", voltage);
    } else {
        Serial.println("Error reading voltage");
    }

    float current = pzem.current();
    if( !isnan(current) ){
        Firebase.setFloat("/sems001/amps", current);
    } else {
        Serial.println("Error reading current");
    }


    
    float energy = pzem.energy();
    if( !isnan(energy) ){
        Firebase.setFloat("/sems001/unit", energy);
    } else {
        Serial.println("Error reading energy");
    }
    

    float power = pzem.power();
    if( !isnan(power) && temp == 50 ){
      int p = (int)power;
        String days = Firebase.getString("/sems001/hours");
        Firebase.setString("/sems001/hours",days+","+p);
        temp =0;
    } else {
      Firebase.setFloat("/sems001/watt",power);
        Serial.println("Error reading power / not changed");
    }
    temp =temp+1;

    lcd.clear();
    lcd.print("V:");lcd.print(voltage);
    lcd.print(" A:");lcd.print(current);
    lcd.setCursor(0,1);
    lcd.print("Kwh: ");lcd.print(energy);

  timeClient.update();

  unsigned long epochTime = timeClient.getEpochTime();
  struct tm *ptm = gmtime ((time_t *)&epochTime);
  int monthDay = ptm->tm_mday;
  Serial.print("Month day: ");
  Serial.println(monthDay);

  int currentHour = timeClient.getHours();
  Serial.print("Hour: ");
  Serial.println(currentHour);  

  int currentMinute = timeClient.getMinutes();
  Serial.print("Minutes: ");
  Serial.println(currentMinute);

   int weekDay = timeClient.getDay();
   Serial.print("Week Day: ");
   Serial.println(weekDay);

   int currentMonth = ptm->tm_mon+1;
   Serial.print("Month: ");
   Serial.println(currentMonth);
  

    /*when day change day report get resetted 
    and add uset used this day to week*/
  if(currentHour == 23 && currentMinute >= 55){
    float day_Unit = energy-temp_energy;
    temp_energy = energy;
    Firebase.setString("/sems001/hours","");
    String days_x = Firebase.getString("/sems001/days");
    Firebase.setString("/sems001/days",days_x+","+day_Unit);
    }

/*on sunday weekly report get resetted*/
    if(weekDay == 0 && currentHour == 23 && currentMinute >= 55){
      Firebase.setString("/sems001/days","");
      }

/*on 1st day of month monthly report get resetted*/
    if(monthDay == 1 && currentHour == 23 && currentMinute >= 55){
      float month_Unit = energy-temp_month;
      temp_month = energy;
      String month_x = Firebase.getString("/sems001/years");
      Firebase.setString("/sems001/years",month_x+","+month_Unit);
      }

      
/*on 1st day of newyear yearly report get resetted*/
     if(currentMonth ==1 && monthDay == 1 && currentHour == 1 && currentMinute <=15){
      Firebase.setString("/sems001/years","");
      }
      


    Serial.print("V: ");
    Serial.println(voltage);
    Serial.println("Amp: ");
    Serial.println(current);
    Serial.println("Kwh: ");
    Serial.println(energy);
    Serial.println("w: ");
    Serial.println(power);
    
   delay(1000);
}
