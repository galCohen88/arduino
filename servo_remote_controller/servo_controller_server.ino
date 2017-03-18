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
const char myPSK[] = "WIFIPWD";

const String htmlHeader = "HTTP/1.1 200 OK\r\n"
                          "Content-Type: text/html\r\n"
                          "Connection: close\r\n\r\n"
                          "<!DOCTYPE HTML>\r\n"
                          "<html>\r\n";

const String responseContent = "Opening door";

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
  esp8266.pinMode(5, OUTPUT);

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

void serverListener()
{
  ESP8266Client client = server.available(500);
  blinkSeveralTimes(1, 0);
  if (client)
  {
    Serial.println(F("Client Connected!"));
    boolean currentLineIsBlank = true;
    while (client.connected())
    {
      if (client.available())
      {
        char c = client.read();
        if (c == '\n' && currentLineIsBlank)
        {
          Serial.println(F("Sending HTML page"));
          // send a standard http response header:
          client.print(htmlHeader);
          String htmlBody;
          htmlBody = responseContent;
          client.print(htmlBody);
          break;
        }
        if (c == '\n')
        {
          currentLineIsBlank = true;
        }
        else if (c != '\r')
        {
          currentLineIsBlank = false;
        }
      }
    }
    delay(1);
    client.stop();
    openAndClose();
    Serial.println(F("Client disconnected"));
  }

}
void openAndClose(){
    Serial.println(F("Open"));
    ser.attach(3);
    ser.write(1);
    delay(1000);
    Serial.println(F("Close"));
    ser.write(90);
    Serial.println(F("detach servo"));
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

void blinkSeveralTimes(int numberOfBlinks, int delayBetweenBlinks){
  int i = 0;
  for(i=0; i<numberOfBlinks; i++){
    esp8266.digitalWrite(5, HIGH);
    esp8266.digitalWrite(5, LOW);
    delay(delayBetweenBlinks);
  }
}
