/*
 * code write for project:
 * https://github.com/Ni3nayka/MUR
 * 
 * author: Egor Bakay <egor_bakay@inbox.ru> Ni3nayka
 * write:  February 2022
 * modify: February 2022
 */

#pragma once

#include <Servo.h>

Servo servo_1;
Servo servo_2;

#define PIN_SERVO_1 9
#define PIN_SERVO_2 10

void setup_servo() {
  servo_1.attach(PIN_SERVO_1);
  servo_2.attach(PIN_SERVO_2);
}

void servo(int number, int angle) {
  if      (number==1) servo_1.write(angle);
  else if (number==2) servo_2.write(angle);
}
