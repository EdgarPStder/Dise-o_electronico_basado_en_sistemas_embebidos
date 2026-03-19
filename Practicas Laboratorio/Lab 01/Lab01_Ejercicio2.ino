// Lab01_Ejercicio2.ino
/* =================================================
   Lab 01 — Ejercicio 2: Patrón SOS en código Morse
   S = · · ·   (3 destellos cortos  200 ms)
   O = − − −   (3 destellos largos  600 ms)
   S = · · ·   (3 destellos cortos  200 ms)
   Pausa entre repeticiones: 2 000 ms
   
   Tiempos entre destellos dentro de una letra: 200 ms
   Tiempos entre letras: 600 ms
   ================================================= */

const int PIN_LED = 13;

// Duraciones (ms)
const int CORTO       = 200;   // Punto  (·)
const int LARGO       = 600;   // Raya   (−)
const int GAP_SIMBOLO = 200;   // Pausa entre símbolos de la misma letra
const int GAP_LETRA   = 600;   // Pausa entre letras
const int GAP_CICLO   = 2000;  // Pausa entre repeticiones del SOS

// ── Función auxiliar: enviar un destello ──────────
void destello(int duracion_ms) {
  digitalWrite(PIN_LED, HIGH);
  delay(duracion_ms);
  digitalWrite(PIN_LED, LOW);
  delay(GAP_SIMBOLO);
}

void setup() {
  pinMode(PIN_LED, OUTPUT);
  Serial.begin(9600);
  Serial.println("=== Lab 01 Ejercicio 2: SOS Morse ===");
}

void loop() {
  Serial.println("--- S (· · ·) ---");
  destello(CORTO);
  destello(CORTO);
  destello(CORTO);
  delay(GAP_LETRA);

  Serial.println("--- O (− − −) ---");
  destello(LARGO);
  destello(LARGO);
  destello(LARGO);
  delay(GAP_LETRA);

  Serial.println("--- S (· · ·) ---");
  destello(CORTO);
  destello(CORTO);
  destello(CORTO);

  Serial.println(">>> Pausa 2 s <<<\n");
  delay(GAP_CICLO);
}
