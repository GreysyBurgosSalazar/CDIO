#include <Adafruit_ADS1X15.h>

Adafruit_ADS1115 ads; // Crea una instancia del objeto Adafruit_ADS1115 llamado "ads".

int channelValueHumedad = 0; // Canal para medir la humedad en el módulo ADS1115.
int sensorValueHumedad = 0; // Variable para almacenar el valor leído del sensor de humedad.
int humedadValue = 0; // Variable para almacenar el valor de humedad después de mapearlo.

int channelValueTemperatura = 1; // Canal para medir la temperatura en el módulo ADS1115.

void setup() {
  ads.setGain(GAIN_ONE); // Configura la ganancia del módulo ADS1115.

  Serial.begin(9600); // Inicializa la comunicación serial a 9600 baudios.

  Serial.println("Inicializando el medidor de humedad y temperatura");

  if (!ads.begin()) {
    Serial.println("Failed to initialize ADS."); // Imprime un mensaje si la inicialización del módulo ADS1115 falla.
    while (1); // Se queda en un bucle infinito si la inicialización falla.
  }
}

void loop() {
  // Medición de humedad
  float voltsHumedad;
  sensorValueHumedad = ads.readADC_SingleEnded(channelValueHumedad); // Lee el valor del canal de humedad.
  voltsHumedad = ads.computeVolts(sensorValueHumedad); // Convierte el valor leído a voltaje.
  humedadValue = map(sensorValueHumedad, 18000, 30415, 100, 0); // Mapea el valor leído al rango de humedad.

  Serial.print("Humedad: ");
  Serial.print(sensorValueHumedad); // Imprime el valor bruto de humedad leído.
  Serial.print('\n');
  Serial.print("Porcentaje de humedad: ");
  Serial.print(humedadValue); // Imprime el valor de humedad mapeado.
  Serial.print('\n');

  // Medición de temperatura
  int16_t adcTemperatura = ads.readADC_SingleEnded(channelValueTemperatura); // Lee el valor del canal de temperatura.
  float voTemperatura = (adcTemperatura * 4.096 / 32767); // Convierte el valor leído a voltaje.
  float bTemperatura = 0.79; // Parámetro de ajuste.
  float mTemperatura = 0.035; // Parámetro de ajuste.
  float temperatura = (voTemperatura - bTemperatura) / mTemperatura; // Calcula la temperatura en base al voltaje.

  Serial.print("Temperatura: ");
  Serial.print(temperatura);
  Serial.print("°");
  Serial.print('\n');
  Serial.print("Vo: ");
  Serial.print(voTemperatura); // Imprime el voltaje de temperatura.
  Serial.print('\n');
  Serial.println(adcTemperatura); // Imprime el valor bruto de temperatura.

  delay(2000); // Espera 1 segundo antes de la siguiente lectura.
}


