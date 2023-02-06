/*
 * code write for project:
 * https://github.com/Ni3nayka/MUR
 * 
 * author: Egor Bakay <egor_bakay@inbox.ru> Ni3nayka
 * write:  February 2022
 * modify: February 2022
 */

#pragma once

#include "I2C_config.h"
#include <Wire.h>

class I2C_sender {
  public:
    
    void setup() {
      Wire.begin(D1, D2); 
      Wire.setClock(I2C_CLOCK);
    }
    
    void test() {
      // send
      Wire.beginTransmission(I2C_ADRESS); /* Начинаем передачу на адресе 8 */
      Wire.write("Hello Arduino");  /* Отправляем "hello Arduino" */
      Wire.endTransmission();    /* прекращаем передачу */
      // get
      Wire.requestFrom(I2C_ADRESS, 15); /* (A,B) запрашиваем и считываем B байт с адреса A slave устройства */
      bool flag = 0;
      while(Wire.available()){
        char c = Wire.read();
        if (c==SYMBOL_EMPTY) break;
        Serial.print(c);
        flag = 1;
      }
      if (flag) Serial.println();
      //delay(1000);
    }

    void motor(int number, int speed, int distanse = 0) {
      number = I2C_WRITE_NUMBER_MOTOR(number);
      if (!I2C_SYMBOL_MOTOR(number)) {
        Serial.println("WARNING: you are requesting a non-existent device - motor");
        return;
      }
      speed = constrain(speed,-100,100);
      distanse = constrain(distanse,0,250);
      String a = String((char)number) + String((char)I2C_WRITE_SPEED_MOTOR(speed)) + String((char)distanse);
      //Serial.print(">>>");Serial.print(a); Serial.print("<<<"); Serial.println();
      I2C_sender::full_send(a);
    }

    void servo(int number, int angle) {
      number = I2C_WRITE_NUMBER_SERVO(number);
      if (!I2C_SYMBOL_SERVO(number)) {
        Serial.println("WARNING: you are requesting a non-existent device - servo");
        return;
      }
      angle = constrain(angle,0,180);
      String a = String((char)number) + String((char)angle);
      I2C_sender::full_send(a);
    }

    int sensor(int number) {
      number = I2C_WRITE_NUMBER_SENSOR(number);
      if (!I2C_SYMBOL_SENSOR(number)) {
        Serial.println("WARNING: you are requesting a non-existent device - sensor");
        return 0;
      }
      int a = 0;
      do {
        I2C_sender::send_data(String((char)number));
        a = I2C_sender::get_data();
      } while (a==SYMBOL_ERROR);
      return a;
    }

    void emergency_stop() {
      for (int i = 0; i < 100; i++) {
        I2C_sender::send_data(String(SYMBOL_EMERGENCY_STOP));
      }
    }
    
  private:

    void full_send(String a) {
      do {
        I2C_sender::send_data(a);
      } while (I2C_sender::get_data()!=SYMBOL_OK);
    }
    
    void send_data(String a) {
      Wire.beginTransmission(I2C_ADRESS);
      for (int i = 0; i<a.length(); i++) {
        Wire.write(a[i]);
      }
      Wire.endTransmission();
    }

    int get_data() {
      delayMicroseconds(1); // slow arduino
      int a = Wire.requestFrom(I2C_ADRESS, 1);
//      if (a==0) {
//        Serial.println("ERROR: I2C device unavailable");
//        return SYMBOL_ERROR;
//      }
      int c = Wire.read();
      //Serial.print(">"); Serial.println(c);
      if (c==-1) {
        Serial.println("WARNING: no response from I2C received - replay");
        return I2C_sender::get_data();
      }
      else return c;
    }
};
