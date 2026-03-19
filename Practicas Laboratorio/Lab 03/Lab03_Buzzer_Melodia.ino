// Lab03_Buzzer_Melodia.ino
/* =================================================
   Lab 03 — Buzzer piezoeléctrico: escala musical
   con tone() / noTone()
   
   Conexión:
     Buzzer piezoeléctrico pasivo:
       Terminal + -> Pin 6
       Terminal - -> GND
   
   Nota: usa un buzzer PASIVO (requiere señal PWM).
   Un buzzer ACTIVO solo necesita HIGH/LOW y no
   responde a distintas frecuencias.
   ================================================= */

const int PIN_BUZZER = 6;

// Frecuencias (Hz) de las 7 notas de la escala Do Mayor
int    notas[]   = {262, 294, 330, 349, 392, 440, 494};
String nombres[] = {"Do", "Re", "Mi", "Fa", "Sol", "La", "Si"};

const int DURACION = 300;   // ms por nota

void setup() {
  Serial.begin(9600);
  Serial.println("Lab 03 — Buzzer: escala musical Do Mayor");
  Serial.println("Nota\tFrec (Hz)\tDuracion (ms)");
}

void loop() {
  // ── Escala ascendente Do → Si ──────────────────
  for (int i = 0; i < 7; i++) {
    Serial.print(nombres[i]);
    Serial.print("\t");
    Serial.print(notas[i]);
    Serial.print(" Hz\t\t");
    Serial.print(DURACION);
    Serial.println(" ms");

    tone(PIN_BUZZER, notas[i], DURACION);
    delay(DURACION + 50);   // Pequeña pausa entre notas
  }

  noTone(PIN_BUZZER);   // Detener cualquier tono residual
  Serial.println("--- Pausa entre escalas ---\n");
  delay(1000);           // Pausa de 1 s entre repeticiones

  // ── Escala descendente Si → Do ─────────────────
  for (int i = 6; i >= 0; i--) {
    Serial.print(nombres[i]);
    Serial.print("\t");
    Serial.print(notas[i]);
    Serial.print(" Hz\t\t");
    Serial.print(DURACION);
    Serial.println(" ms");

    tone(PIN_BUZZER, notas[i], DURACION);
    delay(DURACION + 50);
  }

  noTone(PIN_BUZZER);
  Serial.println("--- Pausa entre escalas ---\n");
  delay(1000);
}
