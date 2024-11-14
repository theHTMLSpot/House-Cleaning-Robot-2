#include <Servo.h>

#define echoPin 1
#define trigPin 0
#define stepR 7
#define dirR 6
#define stepL 8
#define dirL 9
#define kneeR 4
#define kneeL 5

#define stepsPerRevolution 200

Servo Left;
Servo Right;

void setup() {
  Serial.begin(9600);

  Left.attach(kneeL);
  Right.attach(kneeR);

  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(stepR, OUTPUT);
  pinMode(dirR, OUTPUT);
  pinMode(stepL, OUTPUT);
  pinMode(dirL, OUTPUT);
  pinMode(kneeR, OUTPUT);
  pinMode(kneeL, OUTPUT);
}

void loop() {
  long duration, distance;

  // Send ultrasonic pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Calculate distance
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;
  Serial.println(distance);

  // Trigger movement if object is within 20 cm
  if (distance < 20) {
    Left.write(90);
    Right.write(90);
    delay(500);

    if (distance >= 20) return;

    Left.write(45);
    Right.write(45);
    delay(500);

    if (distance >= 20) return;

    Left.write(180);
    Right.write(180);

    // Set motor directions
    digitalWrite(dirL, LOW);
    digitalWrite(dirR, LOW);

    digitalWrite(stepL, HIGH);
    digitalWrite(stepR, HIGH);
    delay(5000);

    digitalWrite(stepL, LOW);
    digitalWrite(stepR, LOW);

    // Change direction for turning
    digitalWrite(dirL, HIGH);
    digitalWrite(dirR, LOW);

    digitalWrite(stepL, HIGH);
    digitalWrite(stepR, HIGH);
    delay(500);

    digitalWrite(stepL, LOW);
    digitalWrite(stepR, LOW);

    // Reset both directions forward
    digitalWrite(dirL, HIGH);
    digitalWrite(dirR, HIGH);
  }

  delay(100);
}
