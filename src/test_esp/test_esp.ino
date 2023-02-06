// LOLIN(WEMOS) D1 R2 & mini

#include "wifi_config.h" // wifi-pass 
// uncomment this if you need:
//#define WIFI_NAME "test_name"
//#define WIFI_PASSWORD "test_pass"
//#define DEVICE_NAME "test_esp8266" 
//#define DEVICE_PASSWORD "1234"

#include "I2C_config.h"
#include <Wire.h>

#define ENABLE_AVOCADO_ESP_WIFI_BOOT

#include <AVOCADO_esp.h>

AVOCADO_esp esp;

void setup() {
  Wire.begin(D1, D2); 
  Wire.setClock(I2C_CLOCK);
  Serial.begin(115200);
  esp.setup();
}

void loop() {
  esp.update();
  i2c_test();
}

void i2c_test() {
  Wire.beginTransmission(I2C_ADRESS); /* Начинаем передачу на адресе 8 */
  Wire.write("Hello Arduino");  /* Отправляем "hello Arduino" */
  Wire.endTransmission();    /* прекращаем передачу */

  Wire.requestFrom(I2C_ADRESS, 100); /* запрашиваем и считываем 13 байт с адреса 8 slave устройства */
  bool flag = 0;
  while(Wire.available()){
    char c = Wire.read();
    Serial.print(c);
    flag = 1;
  }
  if (flag) Serial.println();
  //delay(1000);
}
