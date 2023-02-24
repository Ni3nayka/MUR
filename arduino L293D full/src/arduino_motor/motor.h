/*
 * code write for project:
 * https://github.com/Ni3nayka/MUR
 * 
 * author: Egor Bakay <egor_bakay@inbox.ru> Ni3nayka
 * write:  February 2022
 * modify: February 2022
 */

#pragma once

#include <AFMotor.h>

AF_DCMotor motor_1(1);
AF_DCMotor motor_2(2);
AF_DCMotor motor_3(3);
AF_DCMotor motor_4(4);

#define MOTOR_DIR(a) (a==0?RELEASE:(a>0?FORWARD:BACKWARD))

void motor(int number, int speed) {
  if (number==1) {
    motor_1.run(MOTOR_DIR(speed));
    motor_1.setSpeed(abs(speed));
  }
  else if (number==2) {
    motor_2.run(MOTOR_DIR(speed));
    motor_2.setSpeed(abs(speed));
  }
  else if (number==3) {
    motor_3.run(MOTOR_DIR(speed));
    motor_3.setSpeed(abs(speed));
  }
  else if (number==4) {
    motor_4.run(MOTOR_DIR(speed));
    motor_4.setSpeed(abs(speed));
  }
}
