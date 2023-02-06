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

#define SYMBOL_START 255
#define SYMBOL_END 254
//#define SYMBOL_START_SET
#define SYMBOL_OK 253
#define SYMBOL_ERROR 252
//#define 

//void WireSetup() {
//  #ifdef __AVR_ATmega328P__
//     Wire.begin(I2C_ADRESS);
//  #else
//     Wire.begin(D1, D2); 
//  #endif
//  Wire.setClock(I2C_CLOCK);
//}
