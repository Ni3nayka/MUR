/*
 * code write for project:
 * https://github.com/Ni3nayka/MUR
 * 
 * author: Egor Bakay <egor_bakay@inbox.ru> Ni3nayka
 * write:  February 2022
 * modify: February 2022
 */

#pragma once

#include "stepper.h"

#define STEP_PIN_DIR_A 2
#define STEP_PIN_STP_A 3
#define STEP_PIN_MS3_A 4
#define STEP_PIN_MS2_A 5
#define STEP_PIN_MS1_A 6

#define STEP_PIN_DIR_B 8
#define STEP_PIN_STP_B 9
#define STEP_PIN_MS3_B 10
#define STEP_PIN_MS2_B 11
#define STEP_PIN_MS1_B 12

#define STEP_PIN_EN    7
#define STEP_PIN_VOLT  A7
#define STEP_OFF_TIME  500

//stepper stepper1(STEP_PIN_DIR_A,STEP_PIN_STP_A,STEP_PIN_MS2_A,STEP_PIN_MS1_A,STEP_PIN_MS0_A,STEP_PIN_EN_A);

class Shield {
  public:
    stepper stepper_A;
    stepper stepper_B;
    void setup() {
        stepper_A.setup(STEP_PIN_DIR_A,STEP_PIN_STP_A,STEP_PIN_MS3_A,STEP_PIN_MS2_A,STEP_PIN_MS1_A);
        stepper_B.setup(STEP_PIN_DIR_B,STEP_PIN_STP_B,STEP_PIN_MS3_B,STEP_PIN_MS2_B,STEP_PIN_MS1_B);
        pinMode(STEP_PIN_EN,OUTPUT);
        Shield::on_stepper();
        _timer_off_stepper = 0;
    }
    int voltmetr() {
      return analogRead(STEP_PIN_VOLT)/5; // подобрать K
    }
    void update() {
      stepper_A.update();
      stepper_B.update();
      if (stepper_A.real_speed()==0 && stepper_B.real_speed()==0) {
        if (_timer_off_stepper+STEP_OFF_TIME<millis()) {
          Shield::off_stepper();
        }
      }
      else {
        _timer_off_stepper = millis();
        Shield::on_stepper();
      }
    }
    void test() {
      stepper_A.step_mode(2);
      stepper_A.step_mode(3);
      stepper_A.step_mode(6);
      stepper_A.step_mode(7);
    }
  private:
  unsigned long int _timer_off_stepper;
    void off_stepper() {
      digitalWrite(STEP_PIN_EN,1);
    }
    void on_stepper() {
      digitalWrite(STEP_PIN_EN,0);
    }
};
