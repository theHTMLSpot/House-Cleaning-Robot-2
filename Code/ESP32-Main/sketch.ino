#include <Servo.h>
#include <esp_now.h>

// Pin Definitions
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

bool manualOverride = false; // Flag for manual override
bool stopSignal = false;     // Flag for stop command received via ESP-NOW
bool stairsMode = false;     // Flag for stair-climbing mode

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

  Serial.println("Robot ready!");

  // Initialize ESP-NOW without Wi-Fi
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Register receive callback
  esp_now_register_recv_cb(onDataReceived);
}

void loop() {
  long duration, distance;

  // Stop all operations if stop signal is active
  if (stopSignal) {
    stopMovement();
    return;
  }

  // Handle stair-climbing mode
  if (stairsMode) {
    climbStairs();
    return;
  }

  // Manual control
  if (manualOverride) {
    // Add manual control logic here (Bluetooth or other)
    return;
  }

  // Autonomous operation
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;
  Serial.println(distance);

  // Send ultrasonic pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Trigger movement if object is within 20 cm
  if (distance < 20) {
    autonomousMovement(distance);
  }

  delay(100);
}

void autonomousMovement(long distance) {
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

void stopMovement() {
  digitalWrite(stepL, LOW);
  digitalWrite(stepR, LOW);
  Serial.println("Stop signal received, halting movement.");
}

void climbStairs() {
  Serial.println("Climbing stairs...");
  // Simulate stair-climbing with servo movements
  for (int i = 0; i < 5; i++) { // Repeat the climb motion 5 times
    // Bend knees
    Left.write(45);
    Right.write(45);
    delay(500);

    // Extend knees
    Left.write(90);
    Right.write(90);
    delay(500);
  }

  // Reset knees and exit stairs mode
  Left.write(90);
  Right.write(90);
  stairsMode = false;
  Serial.println("Finished climbing stairs.");
}

// ESP-NOW callback function to handle incoming data
void onDataReceived(const uint8_t *macAddr, const uint8_t *incomingData, int len) {
  String command = "";
  for (int i = 0; i < len; i++) {
    command += (char)incomingData[i];
  }
  
  Serial.print("Received command: ");
  Serial.println(command);

  if (command == "S") {
    stopSignal = true; // Stop the robot
    Serial.println("Received ESP-NOW Stop Command");
  } else if (command == "C") {
    stopSignal = false; // Clear stop signal
    Serial.println("Received ESP-NOW Clear Stop Command");
  } else if (command == "STAIRS") {
    stairsMode = true; // Enter stair-climbing mode
    Serial.println("Received ESP-NOW STAIRS Command");
  }
}
