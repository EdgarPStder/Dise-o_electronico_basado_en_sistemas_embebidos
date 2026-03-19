// Lab03_PWM_Brillo.ino
/* =================================================
   Lab 03 — Control de brillo con analogWrite (PWM)
   Conexión:
     LED blanco/azul: ánodo -> R 150Ω -> Pin 9 (~PWM)
                      cátodo -> GND
   Pines PWM en Arduino UNO: 3, 5, 6, 9, 10, 11
   Frecuencia PWM pin 9: ~490 Hz
   ================================================= */

const int PIN_LED = 9;   // Pin PWM (~9 en Arduino UNO)

void setup() {
  pinMode(PIN_LED, OUTPUT);
  Serial.begin(9600);
  Serial.println("Lab 03 — Control PWM de brillo");
  Serial.println("Brillo\t/255\tDuty Cycle");
}

void loop() {
  // ── Subir de 0 a 255 ──────────────────────────
  for (int brillo = 0; brillo <= 255; brillo += 5) {
    analogWrite(PIN_LED, brillo);

    Serial.print("Brillo: ");
    Serial.print(brillo);
    Serial.print("/255   DC: ");
    Serial.print((brillo * 100) / 255);
    Serial.println("%");

    delay(30);
  }

  // ── Bajar de 255 a 0 ──────────────────────────
  for (int brillo = 255; brillo >= 0; brillo -= 5) {
    analogWrite(PIN_LED, brillo);
    delay(30);
  }
}
