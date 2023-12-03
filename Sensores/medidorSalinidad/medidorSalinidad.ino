
#define power_pin 5

void setup() {
  pinMode (power_pin, OUTPUT);
  Serial.begin(9600);

}

void loop() {
  int16_t adc0;

  digitalWrite (power_pin, HIGH);
  delay(1000);

  adc0 = analogRead(A0);
  digitalWrite(power_pin, LOW);
  delay(1000);

  Serial.print("Lectura digital = ");
  Serial.print(adc0, DEC);
  Serial.print('\n');

}
