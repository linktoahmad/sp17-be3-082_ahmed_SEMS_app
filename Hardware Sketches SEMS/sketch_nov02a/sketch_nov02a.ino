#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
//needed for library
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager
#define trigger D0
#define LED D2
#define power D3
void setup() {
    // put your setup code here, to run once:
    Serial.begin(115200);
    pinMode(trigger,INPUT); 
    pinMode(LED,OUTPUT); 
     pinMode(power,OUTPUT);    
    if(digitalRead(trigger) == HIGH){
    digitalWrite(power,HIGH);
    WiFiManager wifiManager;
    wifiManager.resetSettings();
    wifiManager.autoConnect("CIRCUIT DIGEST WiFi Manager");
    Serial.println("connected :)");
  }     
}
void loop() { 
  if (WiFi.status() == WL_CONNECTED)
        {
          digitalWrite(power,LOW);
          while(WiFi.status() == WL_CONNECTED){           
            digitalWrite(LED,HIGH);
            delay(500);
            digitalWrite(LED,LOW);
            delay(200);   
          }              
        }
        else {
          digitalWrite(LED,LOW);
        }
}
