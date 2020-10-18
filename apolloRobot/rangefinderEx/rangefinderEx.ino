/**
 * Created by ArduinoGetStarted.com, modified by group Apollo
 *
 * This example code is in the public domain
 *
 * Tutorial page: https://arduinogetstarted.com/tutorials/arduino-ultrasonic-sensor-led
 */
#include <Servo.h>

const int TRIG_PIN = 3;
const int ECHO_PIN = 4;
const int LED_PIN  = 13; // onboard LED
const int DISTANCE_THRESHOLD = 15; // centimeters

float duration_us, distance_cm;

Servo servo1, servo2;

void setup() {
  Serial.begin (9600);
  
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  
  servo1.attach(6);
  servo2.attach(9);
}

void loop() {
  // generate 10-microsecond pulse to TRIG pin
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  duration_us = pulseIn(ECHO_PIN, HIGH); // measure duration of pulse from ECHO pin and compute distance
  distance_cm = 0.017 * duration_us;     // FIXME: output occasionally jumps to 2000+ cm in serial monitor
                                         //        something to watch for when programming the robot
  
  if(distance_cm < DISTANCE_THRESHOLD) {
    digitalWrite(LED_PIN, HIGH);
    servo1.write(25);
    servo2.write(100);
  } else {
    digitalWrite(LED_PIN, LOW);
    servo1.write(100);
    servo2.write(25);
  }

  Serial.print("distance: ");
  Serial.print(distance_cm);
  Serial.println(" cm");
  Serial.println(duration_us);

  delay(250);
}
