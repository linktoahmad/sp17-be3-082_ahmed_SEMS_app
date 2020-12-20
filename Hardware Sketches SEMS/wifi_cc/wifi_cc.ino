#include <ESP8266WiFi.h>        
//needed for library
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>         

void setup() {

    Serial.begin(115200);
    
    WiFiManager wifiManager;
    wifiManager.resetSettings();
    wifiManager.autoConnect("SEMS ioT Meter");
       
}
void loop() { 
 
}
