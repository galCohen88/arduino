/*
Robotale Potentiometer Sample Sketch
*/
const int potIn = A0;

int RawValue= 0;
float Voltage = 0;
float Resistance = 0;

void setup(){  
  pinMode(potIn, INPUT);
  Serial.begin(9600);
}

void loop(){  
  RawValue = analogRead(potIn); 
  Voltage = (RawValue * 5.0 )/ 1024.0; // scale the ADC
  
  Resistance = 5000.0 * (RawValue/1024.0); //5000 Refers to the resistance of potentiometer
  
  Serial.print("Raw Value = " );  // shows pre-scaled value                    
  Serial.print(RawValue);      
  Serial.print("\t Voltage = "); // shows the voltage measured     
  Serial.print(Voltage,3); //3 digits after decimal point
  Serial.print("\t Resistance = "); // shows the voltage measured 
  Serial.println(Resistance); 
  delay(500);   // 1/2 sec so your display doesnt't scroll too fast
}
