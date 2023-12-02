#include <Adafruit_ADS1X15.h>
Adafruit_ADS1115 ads;

int channelValue = 0;
float Offset = 0.05;
int samplingInterval = 20;
int printInterval = 800;
int ArrayLength = 40;
int pHArrayIndex = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Inicializando medidor de pH");

  if (!ads.begin()) {
    Serial.println("Failed to initialize ADS.");
    while (1);
  }

  ads.setGain(GAIN_ONE);
}

void loop(void) {
  int pHArray[ArrayLength];
  static unsigned long samplingTime = millis();
  static unsigned long printTime = millis();
  static float pHValue, voltage;

  if (millis() - samplingTime > samplingInterval) {
    pHArray[pHArrayIndex++] = ads.readADC_SingleEnded(channelValue);
    if (pHArrayIndex == ArrayLength) pHArrayIndex = 0;

    // Calcular voltage manualmente usando la resolución del ADC y la referencia de voltaje
    float resolution = 32767.0;  // Resolución del ADC de 15 bits
    float referenceVoltage = 4.096;  // Referencia de voltaje del ADS1115 en voltios
    voltage = (float)pHArray[pHArrayIndex] * (referenceVoltage / resolution);
    
    pHValue = 3.5 * voltage + Offset;
    samplingTime = millis();
  }

  if (millis() - printTime > printInterval) {
    Serial.print("Voltage:");
    Serial.print(voltage, 2);
    Serial.print('\n');
    Serial.print("pH value:");
    Serial.println(pHValue, 2);
    printTime = millis();
  }
}
