#include "SensorHumedad.h"
#include <Arduino.h> 
#include <Adafruit_ADS1X15.h>
Adafruit_ADS1115 ads;

SensorHumedad::SensorHumedad(int canal) {
  canalADS = canal;
}

int SensorHumedad::lecturaHumedad() {
  int valorDigital = ads.readADC_SingleEnded(canalADS);
  int humedad = map(valorDigital, 30900, 16000, 0, 100);
  if (humedad > 100) {
    humedad = 100;
  }
  if (humedad < 0) {
    humedad = 0;
  }
  return humedad;
}

void SensorHumedad::mostrarHumedad() {
  int lectura = lecturaHumedad();
  Serial.println("Humedad: ");
  Serial.println(lectura);
  Serial.println("%");
  // Warning
  if (lectura <= 10) {
    Serial.println("HUMEDAD BAJA!!!");
  }
}

void SensorHumedad::enviarDatosHumedad() {
  int datosHumedad = lecturaHumedad()
}