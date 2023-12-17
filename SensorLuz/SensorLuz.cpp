#include "SensorLuz.h"
#include <Arduino.h>

SensorLuz::SensorLuz(int canal) {
  canalADS = canal;
}

float SensorLuz::lecturaLuz() {
  float valorDigital = ads.readADC_SingleEnded(canalADS);
  float luz = valorDigital * 4.096 / 32767;
  if (luz > 0.03) {
    return 10; // luz artificial
  } else if (luz > 0) {
    return 1; // luz natural
  } else {
    return 0; // oscuro
  }
}

void SensorLuz::mostrarLuz() {
  float lectura = lecturaLuz();
  Serial.println("Sistema de iluminación: ");
  if (lectura == 0) {
    Serial.println("Apagado. ····· A oscuras.");
  } else if (lectura == 10) {
    Serial.println("Activado.");
  } else {
    Serial.println("Apagado. ····· Luz natural.");
  }
}

void SensorLuz::enviarDatosLuz() {
  float datosLuz = lecturaLuz();
}