// Lab01_Ejercicio3.ino
/* =================================================
   Lab 01 — Ejercicio 3
   Muestra el tiempo transcurrido con millis() en
   el Monitor Serial.
   Formato de salida:
     [#N] t=XXXX ms  LED -> ESTADO
   ================================================= */

const int PIN_LED = 13;
int contador = 0;

void setup() {
  pinMode(PIN_LED, OUTPUT);
  Serial.begin(9600);
  Serial.println("=== Lab 01 Ejercicio 3: Blink + millis() ===");
  Serial.println("Formato: [#N] t=XXXX ms  LED -> ESTADO");
}

void loop() {
  contador++;

  // ── Encender LED ──────────────────────────────
  unsigned long tiempo_actual = millis();
  digitalWrite(PIN_LED, HIGH);

  Serial.print("[#");
  Serial.print(contador);
  Serial.print("] t=");
  Serial.print(tiempo_actual);
  Serial.println(" ms  LED -> ENCENDIDO");

  delay(500);

  // ── Apagar LED ────────────────────────────────
  tiempo_actual = millis();
  digitalWrite(PIN_LED, LOW);

  Serial.print("[#");
  Serial.print(contador);
  Serial.print("] t=");
  Serial.print(tiempo_actual);
  Serial.println(" ms  LED -> APAGADO");

  delay(500);
}
