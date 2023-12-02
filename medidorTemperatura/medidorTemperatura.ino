#include <Adafruit_ADS1X15.h>
Adafruit_ADS1115 ads;

  int channelValue = 0;

void setup() {
//ganancia
  ads.setGain(GAIN_ONE);

  Serial.begin(9600);

  Serial.println("Inicializando el medidor de temperatura");
//inicilizar la ganancia
  if (!ads.begin()) {
    Serial.println("Failed to initialize ADS.");
    while (1);
  }
}

void loop() {

  int16_t adc0 = ads.readADC_SingleEnded(channelValue);
  float vo = (adc0 * 4.096 / 32767);
  float b = 0.79;
  float m = 0.035;
  float temperatura = ( vo-b )/ m;

  Serial.print("Temperatura:");
  Serial.print(temperatura);
  Serial.print("°");
  Serial.print('\n');
  Serial.print("Vo:");
  Serial.print(vo);
  Serial.print('\n');
  Serial.println(adc0);



  delay(1000);
}
