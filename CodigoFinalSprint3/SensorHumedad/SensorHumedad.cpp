#include "SensorHumedad.h"

SensorHumedad::SensorHumedad(int canal,Adafruit_ADS1115& ads): canalADS(canal), ads1(ads) {
}

int SensorHumedad::lecturaHumedad() {
  int valorDigital = ads1.readADC_SingleEnded(canalADS);
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
  int datosHumedad = lecturaHumedad();
}