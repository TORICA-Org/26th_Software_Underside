#include "LED.h"

void setup() {
  // put your setup code here, to run once:
  init_intLED();
}

void setup1(){
  
}

void loop(){

}

void loop1() {
  // put your main code here, to run repeatedly:
  write_intLED(1);
  delay(500);
  write_intLED(0);
  delay(500);
}
