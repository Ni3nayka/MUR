#include "wifi_config.h" // wifi-pass 
// uncomment this if you need:
//#define WIFI_NAME "test_name"
//#define WIFI_PASSWORD "test_pass"
//#define DEVICE_NAME "test_esp8266" 
//#define DEVICE_PASSWORD "1234"

#define ENABLE_AVOCADO_ESP_WIFI_BOOT

#include <AVOCADO_esp.h>

AVOCADO_esp esp;

void setup() {
  Serial.begin(115200);
  esp.setup();
}

void loop() {
  esp.update();
}
