#ifndef SensorHumedad_h
#define SensorHumedad_h
#include <Arduino.h> 

class SensorHumedad {
  private:
    int canalADS;

  public:
    SensorHumedad(int canal);
    int lecturaHumedad();
    void mostrarHumedad();
    void enviarDatosHumedad();
};

#endif