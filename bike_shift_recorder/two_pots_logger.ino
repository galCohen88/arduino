/*
Robotale Potentiometer Sample Sketch
*/
const int potIn0 = A0;
const int potIn1 = A1;

int RawValue0= 0;
int RawValue1= 0;
float Voltage0 = 0;
float Voltage1 = 0;
float Resistance0 = 0;
float Resistance1 = 0;

void setup(){
  pinMode(potIn0, INPUT);
  pinMode(potIn1, INPUT);
  Serial.begin(9600);
}

void loop(){
  RawValue0 = analogRead(potIn0);
  RawValue1 = analogRead(potIn1);
  Voltage0 = (RawValue0 * 5.0 )/ 1024.0; // scale the ADC
  Voltage1 = (RawValue1 * 5.0 )/ 1024.0; // scale the ADC

  Resistance0 = 5000.0 * (RawValue0/1024.0); //5000 Refers to the resistance of potentiometer
  Resistance1 = 5000.0 * (RawValue1/1024.0);

  Serial.print("Raw Value pot0 = " );  // shows pre-scaled value
  Serial.print(RawValue0);
  Serial.print("Raw Value pot1 = " );  // shows pre-scaled value
  Serial.print(RawValue1);
  Serial.print("\t pot0 Voltage = "); // shows the voltage measured
  Serial.print(Voltage0,3); //3 digits after decimal point
  Serial.print("pot1 Voltage = "); // shows the voltage measured
  Serial.print(Voltage1,3); //3 digits after decimal point
  Serial.print("\t pot0 Resistance = "); // shows the voltage measured
  Serial.println(Resistance0);
  Serial.print("pot1 Resistance = "); // shows the voltage measured
  Serial.println(Resistance1);
  delay(500);   // 1/2 sec so your display doesnt't scroll too fast
}
