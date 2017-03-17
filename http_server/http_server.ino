/************************************************************
This program is under the license of who ever wants to use it
Created by Gal Cohen (gal.nevis@gmail.com)

This program will demonstrate Arduinos' ability of handling http request
The 'loop' function is used as the 'event listener' or as the 'event loop'
ESP8266 is the WIFI component i'm using for this project
I got the sparkfun shield which makes it easier to work with:
https://www.sparkfun.com/products/13287
************************************************************/


#include <SoftwareSerial.h>
#include <SparkFunESP8266WiFi.h>

const char mySSID[] = "WIFI";
const char myPSK[] = "WIFIPWD";

ESP8266Server server = ESP8266Server(80);

const char destServer[] = "example.com";
const String htmlHeader = "HTTP/1.1 200 OK\r\n"
                          "Content-Type: text/html\r\n"
                          "Connection: close\r\n\r\n"
                          "<!DOCTYPE HTML>\r\n"
                          "<html>\r\n";

const String httpRequest = "GET / HTTP/1.1\n"
                           "Host: example.com\n"
                           "Connection: close\n\n";

void setup(){

  Serial.begin(9600);

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
    if (retVal < 0)
    {
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


void serverSetup()
{
  server.begin();
  Serial.print(F("Server started! Go to "));
  Serial.println(esp8266.localIP());
  Serial.println();
}


void serverListener(){
  ESP8266Client client = server.available(500);

  if (client){
    Serial.println(F("Client Connected!"));
    boolean currentLineIsBlank = true;

    while (client.connected()){
      if (client.available()){
        char c = client.read();
        if (c == '\n' && currentLineIsBlank){
          Serial.println(F("Sending HTML page"));
          client.print(htmlHeader);
          String htmlBody;
          htmlBody+= "This is the served content";
          htmlBody += "</html>\n";
          client.print(htmlBody);
          break;
        }
        if (c == '\n'){
          currentLineIsBlank = true;
        }
        else if (c != '\r'){
          currentLineIsBlank = false;
        }
      }
    }
    delay(1);
    client.stop();
    Serial.println(F("Client disconnected"));
  }
}

void errorLoop(int error){
  Serial.print(F("Error: ")); Serial.println(error);
  Serial.println(F("Looping forever."));
  for (;;)
    ;
}
