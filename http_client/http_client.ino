#include <SoftwareSerial.h>
#include <SparkFunESP8266WiFi.h>

const char mySSID[] = "oded";
const char myPSK[] = "12345678";

const char destServer[] = "example.com";
const String httpRequest = "GET / HTTP/1.1\n"
                           "Connection: close\n\n";
void setup()
{
  Serial.begin(9600);
  serialTrigger(F("Press any key to begin."));
  initializeESP8266();
  connectESP8266();
  displayConnectInfo();
}

void loop(){
  post();
  delay(2000);
}

void initializeESP8266()
{
  int test = esp8266.begin();
  if (test != true)
  {
    Serial.println(F("Error talking to ESP8266."));
    errorLoop(test);
  }
  Serial.println(F("ESP8266 Shield Present"));
}

void connectESP8266()
{
  int retVal = esp8266.getMode();
  if (retVal != ESP8266_MODE_STA)
  {
    retVal = esp8266.setMode(ESP8266_MODE_STA);
    if (retVal < 0)
    {
      Serial.println(F("Error setting mode."));
      errorLoop(retVal);
    }
  }
  Serial.println(F("Mode set to station"));

  retVal = esp8266.status();
  if (retVal <= 0)
  {
    Serial.print(F("Connecting to "));
    Serial.println(mySSID);
    retVal = esp8266.connect(mySSID, myPSK);
    if (retVal < 0)
    {
      Serial.println(F("Error connecting"));
      errorLoop(retVal);
    }
  }
}

void displayConnectInfo()
{
  char connectedSSID[24];
  memset(connectedSSID, 0, 24);
  int retVal = esp8266.getAP(connectedSSID);
  if (retVal > 0)
  {
    Serial.print(F("Connected to: "));
    Serial.println(connectedSSID);
  }

  IPAddress myIP = esp8266.localIP();
  Serial.print(F("My IP: ")); Serial.println(myIP);
}

void post()
{

  ESP8266Client client;

  int retVal = client.connect(destServer, 80);
  if (retVal <= 0)
  {
    Serial.println(F("Failed to connect to server."));
    return;
  }

  client.print(httpRequest);

  while (client.available())
    Serial.write(client.read());

  if (client.connected())
    client.stop(); 
}


void errorLoop(int error)
{
  Serial.print(F("Error: ")); Serial.println(error);
  Serial.println(F("Looping forever."));
  for (;;)
    ;
}

void serialTrigger(String message)
{
  Serial.println();
  Serial.println(message);
  Serial.println();
  while (!Serial.available())
    ;
  while (Serial.available())
    Serial.read();
}