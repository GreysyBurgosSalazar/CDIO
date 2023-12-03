#define power_pin 5
#include <Adafruit_ADS1X15.h>

Adafruit_ADS1115 ads;

const int channelAdsHumidity = 0;
const int channelAdsTemperature = 1;
const int channelAdsPh = 2;
const int channelAdsLight = 3;

int getHumidity(int channelAdsHumidity) { //DONE
  int digitalValueHumidity = ads.readADC_SingleEnded(channelAdsHumidity);
  //int humidityValue = map(digitalValueHumidity, 30900, 17000, 0, 100);
  int humidityValue = map(digitalValueHumidity, 30900, 16000, 0, 100);
  return humidityValue;
}

float getTemperature(int channelAdsTemperature) {  //DONE
  float digitalValueTemperature = ads.readADC_SingleEnded(channelAdsTemperature);
  //map(digitalValueTemperature, 9199, 18292, 6, 46)
  //float voltage = (digitalValueTemperature * 3.3)/32767;
  //float temperature = (voltage-0.78)/0.035;
  float temperatureEquationExcel = (digitalValueTemperature -3435.4)/412.1;
  return temperatureEquationExcel;
}

int getTemperatureFahrenheit(int channelAdsTemperature){ //DONE
  int celsius = getTemperature(channelAdsTemperature);
  int fahrenheit = ((celsius*9/5)+32);
  return fahrenheit;
}

int getSalinity() { //DONE
  int16_t adc0;
  digitalWrite(power_pin, HIGH);
  adc0 = analogRead(A0); 
  if (adc0<800){
    return 0;
  }
  else {
  //int salinityValue = (adc0 - 793.48) / (6.1486);  
  int salinityValue = (adc0 - 841.9)/(3.9143);
  return salinityValue;
  }
}

float getPh(int channelAdsPh) {  
  float offset = 0.05;
  int digitalValuePh = ads.readADC_SingleEnded(channelAdsPh);
  float voltsPh = digitalValuePh*4.096/32767;
  float phValue = (3.5 * voltsPh) + offset;
  //Lo mismo con liquido Ph 4, calibrar el potenciometro y mantener offset
  return phValue;
}

float getLight(int channelAdsLight) {  
  float digitalValueLight = ads.readADC_SingleEnded(channelAdsLight);
  float voltagePhotodiode = digitalValueLight*4.096/32767;
  //float lightValue = map(digitalValueLight, 30000, 28, 100, 0);
  return voltagePhotodiode;
}

void showHumidity(int channelAdsHumidity) { //DONE
  int humidity = getHumidity(channelAdsHumidity);
  if (humidity>100){
    humidity = 100;
  }
  if (humidity<0){
    humidity = 0;
  }
  Serial.println("Humidity: ");
  Serial.println(humidity);
  Serial.println("%");
  //Warning 
  if (humidity <= 10) {
    Serial.println("RISK!!! LOW LEVEL OF HUMIDITY!!!");
  }
}

void showSalinity() { //DONE
  int salinity = getSalinity();
  Serial.println("Salinity: ");
  Serial.println(salinity);
  Serial.println("x5gr.");
}

void showTemperature(int channelAdsTemperature) { //DONE
  int temperatureCelsius = getTemperature(channelAdsTemperature);
  int temperatureFahrenheit = getTemperatureFahrenheit(channelAdsTemperature);
  Serial.println("Temperature:");
  Serial.println(temperatureCelsius); // if Fahrenheit, just change variable
  Serial.println("ºC"); // "ºF"
  //Warning
  if (temperatureCelsius>=35){
    Serial.println("RISK!!! HIGH TEMPERATURE!!!");
  }
}

void showPh(int channelAdsPh) {
  float ph = getPh(channelAdsPh);
  Serial.println("Ph level: ");
  Serial.println(ph);
  while (ph>5.5 && ph<7.5){
  Serial.println("OPTIMAL PH LEVEL");
  }
  if (ph<5.5){
    Serial.println("RISK!!! WATER IS TOO ACIDIC!!!***it may be time to clean the tank.");
  } else if (ph>7.5) {
    Serial.println("RISK!!! WATER IS TOO ALKALINE!!!***it may be time to clean the tank.");
  }
}

void showLight(int channelAdsLight){
  float light = getLight(channelAdsLight);
  Serial.println("Light: ");
  Serial.println(light);
  /*if (light<5){
    Serial.println("low");
  } else if (light>70){
    Serial.println("high");
  }*/
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
  showHumidity(channelAdsHumidity);
  showTemperature(channelAdsTemperature);
  showSalinity();
  showPh(channelAdsPh);
  showLight(channelAdsLight);
  delay(10000); 
}
