/*
 * code write for project:
 * https://github.com/Ni3nayka/MUR
 * 
 * author: Egor Bakay <egor_bakay@inbox.ru> Ni3nayka
 * write:  February 2022
 * modify: February 2022
 */

// LOLIN(WEMOS) D1 R2 & mini

#include "wifi_config.h" // wifi-pass 
// uncomment this if you need:
//#define WIFI_NAME "test_name"
//#define WIFI_PASSWORD "test_pass"
//#define DEVICE_NAME "test_esp8266" 
//#define DEVICE_PASSWORD "1234"

#define ENABLE_AVOCADO_ESP_WIFI_BOOT

#include <AVOCADO_esp.h>

AVOCADO_esp esp;

#include "I2C_sender.h"
I2C_sender i2c;

void setup() {
  delay(1000);
  Serial.begin(115200);
  Serial.println();
  Serial.println();
  //esp.setup();
  i2c.setup();
  i2c.motor(3,-50);
  delay(1000);
  i2c.motor(3,0);
//  i2c.motor(1,100);
//  i2c.motor(2,-98,150);
//  i2c.servo(1,250);
//  i2c.servo(1,-5);
//  i2c.servo(2,78);
//  Serial.println("----");
//  Serial.println(i2c.sensor(0));
//  Serial.println(i2c.sensor(1));
//  Serial.println(i2c.sensor(2));
//  Serial.println(i2c.sensor(3));
//  Serial.println("end");
}

void loop() {
  //esp.update();
  //i2c.test();
}
