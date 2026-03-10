//Xiao(rp2040)内蔵LED制御用関数

#include "LED.h"
#include <Arduino.h>

void init_intLED(){
    //PIN_LED_R, G, B はあらかじめ定義されている．
    //なおPIN_LED_R = 17, G = 16, B = 25に接続されている
    pinMode(PIN_LED_R, OUTPUT);
    pinMode(PIN_LED_G, OUTPUT);
    pinMode(PIN_LED_B, OUTPUT);
}

void write_intLED(bool status){
    digitalWrite(PIN_LED_R, status);
    digitalWrite(PIN_LED_G, status);
    digitalWrite(PIN_LED_G, status);
}