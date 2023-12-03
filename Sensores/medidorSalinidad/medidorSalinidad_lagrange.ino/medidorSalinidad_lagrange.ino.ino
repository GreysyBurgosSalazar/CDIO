#include <Arduino.h>

#define power_pin 5

float lagrange(float x, float x_values[], float y_values[], int n) {
  float result = 0;

  for (int i = 0; i < n; i++) {
    float term = y_values[i];

    for (int j = 0; j < n; j++) {
      if (j != i) {
        term = term * (x - x_values[j]) / (x_values[i] - x_values[j]);
      }
    }

    result += term;
  }

  return result;
}

void setup() {
  pinMode(power_pin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int16_t adc0;

  digitalWrite(power_pin, HIGH);
  delay(1000);

  adc0 = analogRead(A0);
  digitalWrite(power_pin, LOW);
  delay(1000);

  Serial.print("Lectura digital = ");
  Serial.print(adc0, DEC);
  Serial.print('\n');

  float x_values[] = {5, 10, 15, 20, 25};
  float y_values[] = {790, 798, 807, 812, 831};
  int n = sizeof(x_values) / sizeof(x_values[0]);

  float x_to_evaluate = adc0;  // Usar la lectura ADC como valor x a evaluar

  float result = lagrange(x_to_evaluate, x_values, y_values, n);

  Serial.print("Resultado del polinomio de Lagrange para x = ");
  Serial.print(x_to_evaluate);
  Serial.print(" es: ");
  Serial.println(result);
}

