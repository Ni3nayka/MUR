#define PWMB 10 
#define DIRB 12
#define PWMA 11
#define DIRA 13

#include <PinChangeInt.h>
#define AAA A4
volatile uint16_t interruptCount=0;
void BBB() {
  interruptCount++;
}

void setup() {
  pinMode(AAA, INPUT); // INPUT_PULLUP
  attachPinChangeInterrupt(AAA, BBB, CHANGE);
  Serial.begin(9600);
  Serial.println("---------------------------------------");
}

void loop() {
  delay(1000);
  Serial.print("Pin was interrupted: ");
  Serial.print(interruptCount, DEC); 
  Serial.println(" times so far.");
}
