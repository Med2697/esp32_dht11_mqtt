#ifndef MQTT_HANDLER_H
#define MQTT_HANDLER_H


#include <LiquidCrystal.h>

void setupMQTT(LiquidCrystal &lcd);
void sendToMQTT(float temperature, float humidity, LiquidCrystal &lcd);
void handleMQTT();
void led_sub(char* topic, byte *payload, uint8_t length);
void connectMQTT (LiquidCrystal &lcd);


#endif
