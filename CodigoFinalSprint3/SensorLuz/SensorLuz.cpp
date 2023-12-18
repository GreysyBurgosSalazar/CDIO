#include "SensorLuz.h"
#include <Arduino.h>


SensorLuz::SensorLuz(int canal,Adafruit_ADS1115& ads) : canalADS(canal), ads1(ads){
}

float SensorLuz::lecturaLuz() {
  float valorDigital = ads1.readADC_SingleEnded(canalADS);
  float luz = valorDigital * 4.096 / 32767;
  return luz;
  /*if (luz > 0.04) {
    return 10; // luz artificial
  } else if (luz > 0) {
    return 1; // luz natural
  } else {
    return 0; // oscuro
  }*/
}

void SensorLuz::mostrarLuz() {
  float lectura = lecturaLuz();
  Serial.println("Sistema de iluminación: ");
  if (lectura < 0) {
    Serial.println("Apagado. ····· A oscuras.");
  } else if (lectura > 0) {
    Serial.println("Activado.");
  /*} else {
    Serial.println("Apagado. ····· Luz natural.");
  }*/
}
}

void SensorLuz::enviarDatosLuz() {
  float datosLuz = lecturaLuz();
}