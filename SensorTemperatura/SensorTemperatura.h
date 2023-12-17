#ifndef SensorTemperatura_h
#define SensorTemperatura_h

#include <Arduino.h>

class SensorTemperatura {
  private:
    int canalADS;

  public:
    SensorTemperatura(int canal);
    float lecturaTemperatura();
    void mostrarTemperatura();
    void enviarDatosTemperatura();
};

#endif