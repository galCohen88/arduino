/************************************************************
This program is under the license of who ever wants to use it
Created by Gal Cohen (gal.nevis@gmail.com)

This program will demonstrate Arduinos' ability of handling recursive functions
************************************************************/


int led = 13;

void setup(){
  pinMode(led, OUTPUT);
  recurse(1, 1);
}

void loop(){
  // nothing here (mandatory method)
}

void recurse(long i, long direction){
   // delay between blinks will change according to recursion depth

  if(i == 100){
     direction = 0;
  }
  if(i == 1){
    direction = 1;
  }

  digitalWrite(led, HIGH);
  delay(i);
  digitalWrite(led, LOW);
  delay(i);


  if(direction == 0){
   recurse(i-1, direction);
  }
  else{
   recurse(i+1, direction);
  }

}
