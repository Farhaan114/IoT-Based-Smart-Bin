#include <Servo.h>

// Define pins for PIR sensor, ultrasonic sensors, and servo motor
const int pirPin = 2;
const int ultrasonicEchoPin1 = 4;
const int ultrasonicTrigPin1 = 3;
const int ultrasonicEchoPin2 = 6;
const int ultrasonicTrigPin2 = 5;
const int servoPin = 9;

// Create servo object
Servo servo;

void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Initialize PIR sensor pin as input
  pinMode(pirPin, INPUT);

  // Initialize ultrasonic sensor pins
  pinMode(ultrasonicTrigPin1, OUTPUT);
  pinMode(ultrasonicEchoPin1, INPUT);
  pinMode(ultrasonicTrigPin2, OUTPUT);
  pinMode(ultrasonicEchoPin2, INPUT);

  // Attach servo to pin and set initial position to 0 degrees
  servo.attach(servoPin);
  servo.write(0);
}

void loop() {
  // Read distances from ultrasonic sensors
  long duration1, distance1, duration2, distance2;
  digitalWrite(ultrasonicTrigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(ultrasonicTrigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(ultrasonicTrigPin1, LOW);
  duration1 = pulseIn(ultrasonicEchoPin1, HIGH);
  distance1 = duration1 * 0.034 / 2;

  digitalWrite(ultrasonicTrigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(ultrasonicTrigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(ultrasonicTrigPin2, LOW);
  duration2 = pulseIn(ultrasonicEchoPin2, HIGH);
  distance2 = duration2 * 0.034 / 2;

  // Print distances to Serial Monitor
  Serial.print("Distance 1: ");
  Serial.print(distance1);
  Serial.print(" cm, Distance 2: ");
  Serial.print(distance2);
  
  // If the second ultrasonic sensor reads a distance less than 10cm, print a message
  if (distance2 <= 5) {
    Serial.println(" cm - Dustbin is filled and cannot be opened");
  } else {
    Serial.println(" cm");
  }

  // If an object is 5 cm away or closer
  if (distance1 <= 20 && distance2 > 5) {
    // Read PIR sensor input
    int pirValue = digitalRead(pirPin);

    // If motion is detected
    if (pirValue == HIGH) {
      Serial.println("Motion detected!");

      // Move servo to position 90 degrees
      servo.write(90);

      // Wait for 5 seconds
      delay(5000);

      // Move servo back to position 0 degrees
      servo.write(0);
    }
  }

  // Delay for 100 milliseconds
  delay(100);
}
