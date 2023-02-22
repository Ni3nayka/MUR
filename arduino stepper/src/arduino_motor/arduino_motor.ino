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

int device_mode = 0;
/*
 * 0 - no (error)
 * 1 - motor
 * 2 - servo
 * 3 - sensor
 */
int device_number = 0;
int device_input_counter = 0;

int servo_angle[2] = {90,90};
int motor_speed[2] = {0,0};
int motor_distanse[2] = {0,0};

#define DEBUG

void setup() {
  Wire.begin(I2C_ADRESS); 
  Wire.setClock(I2C_CLOCK);
  Wire.onReceive(receiveEvent); /* регистрируем полученное событие */
  Wire.onRequest(requestEvent); /* регистрируем запрошенное событие */
  Serial.begin(115200);
}

void loop() {
  update_servo();
  update_motor();
}

void  update_servo() {
  
}

void  update_motor() {
  
}

void receiveEvent(int howMany) {
  device_input_counter = 0;
  device_mode = 0;
  device_number = 0;
  while (0 < Wire.available()) {
    int c = Wire.read(); 
    #ifdef DEBUG
      Serial.print(int(c)); 
      Serial.print(" ");
    #endif
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
        if (device_mode==1) motor_speed[device_number-1] = I2C_READ_SPEED_MOTOR(c);
        else if (device_mode==2) servo_angle[device_number-1] = c;
        else device_mode = 0;
      }
      else if (device_input_counter==2) {
        if (device_mode==1) motor_distanse[device_number-1] = c;
        else device_mode = 0;
      }
      else device_mode = 0;
    }
    device_input_counter++;
  }
  #ifdef DEBUG
    Serial.println(); 
    print_data();
  #endif
  if (device_mode==0) Serial.println("ERROR: the message was received with an error");
}

void print_data() {
  Serial.print("motor_speed: ");
  Serial.print(motor_speed[0]);
  Serial.print(" ");
  Serial.print(motor_speed[1]);
  Serial.print("   motor_distanse: ");
  Serial.print(motor_distanse[0]);
  Serial.print(" ");
  Serial.print(motor_distanse[1]);
  Serial.print("   servo_angle: ");
  Serial.print(servo_angle[0]);
  Serial.print(" ");
  Serial.print(servo_angle[1]);
  Serial.println();
}

void requestEvent() {
  if (device_mode==1 || device_mode==2) Wire.write(SYMBOL_OK);
  else if (device_mode==3) Wire.write(char(map(analogRead(device_number),0,1023,0,250)));
  else Wire.write(SYMBOL_ERROR);
  device_mode = 0;
}
