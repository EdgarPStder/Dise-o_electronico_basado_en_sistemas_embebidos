// Lab02_Ejercicio3.ino
/* =================================================
   Lab 02 — Ejercicio 3 (Wokwi)
   2 pulsadores, LED verde y LED rojo.
     - Botón A (Pin 2): enciende LED VERDE (Pin 8)
     - Botón B (Pin 4): enciende LED ROJO  (Pin 7)
   
   Conexión (simular en wokwi.com):
     Botón A : Pin 2 -> GND  (pull-up interno)
     Botón B : Pin 4 -> GND  (pull-up interno)
     LED verde: ánodo -> R 220Ω -> Pin 8, cátodo -> GND
     LED rojo : ánodo -> R 220Ω -> Pin 7, cátodo -> GND
   
   Nota Wokwi: en el simulador agrega los componentes
   desde la barra lateral y conecta según el esquema.
   Captura pantalla del simulador como evidencia.
   ================================================= */

const int PIN_BTN_A    = 2;   // Botón A -> LED verde
const int PIN_BTN_B    = 4;   // Botón B -> LED rojo
const int PIN_LED_VERDE = 8;
const int PIN_LED_ROJO  = 7;

const unsigned long DEBOUNCE_MS = 20;

// Debounce botón A
int           ultimo_a   = HIGH;
unsigned long t_cambio_a = 0;

// Debounce botón B
int           ultimo_b   = HIGH;
unsigned long t_cambio_b = 0;

// Estado de los LEDs
int estado_verde = LOW;
int estado_rojo  = LOW;

void setup() {
  pinMode(PIN_BTN_A,     INPUT_PULLUP);
  pinMode(PIN_BTN_B,     INPUT_PULLUP);
  pinMode(PIN_LED_VERDE, OUTPUT);
  pinMode(PIN_LED_ROJO,  OUTPUT);
  Serial.begin(9600);
  Serial.println("Lab 02 Ejercicio 3 — Wokwi: 2 botones, 2 LEDs");
  Serial.println("Boton A -> LED Verde | Boton B -> LED Rojo");
}

void loop() {
  int lectura_a = digitalRead(PIN_BTN_A);
  int lectura_b = digitalRead(PIN_BTN_B);

  // ── Botón A: alterna LED verde ───────────────
  if (lectura_a != ultimo_a) t_cambio_a = millis();
  if ((millis() - t_cambio_a) > DEBOUNCE_MS) {
    if (lectura_a == LOW && ultimo_a == HIGH) {
      estado_verde = !estado_verde;
      digitalWrite(PIN_LED_VERDE, estado_verde);
      Serial.print("LED Verde: ");
      Serial.println(estado_verde ? "ENCENDIDO" : "APAGADO");
    }
  }
  ultimo_a = lectura_a;

  // ── Botón B: alterna LED rojo ─────────────────
  if (lectura_b != ultimo_b) t_cambio_b = millis();
  if ((millis() - t_cambio_b) > DEBOUNCE_MS) {
    if (lectura_b == LOW && ultimo_b == HIGH) {
      estado_rojo = !estado_rojo;
      digitalWrite(PIN_LED_ROJO, estado_rojo);
      Serial.print("LED Rojo : ");
      Serial.println(estado_rojo ? "ENCENDIDO" : "APAGADO");
    }
  }
  ultimo_b = lectura_b;
}
