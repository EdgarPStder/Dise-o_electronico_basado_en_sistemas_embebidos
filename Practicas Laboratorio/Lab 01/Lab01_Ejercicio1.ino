// Lab01_Ejercicio1.ino
/* =================================================
   Lab 01 — Ejercicio 1
   Modificación de tiempos de delay:
     - LED encendido : 200 ms
     - LED apagado   : 800 ms
   Observación esperada: el LED se percibe como un
   destello rápido con apagado prolongado, dando la
   sensación visual de que está casi siempre apagado.
   ================================================= */

const int PIN_LED = 13;
int contador = 0;

void setup() {
  pinMode(PIN_LED, OUTPUT);
  Serial.begin(9600);
  Serial.println("=== Lab 01 Ejercicio 1: Blink 200/800 ms ===");
  Serial.println("Formato: [#N] LED -> ESTADO");
}

void loop() {
  contador++;

  // Encender 200 ms
  digitalWrite(PIN_LED, HIGH);
  Serial.print("[#");
  Serial.print(contador);
  Serial.println("] LED -> ENCENDIDO  (200 ms)");
  delay(200);

  // Apagar 800 ms
  digitalWrite(PIN_LED, LOW);
  Serial.print("[#");
  Serial.print(contador);
  Serial.println("] LED -> APAGADO    (800 ms)");
  delay(800);
}
