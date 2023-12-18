#define power_pin 5
#include <Adafruit_ADS1X15.h>
#include <SensorTemperatura.h>
#include <SensorPh.h>
#include <SensorHumedad.h>
#include <SensorLuz.h>
#include <ESP8266WiFi.h>
#include <ThingSpeak.h>

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
  //Creo los objetos tipo sensor
  SensorTemperatura sensorTemp(1,ads); 
  SensorPh sensorPh(2, 0.05,ads);
  SensorHumedad sensorHum(0,ads); 
  SensorLuz sensorLuz(3,ads);
 
WiFiClient client;
const char *ssid = "Pixel_3467";  // Nombre de tu red WiFi
const char *password = "sparkfun";  // Contraseña de tu red WiFi

const char *thingSpeakApiKey = "5B9I2IB3HTHVX27V"; // API Key de ThingSpeak
const unsigned long channelID = 2383609; // ID de tu canal ThingSpeak

// Función para inicializar la conexión WiFi
void connectWiFi() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to WiFi!");
}

void setup() {
  initializeSparkfun();
  initializeADS();
  connectWiFi(); // Llama a la función para conectarse a WiFi

  ThingSpeak.begin(client); // Inicializa ThingSpeak
}

void loop() {
  // Aquí deberías obtener los valores de los sensores y almacenarlos en variables
  float lecturaSensor1 = sensorHum.lecturaHumedad();
  float lecturaSensor2 = sensorTemp.lecturaTemperatura();
  float lecturaSensor3 = medirSalinidad();
  float lecturaSensor4 = sensorPh.lecturaPh();
  float lecturaSensor5 = sensorLuz.lecturaLuz();
  // Envío de datos a ThingSpeak
  ThingSpeak.setField(1, lecturaSensor1);
  ThingSpeak.setField(2, lecturaSensor2);
  ThingSpeak.setField(3, lecturaSensor3);
  ThingSpeak.setField(4, lecturaSensor4);
  ThingSpeak.setField(5, lecturaSensor5);
  // ... (asigna campos para los datos de todos tus sensores)

  int httpCode = ThingSpeak.writeFields(channelID, thingSpeakApiKey);
  if (httpCode == 200) {
    Serial.println("Datos enviados a ThingSpeak correctamente");
  } else {
    Serial.println("Error en el envío de datos a ThingSpeak. Código HTTP: " + String(httpCode));
  }
  
  mostrarSalinidad();
  sensorTemp.mostrarTemperatura();
  sensorPh.mostrarPh();
  sensorHum.mostrarHumedad();
  sensorLuz.mostrarLuz();

  delay(5000); // Espera 15 segundos antes de enviar datos nuevamente (ThingSpeak limita a 15 segundos)
}
