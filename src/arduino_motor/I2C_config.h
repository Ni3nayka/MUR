/*
 * code write for project:
 * https://github.com/Ni3nayka/MUR
 * 
 * author: Egor Bakay <egor_bakay@inbox.ru> Ni3nayka
 * write:  February 2022
 * modify: February 2022
 */

#pragma once

#define I2C_ADRESS 0x17
#define I2C_CLOCK 400000

/* 
 * protocol: 
 * device (**options)
 * motor_number(1:2) speed(27:227)(-100:100) distanse(0:250)  - require confirmation
 * servo_number(3:4)(1:2) angle(0:180)  - require confirmation
 * sensor_number(5:8)(0:4)
 */

#define I2C_SYMBOL_MOTOR(a) (int(a)==1||int(a)==2)
#define I2C_SYMBOL_SERVO(a) (int(a)==3||int(a)==4)
#define I2C_SYMBOL_SENSOR(a) (int(a)>=5&&int(a)<=8)

#define I2C_READ_NUMBER_MOTOR(a) int(a)
#define I2C_READ_NUMBER_SERVO(a) (int(a)-2)
#define I2C_READ_NUMBER_SENSOR(a) (int(a)-5)

#define I2C_WRITE_NUMBER_MOTOR(a) int(a)
#define I2C_WRITE_NUMBER_SERVO(a) (int(a)+2)
#define I2C_WRITE_NUMBER_SENSOR(a) (int(a)+5)

#define I2C_MOTOR_SPEED_TRANSLATE 127
#define I2C_WRITE_SPEED_MOTOR(a) (int(a)+I2C_MOTOR_SPEED_TRANSLATE)
#define I2C_READ_SPEED_MOTOR(a) (int(a)-I2C_MOTOR_SPEED_TRANSLATE)

#define SYMBOL_EMPTY int(255)
#define SYMBOL_ERROR int(254)
#define SYMBOL_OK int(253)
#define SYMBOL_EMERGENCY_STOP int(252)

//void WireSetup() {
//  #ifdef __AVR_ATmega328P__
//     Wire.begin(I2C_ADRESS);
//  #else
//     Wire.begin(D1, D2); 
//  #endif
//  Wire.setClock(I2C_CLOCK);
//}
