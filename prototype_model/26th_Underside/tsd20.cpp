#include <SerialPIO.h>
#include "tsd20.h"

#include "Underside_config.h"

#include tsd20_Serial(tsd20_RX, tsd20_TX, 256);

void init_tsd20(){
    //読み取り用Serial設定
    tsd20_Serial.begin(460800);
}

void read_tsd20(){
    if(tsd20_Serial.available() >= 4){
        //Frame Header読み取り
        if(tsd20_Serial.read() == 0x5C) {
            uint8_t dist_L = tsd20_Serial.read();
            uint8_t dist_H = tsd20_Serial.read();
            uint8_t recv_chk = tsd20_Serial.read();
        }
    }
}