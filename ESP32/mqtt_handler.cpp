#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include "mqtt_handler.h"
#include "config.h"
#include "cert.h"

WiFiClientSecure esp32;
PubSubClient Client(esp32);
char* ledState = "OFF";

void setupMQTT(LiquidCrystal &lcd) {
    esp32.setCACert(root_ca);
    Client.setServer(mqtt_server, port);
    Client.setCallback(led_sub);

}
void connectMQTT (LiquidCrystal &lcd){
    while (!Client.connected()) {
        lcd.clear();
        lcd.print("Connecting MQTT...");
        delay(1000);
        lcd.clear();
        if (Client.connect("ESP32_Client", mqtt_user, mqtt_psw)) {
            lcd.print("MQTT Connected");
            Client.subscribe("led");
            handleMQTT();
        } else {
            lcd.print("MQTT Connection Failed");
            delay(2000);
        }
    }
    delay(1000);
}

void led_sub(char* topic, byte *payload, uint8_t length){
  if (String(topic) == "led"){
    String message ="";
    for(int i=0;i<length;i++){
      message+=(char)payload[i];
    }
    if(message == "ON"){
      digitalWrite(pinl,HIGH);
      ledState = "ON";
    }else if (message == "OFF"){
      digitalWrite(pinl, LOW);
      ledState = "OFF";
    }
    delay(800);
  }
}

void handleMQTT() {
    Client.loop();
}

void sendToMQTT(float temperature, float humidity, LiquidCrystal &lcd) {
    lcd.clear();
    if (!Client.publish("esp32/temp",String(temperature).c_str(),true)
        || !Client.publish("esp32/temp",String(humidity).c_str(),true)
        || !Client.publish("esp32/led",String(ledState).c_str(),true)) {
        lcd.print("MQTT Failed");
    } else {
        lcd.print("MQTT Sent");
    }
    delay(800);
}
