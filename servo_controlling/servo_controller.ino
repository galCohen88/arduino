/************************************************************
This program is under the license of who ever wants to use it
Created by Gal Cohen (gal.nevis@gmail.com)

This program will demonstrate how to control servo using arduino
without external power source (although when extended with shields
external power source is recommended)
************************************************************/

#include<Servo.h> // include server library

Servo ser; // create servo object to control the servo

int poser = 1; // initial position of server (angle relatively to servo Z axis)

int val; // initial variable for user input

void setup() {
    Serial.begin(9600); // Serial comm begin at 9600bps
    ser.attach(6); // servo is connected at pin 6, but can be attached to each pin
    ser.write(poser);
}

void loop() {
    if (Serial.available()){
        val = Serial.read();// then read the serial value
        if (val == 'o'){
            Serial.println(F("Opening"));
            ser.write(90);
            delay(2000);
            Serial.println(F("return"));
            ser.write(1);
        }
    }
}
