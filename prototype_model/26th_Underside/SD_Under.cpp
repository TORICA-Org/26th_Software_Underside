/*-----------------------
このファイルの役割：Under用SD用関数
更新日時：2026-03-11 17:09

------------------------*/

#include "SD_Under.h"

//ピン配置定義ファイルを読み込む
#include "Underside_config.h"

#include "parameters.h"

#include <SPI.h>


TORICA_SD sd(SD_CS, false); //引数なしでインスタンス化

char SD_BUF[256]; //SD書き込み用バッファ


//SD初期化コード
void initSD(){

    //↓Xiaoだとこれいらない．panicする
    // #ifdef ARDUINO_ARCH_RP2040 //RP2040およびRP2350のチェック用
    // SPI.setCS(SD_CS);
    // SPI.setSCK(SD_SCK);
    // SPI.setTX(SD_MOSI);
    // SPI.setRX(SD_MISO);
    // #endif

    SPI.begin();
    sd.begin(SD_CS);
}



//TORICA_SD内のバッファに保存
void save_SD_BUF(char* BUF){
    memset(SD_BUF, 0, sizeof(SD_BUF)); //SD_BUFを0で初期化

    sd.add_str(BUF);
}

void flashSD(){
    sd.flash(); //SD書き込み
}


//SDが生きてるか調べる関数
bool SDisActive(){
    if (sd.SDisActive == true){
        return true;
    } else {
        return false;
    }
}