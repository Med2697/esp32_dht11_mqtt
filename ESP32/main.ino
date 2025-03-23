#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal.h>
#include<WiFi.h>
#include "cert.h"
#include "config.h"
#include "wifi_handler.h"
#include "mqtt_handler.h"
#include "thing_handler.h"
#include <PubSubClient.h>
extern PubSubClient Client;

#define dhtpin 14
#define pin 4

LiquidCrystal lcd(16,17,5,18,19,21);
DHT dht(dhtpin,DHT11);

float temperature,humidite;
const unsigned long intervale = 10000;
long precedentvalue =0;
long value;

const char* server = "api.thingspeak.com";
bool flag = false;

void IRAM_ATTR res(){
  flag = true;
}

void setup() {
  // put your setup code here, to run once:
  pinMode(pinl,OUTPUT);
  lcd.begin(16,2);
  attachInterrupt (digitalPinToInterrupt(pin),res,FALLING);
  connect (lcd);
  setupMQTT(lcd);
  dht.begin();  
}

void loop() {
  // put your main code here, to run repeatedly:
  if(!Client.connected()) connectMQTT(lcd);
  if (flag){
    lcd.clear();
    lcd.print("interrupt");
    delay(800);
    flag = false;
  }
  value = millis();
  if((value-precedentvalue)>intervale){
    //temperature = dht.readTemperature();
    //humidite = dht.readHumidity();
    temperature = random(90,100)/10.0;
    humidite = random(800,850)/10.0;
    precedentvalue = value;
    if (isnan(temperature) || isnan(humidite)){
      lcd.clear();
      lcd.print("DHT erreur");
      delay(1000);
    }
    senttoThing(temperature, humidite, lcd);
    sendToMQTT(temperature, humidite, lcd);
    handleMQTT();
    }
  }
  
