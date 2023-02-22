/*
 * code write for project:
 * https://github.com/Ni3nayka/MUR
 * 
 * author: Egor Bakay <egor_bakay@inbox.ru> Ni3nayka
 * write:  February 2022
 * modify: February 2022
 */

// LOLIN(WEMOS) D1 R2 & mini

#include "pins.h"

class Robot {
  public:
    // SETUP 
    void setup() {
      //delay(1000);
      Serial.begin(115200);
      Serial.println();
      Serial.println();
      Serial.println("Hello");
      pinMode(PWM_L1,OUTPUT);
      pinMode(PWM_L2,OUTPUT);
      pinMode(PWM_R1,OUTPUT);
      pinMode(PWM_R2,OUTPUT);
      pinMode(LED,OUTPUT);
      pinMode(MULTIPLEXER_S1,OUTPUT);
      pinMode(MULTIPLEXER_S2,OUTPUT);
      pinMode(MULTIPLEXER_S3,OUTPUT);
      pinMode(MULTIPLEXER_A,INPUT);
    }
    // MOTOR
    void motor_L(long int speed) {
      speed = translate_speed(speed);
      analogWrite(PWM_L1,speed>0?speed:0);
      analogWrite(PWM_L2,speed<0?-speed:0);
    }
    void motor_R(long int speed) {
      speed = translate_speed(speed);
      analogWrite(PWM_R1,speed>0?speed:0);
      analogWrite(PWM_R2,speed<0?-speed:0);
    }
    void motors(long int speed_L, long int speed_R) {
      motor_L(speed_L);
      motor_R(speed_R);
    }
    // AAAAAAAAAAAAAAAAAAAA 
    void update_enc() {
//      for (int i = 0; i<8; i++) {
//        Serial.print(Robot::get_multiplexer(i));  
//        Serial.print(" ");  
//      }
//      Serial.println();
      bool R1_new = Robot::get_multiplexer(MULTIPLEXER_ENC_R1);//>500;
      bool R2_new = Robot::get_multiplexer(MULTIPLEXER_ENC_R2);//>500;
      //Serial.println(Robot::get_multiplexer(MULTIPLEXER_ENC_R1));
      if (R1_new!=Robot::R1 || R2_new!=Robot::R2) {
        //Serial.println("!");
        if (Robot::R1!=R2_new) enc_R++;
        else enc_R--;
        Robot::R1 = R1_new;
        Robot::R2 = R2_new;
      }
    }
    // SENSOR
    int get_sensor(int n) {
      if (n==PIN_A1 || n==PIN_A2 || n==PIN_A3 || n==PIN_A4) 
        return Robot::get_multiplexer(n);
      return -1;
    }
    long int enc_L = 0, enc_R = 0;
  private:
    int get_multiplexer(int n) {
      //if (n<0 || n>7) return -1;
      digitalWrite(MULTIPLEXER_S1,n%2);
      digitalWrite(MULTIPLEXER_S2,(n>>1)%2);
      digitalWrite(MULTIPLEXER_S3,(n>>2)%2);
      //return analogRead(MULTIPLEXER_A);
      return analogRead(MULTIPLEXER_A)>500;
    }
    int translate_speed(long int speed) {
      return map(constrain(speed,-100,100),-100,100,-255,255);
    }
    bool L1 = 0, L2 = 0, R1 = 0, R2 = 0;
};

Robot robot;

unsigned long int time1 = 0;
unsigned long int time2 = 0;

void setup() {
  robot.setup();
  
//      for (int i = 0; i<8; i++) {
//        Serial.print(i%2);
//        Serial.print(" ");
//        Serial.print((i>>1)%2);
//        Serial.print(" ");
//        Serial.print((i>>2)%2);
//        Serial.println();  
//      }
}

void loop() {
  robot.update_enc();
  //digitalRead(LED);
  if (time1+1000<millis()) {
    time1 = millis();
    Serial.println(robot.enc_R);
    Serial.println(time2);
    time2 = 0;
  }
  if (time2==2000000) Serial.println("!");
  time2++;
//  robot.motor_R(100);
//  delay(1000);
//  robot.motor_R(0);
//  delay(1000);
//  robot.motor_R(-50);
//  delay(1000);
//  robot.motor_R(0);
//  delay(1000);
}
