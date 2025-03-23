#include <WiFi.h>
#include "thing_handler.h"
#include "config.h"
#include "wifi_handler.h"
#include <HTTPClient.h>


extern const char* server;

void senttoThing(float temp, float hum, LiquidCrystal &lcd){
  if(WiFi.status() != WL_CONNECTED ) connect(lcd);
  
   HTTPClient http;
   lcd.clear();
   lcd.print("Envoi Thing...");
   delay(500);
   String url = "https://" + String(server) + "/update?api_key=" + apikey + "&field1=" + String(temp) + "&field2=" + String(hum);
   http.begin(url);
   int a = http.GET();
   lcd.setCursor(0,1);
   if(a > 0){
     lcd.print("envoye");  
   }else{
     lcd.print("echec");    
   }
   delay(1000);
   http.end();

}
