#ifndef SensorPh_h
#define SensorPh_h

#include <Arduino.h>

class SensorPh {
  private:
    int canalADS;
    float offset;

  public:
    SensorPh(int canal, float offsetPh);
    float lecturaPh();
    void mostrarPh();
    void enviarDatosPh();
};

#endif