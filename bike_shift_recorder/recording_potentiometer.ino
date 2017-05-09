/************************************************************
This program is under the license of who ever wants to use it
Created by Gal Cohen (gal.nevis@gmail.com)

Connecting potentiometer
http://henrysbench.capnfatz.com/henrys-bench/arduino-sensors-and-input/robotale-slide-potentiometer-arduino-tutorial/
Coding the sd-card component (no level shifter in this project)
https://learn.sparkfun.com/tutorials/microsd-shield-and-sd-breakout-hookup-guide?_ga=2.165194172.2063893433.1494286498-184119552.1488831953#sd-card-breakout-boards
SD card Wiring diagram
https://learn.sparkfun.com/tutorials/microsd-breakout-with-level-shifter-hookup-guide
************************************************************/

#include <SPI.h>
#include <SD.h>

const int chipSelect = 8;

const int potIn = A0;

int RawValue= 0;
float Voltage = 0;
float Resistance = 0;

void setup(){
    pinMode(potIn, INPUT);
    Serial.begin(9600);



    Serial.print("Initializing SD card...");
    pinMode(10, OUTPUT);
    pinMode(chipSelect, OUTPUT);

    if (!SD.begin(chipSelect)) {
      Serial.println("Card failed, or not present");
      return;
    }
    Serial.println("card initialized.");

}

void loop(){
  RawValue = analogRead(potIn);
  Voltage = (RawValue * 5.0 )/ 1024.0;

  Resistance = 5000.0 * (RawValue/1024.0);

  Serial.print("Raw Value = " );
  Serial.print(RawValue);
  Serial.print("\t Voltage = ");
  Serial.print(Voltage,3);
  Serial.print("\t Resistance = ");
  Serial.println(Resistance);

  File dataFile = SD.open("potlog.txt", FILE_WRITE);
    if (dataFile) {
      dataFile.println(Resistance);
      dataFile.close();
      Serial.println(Resistance);
    }
    else {
      Serial.println("error opening datalog.txt");
    }

  delay(500);
}
