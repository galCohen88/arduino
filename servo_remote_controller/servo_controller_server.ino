/************************************************************
This program is under the license of who ever wants to use it
Created by Gal Cohen (gal.nevis@gmail.com)

This program will demonstrate how it's possible controlling an
external servo using arduino, WIFI shield and external power source

I detached the servo from the board using the detach() function
in order to avoid 'noise' vibrations caused by creating objects
and current changes.

Added delay between two 'open' commands for the servo motor
to finish movement
************************************************************/

#include <SoftwareSerial.h>
#include <SparkFunESP8266WiFi.h>
#include<Servo.h>

const char mySSID[] = "WIFI";
const char myPSK[] = "WIFIPASS";

unsigned long old_time;
unsigned long new_time;

ESP8266Server server = ESP8266Server(80);

Servo ser; // create servo object to control a servo

int val; // initial value of input

void setup(){
  Serial.begin(9600);
  ser.attach(3);
  ser.write(90);
  delay(1000);
  ser.detach();

  old_time = millis();
  new_time = 0;

  initializeESP8266();
  connectESP8266();
  displayConnectInfo();
  serverSetup();
}

void loop(){
  serverListener();
}

void initializeESP8266(){
  int test = esp8266.begin();
  if (test != true){
    Serial.println(F("Error talking to ESP8266."));
    errorLoop(test);
  }
  Serial.println(F("ESP8266 Shield Present"));
}

void connectESP8266(){
  int retVal = esp8266.getMode();
  if (retVal != ESP8266_MODE_STA){
    retVal = esp8266.setMode(ESP8266_MODE_STA);
    if (retVal < 0){
      Serial.println(F("Error setting mode."));
      errorLoop(retVal);
    }
  }

  Serial.println(F("Mode set to station"));
  retVal = esp8266.status();
  if (retVal <= 0){
    Serial.print(F("Connecting to "));
    Serial.println(mySSID);
    retVal = esp8266.connect(mySSID, myPSK);
    if (retVal < 0){
      Serial.println(F("Error connecting"));
      errorLoop(retVal);
    }
  }
}

void displayConnectInfo(){
  char connectedSSID[24];
  memset(connectedSSID, 0, 24);
  int retVal = esp8266.getAP(connectedSSID);
  if (retVal > 0){
    Serial.print(F("Connected to: "));
    Serial.println(connectedSSID);
  }
  IPAddress myIP = esp8266.localIP();
  Serial.print(F("My IP: ")); Serial.println(myIP);
}


void serverSetup(){
  server.begin();
  Serial.print(F("Server started! Go to "));
  Serial.println(esp8266.localIP());
  Serial.println();
}

ESP8266Client client;

void serverListener(){
  Serial.println(F("loop"));
  client = server.available(1000);
  if (client){
    Serial.println(F("Client Connected!"));
    while (client.connected()){
      client.stop();
      delay(10);
    }
    new_time = millis();
    Serial.println(new_time - old_time);
    if(new_time - old_time > 5000){
      old_time = millis();
      openAndClose();
    }
  }
}

void openAndClose(){
    Serial.println(F("Open"));
    ser.attach(3);
    ser.write(1);
    delay(1000);
    Serial.println(F("Close"));
    ser.write(90);
    Serial.println(F("Client disconnected. detach"));
    delay(1000);
    ser.detach();
}

void errorLoop(int error)
{
  Serial.print(F("Error: ")); Serial.println(error);
  Serial.println(F("Looping forever."));
  for (;;)
    ;
}
