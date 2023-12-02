#include <Adafruit_ADS1X15.h>
Adafruit_ADS1115 ads;

int channelValue = 0;

void setup() {
  // Establecer la ganancia del ADC
  ads.setGain(GAIN_ONE);

  Serial.begin(9600);

  Serial.println("Inicializando el sensor de luminosidad");

  // Inicializar el ADS1115
  if (!ads.begin()) {
    Serial.println("Failed to initialize ADS.");
    while (1);
  }
}

void loop() {
  // Leer el valor del canal específico (channelValue)
  float valorDigitalLum = ads.readADC_SingleEnded(0);
  float voutLum = ( valorDigitalLum * 4.096)/32767;
  float lumMap = map(valorDigitalLum, 30600, 28, 100, 10);



  // Mostrar la temperatura, la tensión de salida (Vo) y el valor ADC en el puerto serie
  Serial.print("Luminosidad:");
  Serial.print(valorDigitalLum);
  Serial.print('\n');
  Serial.print("Vout Luminosidad:");
  Serial.print(voutLum);
  Serial.print("V");
  Serial.print('\n');
  Serial.print("Porcentaje de luminosidad: ");
  Serial.print(lumMap);
  Serial.print("%");
  Serial.print('\n');
  

  // Esperar 1 segundo antes de realizar la siguiente lectura
  delay(2000);
}

