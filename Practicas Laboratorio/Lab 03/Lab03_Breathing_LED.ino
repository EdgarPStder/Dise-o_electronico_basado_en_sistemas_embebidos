// Lab03_Breathing_LED.ino
/* =================================================
   Lab 03 — Efecto "Breathing" con función seno
   La función sin() produce una transición suave y
   natural entre brillo mínimo y máximo, similar al
   ritmo de la respiración humana (~12-20 rpm).
   
   Conexión:
     LED: ánodo -> R 150Ω -> Pin 9 (~PWM)
          cátodo -> GND
   ================================================= */

#include <math.h>

const int PIN_LED = 9;
float angulo      = 0.0;

void setup() {
  pinMode(PIN_LED, OUTPUT);
  Serial.begin(9600);
  Serial.println("Lab 03 — Breathing LED (efecto seno)");
  Serial.println("Angulo\tBrillo");
}

void loop() {
  // sin() devuelve -1.0 a 1.0 → mapear a 0.0-1.0
  float seno  = (sin(angulo) + 1.0) / 2.0;   // 0.0 a 1.0
  int brillo  = (int)(seno * 255);            // 0 a 255

  analogWrite(PIN_LED, brillo);

  Serial.print(angulo, 2);
  Serial.print("\t");
  Serial.println(brillo);

  angulo += 0.05;                    // Velocidad del efecto
  if (angulo > 2 * PI) angulo = 0;   // Reiniciar ciclo

  delay(15);
}
