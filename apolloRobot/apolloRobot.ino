/**
 * Authors: Sharif Akil, Pamela Hernandez Villalba, Helena Holland, Brent Fairchild, Jacob Harvey
 * Date:    2020/10/30
 * Version: 1.0
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
// spike
const int FRONT_PIN = 2;
// cube drop
const int DROP_PIN = 7;
// misc values
int distanceThreshold, inRange, phaseStep, posL, posR;

Servo leftWheel, rightWheel, frontSpike, cubeDrop;

void setup() {
    Serial.begin(9600);
    // rangefinder pins
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    // servo pins
    rightWheel.attach(RIGHT_PIN);
    leftWheel.attach(LEFT_PIN);
    frontSpike.attach(FRONT_PIN);
    cubeDrop.attach(DROP_PIN);
    // initialize servo positions
    leftWheel.write(20);
    rightWheel.write(170);
    frontSpike.write(100);
    cubeDrop.write(50);

    Serial.println("Starting Run ...");
}

//int readButton() {
//    int condition;
//    // TODO: implement function to halt program execution until button is pressed
//    return condition;
//}

int checkDistance(int phase) {
    int condition;
    float duration_us, distance_cm;
    // generate 10-microsecond pulse to TRIG pin and measure duration of pulse from ECHO pin
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);
    duration_us = pulseIn(ECHO_PIN, HIGH); // measure duration of pulse from ECHO pin and compute distance
    distance_cm = 0.017 * duration_us;

    switch(phase) {
        case 1:
            distanceThreshold = 25;
            if(distance_cm >= distanceThreshold) { // 1 for within threshold, 0 for out of threshold
                Serial.print("Distance: ");
                Serial.print(distance_cm);
                Serial.println(" cm");
                condition = 1;
            } else {
                Serial.print("Distance: ");
                Serial.print(distance_cm);
                Serial.println(" cm");
                condition = 0;
            }
            break;
        case 3:
            distanceThreshold = 125;
            if(distance_cm <= distanceThreshold) { // 0 for within threshold, 1 for out of threshold
                Serial.print("Distance: ");
                Serial.print(distance_cm);
                Serial.println(" cm");
                condition = 1;
            } else {
                Serial.print("Distance: ");
                Serial.print(distance_cm);
                Serial.println(" cm");
                condition = 0;
            }
            break;
    }
    return condition;
}

//void executePhase(int phase);
//    // TODO: move main code blocks from loop() into seperate switch statements for each phase
//    //         this would ease the implementation of readButton() and simplify the main loop() program
//    return;
//}

void loop() {
    // TODO: call readButton
    // TODO: call executePhase
    /**
     * Phase 1: travel to drop off point
     *   rotate wheel servos
     *   front spike down
     *   reset wheel servos
     *   front spike up
     *   repeat until result = 0
     */
    inRange = checkDistance(1);
    phaseStep = 1;
    Serial.println("Entering phase 1 ...");
    while(inRange == 1) {
        switch(phaseStep) {
            case 1:
                posR = 170;
                for(posL = 20; posL <=160; posL += 1) { // rotate both servos simultaneously
                    leftWheel.write(posL);
                    rightWheel.write(posR);
                    delay(4);
                    posR -= 1;
                }
                delay(500);
                phaseStep = 2;
                break;
            case 2:
                delay(500);
                frontSpike.write(50);
                delay(1000);
                leftWheel.write(35);
                delay(500);
                rightWheel.write(180);
                delay(1000);
                frontSpike.write(100);
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
    /**
     * Phase 2: drop cube at drop off point
     *   rotate cubeDrop servo downwards
     *   wait for cube to slide off
     *   rotate cubeDrop servo upwards
     */
    Serial.println("Entering phase 2 ...");
    delay(1000);
    cubeDrop.write(110);
    delay(2000);
    cubeDrop.write(50);
    delay(1000);
    /**
     * Phase 3: travel toward base
     *   rotate wheel servos opposite direction of phase 1
     *   front spike down - might be able to just keep spike down for phase
     *   reset wheel servos
     *   front spike up
     *   repeat until result = 0
     */
    inRange = checkDistance(3); // reset inRange as = 1
    phaseStep = 1; // reset phaseStep for phase 3
    Serial.println("Entering phase 3 ...");
    while(inRange == 1) {
        switch(phaseStep) {
            case 1:
                posR = 65;
                for(posL = 167; posL >=33; posL -= 1) {
                    leftWheel.write(posL);
                    rightWheel.write(posR);
                    delay(4); // ms, higher values slow rotation
                    posR += 1;
                }
                delay(500);
                phaseStep = 2;
                break;
            case 2:
                delay(500);
                frontSpike.write(50);
                delay(1000);
                leftWheel.write(167);
                delay(500);
                rightWheel.write(20);
                delay(1000);
                frontSpike.write(100);
                delay(500);
                phaseStep = 3;
                break;
            case 3:
                inRange = checkDistance(3);
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
}
