/*
  Copyright (c) 2014-2015 NicoHood
  See the readme for credit to other people.

  PinChangeInterrupt_TickTock
  Demonstrates how to use the library

  Connect a button/cable to pin 7 and ground.
  The Led state will change if the pin state does.

  PinChangeInterrupts are different than normal Interrupts.
  See readme for more information.
  Dont use Serial or delay inside interrupts!
  This library is not compatible with SoftSerial.

  The following pins are usable for PinChangeInterrupt:
  Arduino Uno/Nano/Mini: All pins are usable
  Arduino Mega: 10, 11, 12, 13, 50, 51, 52, 53, A8 (62), A9 (63), A10 (64),
              A11 (65), A12 (66), A13 (67), A14 (68), A15 (69)
  Arduino Leonardo/Micro: 8, 9, 10, 11, 14 (MISO), 15 (SCK), 16 (MOSI)
  HoodLoader2: All (broken out 1-7) pins are usable
  Attiny 24/44/84: All pins are usable
  Attiny 25/45/85: All pins are usable
  Attiny 13: All pins are usable
  Attiny 441/841: All pins are usable
  ATmega644P/ATmega1284P: All pins are usable
*/

#include "PinChangeInterrupt.h"

// Choose a valid PinChangeInterrupt pin of your Arduino board
#define pinBlink 7

long int uuuuu = 0;
long int UUUUU = 0;

bool r1=0,r2=0,l1=0,l2=0;
bool R1=0,R2=0,L1=0,L2=0;

void setup() {
  // set pin to input with a pullup, led to output
  pinMode(pinBlink, INPUT_PULLUP);
  pinMode(8, INPUT);
  pinMode(7, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  // Manually blink once to test if LED is functional
  //blinkLed();
  //delay(1000);
  //blinkLed();

  // Attach the new PinChangeInterrupt and enable event function below
  attachPCINT(digitalPinToPCINT(8), blinkLed1, CHANGE);
  attachPCINT(digitalPinToPCINT(7), blinkLed2, CHANGE);
  r1 = digitalRead(8);
  r2 = digitalRead(7);
  l1 = r1;
  l2 = r2;
  
  attachInterrupt(0, UblinkLed1, CHANGE);
  attachInterrupt(1, UblinkLed2, CHANGE);
  R1 = digitalRead(2);
  R2 = digitalRead(3);
  L1 = R1;
  L2 = R2;
  
  Serial.begin(9600);
}

void UblinkLed1(void) {
  R1 = !R1;
  Uuuu();
}

void UblinkLed2(void) {
  R2 = !R2;
  Uuuu();
}

void Uuuu() {
  if (R1!=L2) UUUUU++;
  else UUUUU--;
  L1 = R1;
  L2 = R2;
}

void blinkLed1(void) {
  r1 = !r1;
  uuu();
}

void blinkLed2(void) {
  r2 = !r2;
  uuu();
}

void uuu() {
  if (r1!=l2) uuuuu++;
  else uuuuu--;
  l1 = r1;
  l2 = r2;
}

void loop() {
  // Nothing to do here
  Serial.print(uuuuu);
  Serial.print(" ");
  Serial.println(UUUUU);
  delay(500);
}
