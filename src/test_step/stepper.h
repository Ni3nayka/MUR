/*
 * code write for project:
 * https://github.com/Ni3nayka/MUR
 * 
 * author: Egor Bakay <egor_bakay@inbox.ru> Ni3nayka
 * write:  February 2022
 * modify: February 2022
 */

#pragma once

#define STEP_A 1
#define STOP_DISTANSE 600

//#define STEP_SIZE_16 0
//#define STEP_SIZE_8  1
#define STEP_SIZE_4  2
#define STEP_SIZE_2  3
#define STEP_SIZE_1  7

#define STEP_MIN_SPEED 1000 //5000
#define STEP_MAX_SPEED 25

#define ONE_TURN 800

class stepper {
  public:
    void setup(int dir, int stp, int ms3, int ms2, int ms1) {
      _pin_dir = dir;
      _pin_stp = stp;
      _pin_ms3 = ms3;
      _pin_ms2 = ms2;
      _pin_ms1 = ms1;
      _speed = 0;
      _distance = 0;
      _real_speed = 0;
      _sted_d = 0;
      _time = 0;
      _was_step = 0;
      pinMode(_pin_dir,OUTPUT);
      pinMode(_pin_stp,OUTPUT);
      pinMode(_pin_ms3,OUTPUT);
      pinMode(_pin_ms2,OUTPUT);
      pinMode(_pin_ms1,OUTPUT);
      step_mode(STEP_SIZE_4); 
    }
    void run(int speed, int distance = -1) {
      _speed = speed;
      _distance = distance;
    }
    void update() {
      stepper::_run_motor();
      stepper::_update_speed();
    }
    void step_mode(int mode) { 
      digitalWrite(_pin_ms1,mode%2); 
      digitalWrite(_pin_ms2,(mode>>1)%2); 
      digitalWrite(_pin_ms3,(mode>>2)%2);
      //_step_mode = mode==7?16:(mode==3?8:(mode==2?4:(mode==1?2:1)));
      _step_mode = mode==2?4:(mode==3?2:4);
    }
    int real_speed() {
      return _real_speed;
    }
  private:
    int _pin_dir,_pin_stp,_pin_ms3,_pin_ms2,_pin_ms1; //,_pin_en;
    int _speed, _real_speed;
    long int _distance;
    int _step_mode;
    bool _sted_d,_was_step;
    unsigned long int _time;
    
    void _update_speed() { ///////////////////////////////////////////////////////////////
      if (_was_step) {
        _was_step = 0;
        //Serial.println(_distance);
        _distance -= _step_mode;
      }
      
      if (_distance<=0) _real_speed = 0;
      //else _real_speed = constrain(_distance*STEP_A/_step_mode,0,_speed);
      else _real_speed = map(constrain(_distance/_step_mode,0,STOP_DISTANSE),0,STOP_DISTANSE,STEP_MIN_SPEED,_speed);
      
    }
    void _run_motor() {
      if (_real_speed==0) return;
      if (_time+_real_speed<micros()) {
        _time = micros();
        _sted_d = !_sted_d;
        digitalWrite(_pin_stp,_sted_d);
        if (_sted_d) _was_step = 1;
      }
    }
};
