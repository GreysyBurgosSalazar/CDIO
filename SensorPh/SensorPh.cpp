#include "SensorPh.h"
#include <Arduino.h>

SensorPh::SensorPh(int canal, float offsetPh,Adafruit_ADS1115& ads): canalADS(canal), offset(offsetPh), ads1(ads) {
}

float SensorPh::lecturaPh() {
  float valorDigital = ads1.readADC_SingleEnded(canalADS);
  float voltios = valorDigital * (4.096 / 32767.0);
  float ph = (3.5 * voltios) + offset;
  return ph;
}

void SensorPh::mostrarPh() {
  float lectura = lecturaPh();
  Serial.println("Nivel de pH: ");
  Serial.println(lectura);
  //Warning
  if (lectura < 5.5 || lectura > 7.5) {
    Serial.println("AGUA CONTAMINADA!!!");
  }
}