#include "wifi_handler.h"
#include <WiFi.h>
#include "config.h"

void connect (LiquidCrystal &lcd){
  WiFi.begin(ssid,pswd);
  lcd.clear();
  lcd.print("connecxion wifi ..");
  lcd.setCursor(0,1);
  uint8_t count =0;
  while(WiFi.status() != WL_CONNECTED && count <20){
      count++;
      lcd.print(".");
      delay (500);
  }
  lcd.clear();
  if (WiFi.status()== WL_CONNECTED){
    lcd.print("Wifi connected");
  }else{
    lcd.print("erreur wifi");
  }
  delay(1000);
}
