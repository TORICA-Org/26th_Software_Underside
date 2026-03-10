#include "TORICA_parameters.h"
#include "Underside_config.h"
#include "UARTHelper_Under.h"
#include "DPS310.h"
#include "LED.h"
#include "NeoPixel.h"
#include "SD_Under.h"
#include "URM37.h"


#include <Wire.h>


//100Hz周期実行用
class Timer {
public:
  void setInterval(int _interval) {
    interval = _interval;
  }

  void run(void (*function)()) {
    // 引数([戻り値の型] *([ポインタ変数名])([引数情報]))
    if (millis() - last_timestamp >= interval) {
      last_timestamp = millis();
      function();
    }
  }

private:
  int interval = 0;
  unsigned long last_timestamp = 0;
};

Timer Timer1;
Timer Timer2;



void setup() {
  // put your setup code here, to run once:
  Serial.begin(460800);  //DEBUG用シリアル

  initUART();

  Wire.setSDA(Under_SDA);
  Wire.setSCL(Under_SCL);
  Wire.begin();
  Wire.setClock(400000);

  init_DPS310();

  init_NeoPixel();

  Serial.println("Setup Done.");


  Timer1.setInterval(50);  //10ms(=100Hz)ごとにTimer1内の動作を実行
}

void setup1() {

  init_echo();

  initSD();

  init_intLED();

  
  Serial.println("Setup1 Done.");

  for (int i = 0; i<=3; i++){
    write_intLED(1);
    delay(500);
    write_intLED(0);
    delay(500);
  }
  write_intLED(0);

  Timer2.setInterval(1000);  //100ms(=10Hz)ごとにTimer2の内容を実行
}


void loop() {
  Timer1.run([]() -> void {
    while (receive_available() == true) {
      Lightup_NeoPixel(RED);
      receiveLog();
      save_SD_BUF(readUART_BUF);

      if (receive_available() == false) {
        delay(1);
      }

      NeoPixel_off();
    }

    if (DPS310_is_OK() == true) {
      Lightup_NeoPixel(BLUE);
      read_dps();
      NeoPixel_off();
    }

    flashSD();

/*
    Serial.print("URM altitude: ");
    Serial.println(data_under_urm_altitude_m);
    Serial.print("Pressure: ");
    Serial.print(data_under_bmp_pressure_hPa);
    Serial.print("  Temperature: ");
    Serial.println(data_under_bmp_temperature_deg);
*/

  });
}


void loop1() {
  Timer2.run([]() -> void {
    write_intLED(HIGH);
    
    read_echo();

    Serial.print("URM altitude: ");
    Serial.println(data_under_urm_altitude_m);

    write_intLED(LOW);

  });
}
