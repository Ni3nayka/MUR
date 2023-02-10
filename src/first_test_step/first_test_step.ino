// Установка выводов
const int dirPin = 2;
const int stepPin = 3;
const int stepsPerRevolution = 800;

int test = 2000;
void setup()
{
  // Объявить контакты как выходы
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  
//  pinMode(A6, OUTPUT);
//  digitalWrite(A6,0);

  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  digitalWrite(6,0); // 0
  digitalWrite(5,1); // 1
  digitalWrite(4,1); // 2
}
void loop()
{
  // Установка направления вращения двигателя по часовой стрелке.
  digitalWrite(dirPin, HIGH);
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
//  for(int x = 0; x < stepsPerRevolution; x++)
//  {
//    digitalWrite(stepPin, HIGH);
//    delayMicroseconds(test/2);
//    digitalWrite(stepPin, LOW);
//    delayMicroseconds(test/2);
//  }
  delay(1000); // Ждем секунду
}
