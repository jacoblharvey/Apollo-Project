/**
 * Authors: Sharif Akil, Pamela Hernandez Villalba, Helena Holland, Brent Fairchild, Jacob Harvey
 * Date:    2020/10/14
 * Version: 0.5
 * 
 * This program provides directions for our robot in order to complete the tasks
 * specified in https://github.com/jacoblharvey/Apollo-Project/blob/main/README.md
 * 
 * GitHub for project: https://github.com/jacoblharvey/Apollo-Project
 */
#include <Servo.h>

// rangefinder
const int TRIG_PIN = 3;
const int ECHO_PIN = 4;
const int LED_PIN  = 13; // onboard LED
// TODO: verify accuracy of rangefinder before final release
int distanceThreshold = 120; // centimeters

float duration_us, distance_cm;
int result;

Servo leftWheel, rightWheel, frontSpike, rearSpike, cubeDrop;

void setup() {
    Serial.begin(9600);
    // rangefinder pins
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    pinMode(LED_PIN, OUTPUT);
    // servo pins
    leftWheel.attach(); // TODO: specify pins depending on which work best for layout
    rightWheel.attach();
    frontSpike.attach();
    rearSpike.attach();
    cubeDrop.attach();
}

void loop() {
    // loops for checking distance, e.g. result = 1 stops execution of corresponding phase
    // generate 10-microsecond pulse to TRIG pin
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    duration_us = pulseIn(ECHO_PIN, HIGH); // measure duration of pulse from ECHO pin and compute distance
    distance_cm = 0.017 * duration_us;     // FIXME: output occasionally jumps to 2000+ cm in serial monitor
    // loop for phase 1
    if(distance_cm >= distanceThreshold) {
        result = 1;
    } else {
        result = 0;
    }
    // loop for phase 3
    distanceThreshold = 20;
    if(distance_cm <= distanceThreshold) {
        result = 3;
    } else {
        result = 0;
    }
    // TODO: implement phase 1
    /**
     * Phase 1: travel to drop off point
     *   rotate wheel servos
     *   rear spike down - might be able to just keep spike down for phase
     *   reset wheel servos
     *   rear spike up
     *   repeat until result = 1
     */

    // TODO: implement phase 2
    /**
     * Phase 2: drop cube at drop off point
     *   rotate cubeDrop servo downwards
     *   wait for cube to slide off
     *   rotate cubeDrop servo upwards
     */

    // TODO: implement phase 3
    /**
     * Phase 3: travel toward base
     *   rotate wheel servos opposite direction of phase 1
     *   front spike down - might be able to just keep spike down for phase
     *   reset wheel servos
     *   front spike up
     *   repeat until result = 1
     */
}
