#include <Adafruit_ADS1X15.h>

Adafruit_ADS1015 ads;

//---------------------------------------------------------------------------------------------------------

 int channelValue = 0; // canal de ADS1115 por el que mediremos la humedad 
 int sensorValue = 0;
 int humedityValue = 0;

//--------------------------------------------------------------------------------------------------------

void setup() {

  ads.setGain(GAIN_ONE);

  Serial.begin(9600);

  if(!ads.begin()){
    Serial.println("Failed to initialize ADS.");
    while(1);
  }

}

void loop() {

  
  float volts0;

  sensorValue = ads.readADC_SingleEnded(channelValue);
  volts0= ads.computeVolts(sensorValue);

 

  humedityValue = map (sensorValue,1100,1880, 100,0);

  Serial.println();
  Serial.print("Humedad: ");
  Serial.print (sensorValue, DEC);
  Serial.print('\n');
  Serial.print("Porcentaje de humedad: ");
  Serial.print(humedityValue, DEC);
  

  delay(5000);

}
