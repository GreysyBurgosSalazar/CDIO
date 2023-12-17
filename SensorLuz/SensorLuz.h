#ifndef SensorLuz_h
#define SensorLuz_h

#include <Arduino.h>

class SensorLuz {
  private:
    int canalADS;

  public:
    SensorLuz(int canal);
    float lecturaLuz();
    void mostrarLuz();
    void enviarDatosLuz();
};

#endif