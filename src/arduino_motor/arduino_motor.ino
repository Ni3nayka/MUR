/*
 * code write for project:
 * https://github.com/Ni3nayka/MUR
 * 
 * author: Egor Bakay <egor_bakay@inbox.ru> Ni3nayka
 * write:  February 2022
 * modify: February 2022
 */

#include "I2C_config.h"
#include <Wire.h>

void setup() {
  Wire.begin(I2C_ADRESS); 
  Wire.setClock(I2C_CLOCK);
  Wire.onReceive(receiveEvent); /* регистрируем полученное событие */
  Wire.onRequest(requestEvent); /* регистрируем запрошенное событие */
  Serial.begin(9600);           /* открываем серийный порт для дебаггинга */
}

void loop() {
  //delay(100);
}

// Функция для извлечения любых принимаемых данных от мастера на шину
void receiveEvent(int howMany) {
  while (0 < Wire.available()) {
    char c = Wire.read();      /* получаем байт как символ*/
    Serial.print(c);           /* выводим символ в серийный порт */
  }
  Serial.println();             /* переходим на новую строку */
}

// Функция для извлечения любых отправляемых данных от мастера на шину
void requestEvent() {
  Wire.write("Hello NodeMCU");  /* отправляем по запросу строку "Hello NodeMCU" */
}
