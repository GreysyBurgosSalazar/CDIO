#include <Wire.h>
#include <Adafruit_ADS1X15.h>

Adafruit_ADS1115 adsHumedad;
Adafruit_ADS1115 adsTemperatura;

int channelValueHumedad = 0;
int sensorValueHumedad = 0;
float humidityValue = 0;

int channelValueTemperatura = 0;

void setup() {
  Serial.begin(9600);
  
  adsHumedad.begin();
  adsTemperatura.begin();

  adsHumedad.setGain(GAIN_ONE);
  adsTemperatura.setGain(GAIN_ONE);
}

void loop() {
  // Medición de humedad
  int sensorValueHumedad = adsHumedad.readADC_SingleEnded(channelValueHumedad);
  humidityValue = map(sensorValueHumedad, 9735, 20575, 100, 0);
  Serial.print("Humedad: ");
  Serial.print(sensorValueHumedad);
  Serial.println(" %");

  // Medición de temperatura
  int16_t adcTemperatura = adsTemperatura.readADC_SingleEnded(channelValueTemperatura);
  float voTemperatura = (adcTemperatura * 4.096 / 32767);
  float bTemperatura = 0.79;
  float mTemperatura = 0.035;
  float temperatura = (voTemperatura - bTemperatura) / mTemperatura;

  Serial.print("Temperatura: ");
  Serial.print(temperatura);
  Serial.print("°");
  Serial.print('\n');
  Serial.print("Vo: ");
  Serial.print(voTemperatura);
  Serial.print('\n');
  Serial.println(adcTemperatura);

  delay(1000);
}

