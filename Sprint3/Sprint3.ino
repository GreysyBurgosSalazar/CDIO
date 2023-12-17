#define power_pin 5
#include <Adafruit_ADS1X15.h>
#include <SensorTemperatura.h>
#include <SensorPh.h>
#include <SensorHumedad.h>
#include <SensorLuz.h>

Adafruit_ADS1115 ads;

int medirSalinidad() { 
  int16_t adc0;
  digitalWrite(power_pin, HIGH);
  delay(500);
  adc0 = analogRead(A0); 
  digitalWrite(power_pin, LOW);
  delay(500);
  if (adc0<800){
    return 0;
  }
  else {
  //int salinityValue = (adc0 - 793.48) / (6.1486);  
  int salinidad = (adc0 - 841.9)/(3.9143);
  return salinidad;
  }
}

void mostrarSalinidad() { 
  int lecturaSalinidad = medirSalinidad();
  Serial.println("Salinidad: ");
  Serial.println(lecturaSalinidad);
  Serial.println("gr/l");
}

//----------------------------------------------------------------------------------------------------
void initializeSparkfun() {
  pinMode(power_pin, OUTPUT);//Pin choosen for Salinity Sensor
  Serial.begin(9600);
}
//----------------------------------------------------------------------------------------------------
void initializeADS() {
  ads.begin();
  ads.setGain(GAIN_ONE);//Voltage in ADS +-4.096
}
//----------------------------------------------------------------------------------------------------

void setup() {
  initializeSparkfun();
  initializeADS();
}  

void loop() {
//Creo los objetos tipo sensor
  SensorTemperatura sensorTemp(1); 
  SensorPh sensorPh(2, 0.05);
  SensorHumedad sensorHum(0); 
  SensorLuz sensorLuz(3);

  mostrarSalinidad();
  sensorHum.mostrarHumedad();
  //sensorPh.mostrarPh();
  //sensorTemp.mostrarTemperatura();
  //sensorLuz.mostrarLuz();
  
  delay(1000);

}
