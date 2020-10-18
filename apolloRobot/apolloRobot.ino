/**
 * Authors: Sharif Akil, Pamela Hernandez Villalba, Helena Holland, Brent Fairchild, Jacob Harvey
 * Date:    2020/10/18
 * Version: 0.5.2
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
// wheels
const int RIGHT_PIN = 8;
const int LEFT_PIN = 6;
// spikes
const int FRONT_PIN = 1;
const int REAR_PIN = 10;
// cube drop
const int DROP_PIN = 7;
// TODO: verify accuracy of rangefinder before final release
int distanceThreshold, inRange, phaseStep;
float duration_us, distance_cm;

Servo leftWheel, rightWheel, frontSpike, rearSpike, cubeDrop;

void setup() {
    Serial.begin(9600);
    // rangefinder pins
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    // servo pins
    rightWheel.attach(RIGHT_PIN);
    leftWheel.attach(LEFT_PIN);
    frontSpike.attach(FRONT_PIN);
    rearSpike.attach(REAR_PIN);
    cubeDrop.attach(DROP_PIN);
}

int checkDistance(int phase) {
    int condition;
    // generate 10-microsecond pulse to TRIG pin
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    duration_us = pulseIn(ECHO_PIN, HIGH); // measure duration of pulse from ECHO pin and compute distance
    distance_cm = 0.017 * duration_us;     // FIXME: serial monitor output fluctuates

    switch(phase) {
        case 1:
            distanceThreshold = 20; // TODO: switch to microseconds to remove need for distance calculation
            if(distance_cm >= distanceThreshold) { // 1 for within threshold, 0 for out of threshold
                Serial.print(distance_cm);
                Serial.println(" cm");
                condition = 1;
            } else {
                Serial.print(distance_cm);
                Serial.println(" cm");
                condition = 0;
            }
            break;
        case 3:
            distanceThreshold = 10; // centimeters
            if(distance_cm <= distanceThreshold) { // 0 for within threshold, 1 for out of threshold
                Serial.print(distance_cm);
                Serial.println(" cm");
                condition = 1;
            } else {
                Serial.print(distance_cm);
                Serial.println(" cm");
                condition = 0;
            }
            break;
    }
    return condition;
}

void loop() {
    // TODO: implement button read to begin program
    // TODO: implement phase 1
    /**
     * Phase 1: travel to drop off point
     *   rotate wheel servos
     *   rear spike down - might be able to just keep spike down for phase
     *   reset wheel servos
     *   rear spike up
     *   repeat until result = 0
     */
    inRange = checkDistance(1);
    phaseStep = 1;
//rearSpike.write(25); TODO: lower spike before moving
    // main movement loop for phase 1
    while(inRange == 1) {
        switch(phaseStep) {
            case 1:
                leftWheel.write(25);
                rightWheel.write(25);
                delay(500);
                phaseStep = 2;
                break;
            case 2:
                leftWheel.write(100);
                delay(500);
                rightWheel.write(100);
                delay(500);
                phaseStep = 3;
                break;
            case 3:
                inRange = checkDistance(1);
                Serial.print("Checking distance ... ");
                Serial.println(inRange);
                delay(250);
                if(inRange != 0) {
                    inRange = 1;
                    phaseStep = 1;
                } else {
                    inRange = 0;
                }
                break;
        }
    }
//rearSpike.write(100); // ver 0.5.1: once inRange = 0, program skips while loop and repeatedly sets servo to 25 then 100

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
     *   repeat until result = 0
     */
}
