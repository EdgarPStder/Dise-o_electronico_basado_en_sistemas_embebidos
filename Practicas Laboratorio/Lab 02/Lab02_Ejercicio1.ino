// Lab02_Ejercicio1.ino
/* =================================================
   Lab 02 — Ejercicio 1
   Agrega un segundo pulsador (Pin 3) que reinicia
   el conteo a cero.
   
   Conexión:
     Pulsador A (contar) : Pin 2 -> GND  (pull-up interno)
     Pulsador B (reset)  : Pin 3 -> GND  (pull-up interno)
     LED                 : Pin 13 (LED integrado)
   ================================================= */

const int PIN_BOTON_A        = 2;    // Pulsador contar
const int PIN_BOTON_B        = 3;    // Pulsador reset
const int PIN_LED            = 13;
const unsigned long DEBOUNCE_MS = 20;

// Variables botón A
int           estado_led       = LOW;
int           ultimo_a         = HIGH;
unsigned long t_cambio_a       = 0;
int           conteo           = 0;

// Variables botón B
int           ultimo_b         = HIGH;
unsigned long t_cambio_b       = 0;

void setup() {
  pinMode(PIN_BOTON_A, INPUT_PULLUP);
  pinMode(PIN_BOTON_B, INPUT_PULLUP);
  pinMode(PIN_LED, OUTPUT);
  Serial.begin(9600);
  Serial.println("Lab 02 Ejercicio 1 — Contar + Reset");
  Serial.println("Boton A (Pin 2): sumar pulsacion");
  Serial.println("Boton B (Pin 3): reiniciar conteo");
}

void loop() {
  int lectura_a = digitalRead(PIN_BOTON_A);
  int lectura_b = digitalRead(PIN_BOTON_B);

  // ── Debounce botón A ─────────────────────────
  if (lectura_a != ultimo_a) t_cambio_a = millis();

  if ((millis() - t_cambio_a) > DEBOUNCE_MS) {
    if (lectura_a == LOW && ultimo_a == HIGH) {
      conteo++;
      estado_led = !estado_led;
      digitalWrite(PIN_LED, estado_led);
      Serial.print("Pulsacion #");
      Serial.print(conteo);
      Serial.print("  LED: ");
      Serial.println(estado_led ? "ON" : "OFF");
    }
  }
  ultimo_a = lectura_a;

  // ── Debounce botón B (reset) ─────────────────
  if (lectura_b != ultimo_b) t_cambio_b = millis();

  if ((millis() - t_cambio_b) > DEBOUNCE_MS) {
    if (lectura_b == LOW && ultimo_b == HIGH) {
      conteo     = 0;
      estado_led = LOW;
      digitalWrite(PIN_LED, LOW);
      Serial.println(">>> CONTEO REINICIADO <<<");
    }
  }
  ultimo_b = lectura_b;
}
