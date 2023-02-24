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

#include "motor.h"
#include "servo.h"

int device_mode = 0;
int device_number = 0;

/* device_mode:
 * 0 - no (error)
 * 1 - motor
 * 2 - servo
 * 3 - sensor
 */

#define DEBUG

void setup() {
  Serial.begin(115200);
  Wire.begin(I2C_ADRESS); 
  Wire.setClock(I2C_CLOCK);
  Wire.onReceive(receiveEvent); /* регистрируем полученное событие */
  Wire.onRequest(requestEvent); /* регистрируем запрошенное событие */
  motor(1,0);
  motor(2,0);
  motor(3,0);
  motor(4,0);
  setup_servo();
}

void loop() {
  
}

void receiveEvent(int howMany) {
  device_mode = 0;
  device_number = 0;
  int device_input_counter = 0;
  while (0 < Wire.available()) {
    int c = Wire.read(); 
    //Serial.print(int(c)); Serial.print(" ");
    if (device_input_counter==0) {
      if (I2C_SYMBOL_MOTOR(c)) {
        device_mode = 1;
        device_number = I2C_READ_NUMBER_MOTOR(c);
      }
      else if (I2C_SYMBOL_SERVO(c)) {
        device_mode = 2;
        device_number = I2C_READ_NUMBER_SERVO(c);
      }
      else if (I2C_SYMBOL_SENSOR(c)) {
        device_mode = 3;
        device_number = I2C_READ_NUMBER_SENSOR(c);
      }
      else device_mode = 0;
    }
    else if (device_mode>0) {
      if (device_input_counter==1) {
        if (device_mode==1) motor(device_number,I2C_READ_SPEED_MOTOR(c));
        else if (device_mode==2) servo(device_number,c);
        else device_mode = 0;
      }
      else device_mode = 0;
    }
    device_input_counter++;
  }
  //if (device_mode==0) Serial.println("ERROR: the message was received with an error");
}

void requestEvent() {
  if (device_mode==1 || device_mode==2) Wire.write(SYMBOL_OK);
  else if (device_mode==3) Wire.write(char(map(analogRead(device_number),0,1023,0,250)));
  else Wire.write(SYMBOL_ERROR);
  device_mode = 0;
  device_number = 0;
}
