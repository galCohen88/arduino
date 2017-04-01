#include <pt.h> // ProtoThread Library
#include <clock.h>
#include <timer.h>

#define LEDPIN 13

// protothread instances
static struct pt pt1;
static struct pt pt2;

void setup(){
  Serial.begin(9600);
  pinMode(LEDPIN, OUTPUT);
}

static PT_THREAD(ledThread(struct pt *pt, int threadNumber, float delaySecs)){
  static struct timer t;
  PT_BEGIN(pt); // The begin of the protothread

  timer_set(&t, delaySecs*CLOCK_SECOND);

  while(1){
    // If the timer is expired, then continue the function
    // otherwhise it'll pass the processing resource to another thread

    Serial.print("thread ");
    Serial.print(threadNumber);
    Serial.print("\n");
    digitalWrite(LEDPIN, HIGH);

    PT_WAIT_UNTIL(pt, timer_expired(&t));
    digitalWrite(LEDPIN, LOW);

    timer_reset(&t);
    PT_WAIT_UNTIL(pt, timer_expired(&t));
    timer_reset(&t);
  }
  PT_END(pt); // The end of the protothread
}

void loop(){
  ledThread(&pt1, 1, 0.5);
  ledThread(&pt2, 2, 0.1);
}