#include <Servo.h>

Servo myservo;

int pos = 0;    // variable to store the servo position

void setup() {
  myservo.attach(9);
}

void loop() {
  for (pos = 20; pos <= 160; pos += 1) { // goes from 20 degrees to 160 degrees
    // in steps of 1 degree
    myservo.write(pos);
    delay(5);
  }
  for (pos = 160; pos >= 20; pos -= 1) { // goes from 160 degrees to 20 degrees
    myservo.write(pos);
    delay(5);
  }
}
