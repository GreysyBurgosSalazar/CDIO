#include "SensorTemperatura.h"
#include <Arduino.h>


SensorTemperatura::SensorTemperatura(int canal, Adafruit_ADS1115& ads) : canalADS(canal), ads1(ads){
}

float SensorTemperatura::lecturaTemperatura() {
  float valorDigital = ads1.readADC_SingleEnded(canalADS);
  float temperatura = (valorDigital - 3435.4) / 412.1;
  return temperatura;
}

void SensorTemperatura::mostrarTemperatura() {
  float lecturaCelsius = lecturaTemperatura();
  Serial.println("Temperatura:");
  Serial.println(lecturaCelsius);  
  Serial.println("ºC");                
  //Warning
  if (lecturaCelsius >= 35) {
    Serial.println("TEMPERATURA ELEVADA!!!");
  }
}