#include <TORICA_basicfunc.h>
#include <TORICA_parameters.h>


//25代（竜海）基板向け
#include <Adafruit_DPS310.h>
#include <Wire.h>
#include <Adafruit_NeoPixel.h>
#include <TORICA_URM37.h>


Adafruit_DPS310 dps;
sensors_event_t temp_event, pressure_event;

int URECHO = 26;
int URTRIG = 27;

volatile float dps_pressure_hPa = 0;
volatile float dps_temperature_deg = 0;
volatile float dps_altitude_m = 0;
volatile float urm_altitude_m = 0;

int Power = 11;
int PIN = 12;
#define NUMPIXELS 1

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

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
  unsigned long last_timestamp = 0;  // unsigned int -> unsigned longに修正
};

Timer Timer1;
//Timer Timer2;


void setup() {
  // put your setup code here, to run once:

  Serial.begin(46000);

  Timer1.setInterval(50);

  pinMode(16, OUTPUT);
  pinMode(17, OUTPUT);
  pinMode(25, OUTPUT);

  Wire.setClock(400000);
  Wire.begin();

  Serial.println("DPS310");

  while (!dps.begin_I2C()) {  // Can pass in I2C address here
    //if (! dps.begin_SPI(DPS310_CS)) {  // If you want to use SPI
    Serial.println("Failed to find DPS");
    delay(100);
  }
  Serial.println("DPS OK!");
  dps.configurePressure(DPS310_32HZ, DPS310_16SAMPLES);
  dps.configureTemperature(DPS310_32HZ, DPS310_2SAMPLES);

  pinMode(Power, OUTPUT);
  digitalWrite(Power, HIGH);
  pixels.begin();

  TORICA_URM37_init(URTRIG, URECHO);
}

void loop() {
  Timer1.run([]() -> void {
    // put your main code here, to run repeatedly:
    pixels.clear();
    pixels.setPixelColor(0, pixels.Color(255, 0, 0));
    pixels.show();

    if (dps.temperatureAvailable() && dps.pressureAvailable()) {
      dps.getEvents(&temp_event, &pressure_event);

      dps_pressure_hPa = pressure_event.pressure;
      dps_temperature_deg = temp_event.temperature;
      dps_altitude_m = (powf(1013.25 / dps_pressure_hPa, 1 / 5.257) - 1) * (dps_temperature_deg + 273.15) / 0.0065;

      Serial.print("Temp: ");
      Serial.print(dps_temperature_deg);
      Serial.print(" C,  Pressure: ");
      Serial.print(dps_pressure_hPa);
      Serial.print(" hPa,  Altitude: ");
      Serial.print(dps_altitude_m);
      Serial.print(" m  |  ");
    }
    pixels.clear();
    pixels.show();

    pixels.setPixelColor(0, pixels.Color(0, 0, 255));
    pixels.show();
    urm_altitude_m = TORICA_URM37_getDistance_cm(URTRIG, URECHO) / 100.0;

    Serial.print("URM37 Altitude: ");
    Serial.print(urm_altitude_m);
    Serial.println(" m");

    pixels.clear();
    pixels.show();
  });
}
