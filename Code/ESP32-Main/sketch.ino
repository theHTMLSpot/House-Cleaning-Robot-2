#include <servo.h>

#define echo 1
#define trig 0
#define stepR 7
#define dirR 6
#define stepL 8
#define dirL 9
#define kneeR 4
#define kneeL 5

#define stepsPerRevolution 200;

Servo Left;
Servo Right;

void setup() {
  Serial.begin(9600);

  Left.attach(kneeL);
  Right.attach(kneeR);

  pinMode(echo, INPUT);
  pinMode(trig, OUTPUT);
  pinMode(stepR, OUTPUT);
  pinMode(dirR, OUTPUT);
  pinMode(stepL, OUTPUT);
  pinMode(dirL, OUTPUT);
  pinMode(kneeR, OUTPUT);
  pinMode(kneeL, OUTPUT);
}

void loop() {
  long duration, distance;
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(LOW);
    
  duration = pulseIn(echo, HIGH);
  distance = (duration/2) / 29.1;
  Serial.println(distance);

  digitalWrite(stepL, HIGH);
  digitalWrite(stepR, HIGH);

  delay(500);
  if(distance < 20)
  {
    Left.write(90);
    right.write(90)
    delay(500);
    if ( distance !< 20)
    {
      return;
    }
    Left.write(45);
    Right.write(45);
    delay(500);
     if ( distance !< 20)
    {
      return;
    }
    Left.write(180);
    Right.write(180);

    digitalWrite(dirL, LOW);  
    digitalWrite(dirR, LOW);

    digitalWrite(stepL, HIGH);
    digitalWrite(stepR, HIGH);

    delay(5000);

    digitalWrite(stepL, LOW );
    digitalWrite(stepR, LOW);

    digitalWrite(dirL, HIGH);
    digitalWrite(dirR, LOW); 


    digitalWrite(stepL, HIGH);
    digitalWrite(stepR, HIGH);

    delay(500);

    digitalWrite(stepL, LOW );
    digitalWrite(stepR, LOW);

    digitalWrite(dirL, HIGH);  
    digitalWrite(dirR, HIGH);

  }

  
 }
