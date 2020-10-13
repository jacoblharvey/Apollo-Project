/*
 * Created by ArduinoGetStarted.com
 *
 * This example code is in the public domain
 *
 * Tutorial page: https://arduinogetstarted.com/tutorials/arduino-ultrasonic-sensor-led
 */

const int TRIG_PIN = 3;  // trig pin connects to pin 3 on
const int ECHO_PIN = 4;  // echo pin connects to pin 4 on
const int LED_PIN  = 13; // onboard LED
const int DISTANCE_THRESHOLD = 20; // centimeters

float duration_us, distance_cm;

void setup() {
  Serial.begin (9600);       // initialize serial port
  pinMode(TRIG_PIN, OUTPUT); // set arduino pin to output mode
  pinMode(ECHO_PIN, INPUT);  // set arduino pin to input mode
  pinMode(LED_PIN, OUTPUT);  // set arduino pin to output mode
}

void loop() {
  // generate 10-microsecond pulse to TRIG pin
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

digitalWrite(12, HIGH);
  // measure duration of pulse from ECHO pin
  duration_us = pulseIn(ECHO_PIN, HIGH);
  // calculate the distance
  distance_cm = 0.017 * duration_us;
  if(distance_cm < DISTANCE_THRESHOLD) {
    digitalWrite(LED_PIN, HIGH); // turn on LED
  } else {
    digitalWrite(LED_PIN, LOW);  // turn off LED
  }
  Serial.print("distance: ");
  Serial.print(distance_cm);
  Serial.println(" cm");

  delay(500);
}
