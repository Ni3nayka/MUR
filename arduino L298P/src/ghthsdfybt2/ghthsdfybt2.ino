const int PWMA = 10;
const int PWMB = 11 ;
const int DIRA = 12 ;
const int DIRB = 13 ;
long int encL = 0 ;
long int encR = 0 ;
bool  erl1 , erl2, err1, err2;
bool  ell1 , ell2, elr1, elr2;

#include "PinChangeInterrupt.h"

void setup() {
  pinMode(8, INPUT);
  pinMode(7, INPUT);
  attachPCINT(digitalPinToPCINT(8), ghthsdfybt1, CHANGE);
  attachPCINT(digitalPinToPCINT(7), ghthsdfybt2, CHANGE);
  erl1 = digitalRead(8);
  erl2 = digitalRead(7);
  err1 = erl1;
  err2 = erl2;

  pinMode(5, INPUT);
  pinMode(6, INPUT);
  attachPCINT(digitalPinToPCINT(5), ghthsdfybt1L, CHANGE);
  attachPCINT(digitalPinToPCINT(6), ghthsdfybt2L, CHANGE);
  ell1 = digitalRead(5);
  ell2 = digitalRead(6);
  elr1 = ell1;
  elr2 = ell2;
  
  Serial.begin (9600);
  
  run_enc (2000, -2000);
//  motor(255,255);
//  delay(5000);
//  motor(0,0);
}

void loop() {

}

void run_enc(long int L, long int R) {
  long int eR = 0;
  long int eL = 0;
  long int eror = 50;
  unsigned long int t = millis();
  while (millis() - t < 1000) {
    if ( abs (eL) > eror || abs (eR) > eror)t = millis ();
    Serial.print( encR);
    Serial.print(" ");
    Serial.println( encL);
    eR = R - encR;
    eL = L - encL;

    eL *= 0.75;
    eR *= 0.75;
    motor (eL, eR);


  } motor (0,0);
}

void ghthsdfybt1 () {
  err1 = (!err1);
  jgthfnbyuR();

}
void ghthsdfybt2 () {
  err2 = (!err2);
  jgthfnbyuR();
}
void jgthfnbyuR() {
  if ( erl1 != err2) encR++;
  else encR--;
  //err1 = digitalRead(18);
  //err2 = digitalRead(19);
  erl1 = err1;
  erl2 = err2;
}
void ghthsdfybt1L () {
  elr1 = (!elr1);
  jgthfnbyuL();

}
void ghthsdfybt2L () {
  elr2 = (!elr2);
  jgthfnbyuL();
}
void jgthfnbyuL() {
  if ( ell1 != elr2) encL++;
  else encL--;
  //elr1 = digitalRead(20);
  //elr2 = digitalRead(21);
  ell1 = elr1;
  ell2 = elr2;
}
void motor (long int a , long int b ) {
  a = constrain (a, -255, 255);
  b = constrain (b , -255 , 255);
  analogWrite ( PWMA, abs (a));
  analogWrite ( PWMB, abs (b));
  digitalWrite (DIRA, a > 0);
  digitalWrite (DIRB, b > 0);
}
