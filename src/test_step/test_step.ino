#include "shield.h"
Shield Robot;

unsigned long int t = 0;
int moode = 0;

void setup() {
  Serial.begin(115200);
  Robot.setup();
  Robot.stepper_A.run(1000,3200); // 25 5000
  //Robot.stepper_A.step_mode(2);
}
void loop()
{
  Robot.update();
  /*if (t+5000<millis()) {
    delay(1000);
    moode++;
    Serial.println(moode-1);
    t = millis();
    Robot.stepper_B.step_mode(moode-1);
    if (moode==8) moode = 0;
    
//    if (moode==1) Robot.stepper_A.step_mode(STEP_SIZE_1);
//    else if (moode==2) Robot.stepper_A.step_mode(STEP_SIZE_2);
//    else if (moode==3) Robot.stepper_A.step_mode(STEP_SIZE_4);
//    else if (moode==4) Robot.stepper_A.step_mode(STEP_SIZE_8);
//    else {
//      moode = 0;
//      Robot.stepper_A.step_mode(STEP_SIZE_16);
//    }
  }*/
  // Установка направления вращения двигателя по часовой стрелке.
  /*digitalWrite(dirPin, HIGH);
  // Медленное вращение двигателя
  for(int x = 0; x < stepsPerRevolution; x++)
  {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(test);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(test);
  }
  delay(1000); // Ждем секунду
  
  // Установка направления вращения двигателя против часовой стрелке.
  digitalWrite(dirPin, LOW);
  // Быстрое вращение двигателя
  for(int x = 0; x < stepsPerRevolution; x++)
  {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(test/2);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(test/2);
  }
  delay(1000); // Ждем секунду*/
}
