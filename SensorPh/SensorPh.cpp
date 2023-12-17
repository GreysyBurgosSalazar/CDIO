#include "SensorPh.h"
#include <Arduino.h>

SensorPh::SensorPh(int canal, float offsetPh) {
  canalADS = canal;
  offset = offsetPh;
}

float SensorPh::lecturaPh() {
  float valorDigital = ads.readADC_SingleEnded(canalADS);
  float voltios = valorDigital * (4.096 / 32767.0);
  float ph = (3.5 * voltios) + offset;
  return ph;
}

void SensorPh::mostrarPh() {
  float lectura = lecturaPh();
  Serial.println("Nivel de Ph: ");
  Serial.println(lectura);
  //Warning
  if (lectura < 5.5 || lectura > 7.5) {
    Serial.println("AGUA CONTAMINADA!!!");
  }
}

void SensorPh::enviarDatosPh() {
  float datosPh = lecturaPh();
}