/**
 * Authors: Sharif Akil, Pamela Hernandez Villalba, Helena Holland, Brent Fairchild, Jacob Harvey
 * Date:    2020/11/19
 * Version: 1.2.1
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
// button
const int BUTTON_PIN = 5;
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
    frontSpike.write(65);
    delay(500);
    leftWheel.write(50);
    rightWheel.write(150);
    delay(500);
    frontSpike.write(92);
    delay(500);
    cubeDrop.write(60);
    // button pin
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    // print logo to serial monitor
    Serial.println("");
    Serial.println("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -");
    Serial.println("          AAAAAAAAAAA    PPPPPPPPP,      ,OOOOOOO,     LL             LL              ,OOOOOOO, ");
    Serial.println("         AA       AA    PP       PP    OO       OO    LL             LL             OO       OO");
    Serial.println("        AA       AA    PP       PP    OO       OO    LL             LL             OO       OO");
    Serial.println("       AA       AA    PP       PP    OO       OO    LL             LL             OO       OO");
    Serial.println("      AAAAAAAAAAA    PPPPPPPPP’     OO       OO    LL             LL             OO       OO");
    Serial.println("     AA       AA    PP             OO       OO    LL             LL             OO       OO");
    Serial.println("    AA       AA    PP             OO       OO    LL             LL             OO       OO");
    Serial.println("   AA       AA    PP             OO       OO    LL             LL             OO       OO");
    Serial.println("  AA       AA    PP              ‘OOOOOOO’      ’L'L'L'L'L     ’L'L'L'L'L     ’OOOOOOO’ ");
    Serial.println("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -");
    Serial.println("");
    Serial.println("Starting Run ...");
}

int checkButton() {
    int condition;
    if(digitalRead(BUTTON_PIN) == 0) { // return 1 if button is pressed (reads LOW voltage)
        condition = 1;
    } else {
        condition = 0;
    }
    return condition;
}

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
            distanceThreshold = 30; // centimeters
            if(distance_cm >= distanceThreshold) { // 1 for within threshold, 0 for out of threshold
                Serial.print("Distance: "); // print distance to serial monitor
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
            distanceThreshold = 130; // centimeters
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

void loop() {
    if(checkButton() == 1) { // don't execute phases 1-3 until the button is pressed
        /**
         * Phase 1: travel to drop off point
         *   rotate wheel servos
         *   front spike down
         *   reset wheel servos
         *   front spike up
         *   repeat until result = 0
         */
        delay(1000);
        inRange = checkDistance(1);
        phaseStep = 1;
        Serial.println("Entering phase 1 ...");
        while(inRange == 1) {
            switch(phaseStep) {
                case 1:
                    posR = 145;
                    for(posL = 50; posL <=140; posL += 1) {
                        leftWheel.write(posL);
                        rightWheel.write(posR);
                        delay(4); // ms, higher values slow rotation
                        posR -= 1;
                    }
                    delay(500);
                    phaseStep = 2;
                    break;
                case 2:
                    delay(500);
                    frontSpike.write(65);
                    delay(1000);
                    leftWheel.write(50);
                    delay(500);
                    rightWheel.write(175);
                    delay(1000);
                    frontSpike.write(92);
                    delay(1000);
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
        frontSpike.write(65);
        delay(1000);
        cubeDrop.write(125);
        delay(1000);
        cubeDrop.write(60);
        delay(1000);
        // set up wheels for phase 3
        leftWheel.write(130);
        rightWheel.write(90);
        delay(1000);
        frontSpike.write(92);
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
                    posR = 90;
                    for(posL = 130; posL >=65; posL -= 1) {
                        leftWheel.write(posL);
                        rightWheel.write(posR);
                        delay(4);
                        posR += 1;
                    }
                    delay(500);
                    phaseStep = 2;
                    break;
                case 2:
                    delay(500);
                    frontSpike.write(65);
                    delay(1000);
                    leftWheel.write(130);
                    delay(500);
                    rightWheel.write(75);
                    delay(1000);
                    frontSpike.write(92);
                    delay(1000);
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
    delay(200);
}
