// Lab02_Debounce.ino
/* =================================================
   Lab 02 — Pull-up interno + Debounce por software
   Conexión:
     Pulsador: un lado a Pin 2, otro lado a GND
     (sin resistencia externa, se usa pull-up interno)
     LED: Pin 13 (LED integrado del Arduino)
   Lógica invertida: reposo = HIGH, pulsando = LOW
   
   Patrón no-bloqueante con millis() para debounce.
   ================================================= */

const int PIN_BOTON          = 2;
const int PIN_LED            = 13;
const unsigned long DEBOUNCE_MS = 20;   // 20 ms de debounce

int           estado_led    = LOW;
int           ultimo_estado = HIGH;    // Pull-up: reposo = HIGH
unsigned long t_cambio      = 0;
int           conteo        = 0;

void setup() {
  pinMode(PIN_BOTON, INPUT_PULLUP);   // Pull-up INTERNO — sin R externa
  pinMode(PIN_LED,   OUTPUT);
  Serial.begin(9600);
  Serial.println("Lab 02 — Debounce activado (INPUT_PULLUP)");
  Serial.println("Presiona el pulsador para contar pulsaciones.");
}

void loop() {
  int lectura = digitalRead(PIN_BOTON);

  // Si el estado cambió, reiniciar temporizador de debounce
  if (lectura != ultimo_estado) {
    t_cambio = millis();
  }

  // Solo actuar si el estado lleva >20 ms estable (rebote eliminado)
  if ((millis() - t_cambio) > DEBOUNCE_MS) {
    // Detectar flanco de bajada (HIGH -> LOW = botón presionado)
    if (lectura == LOW && ultimo_estado == HIGH) {
      conteo++;
      estado_led = !estado_led;            // Alternar LED
      digitalWrite(PIN_LED, estado_led);
      Serial.print("Pulsacion #");
      Serial.print(conteo);
      Serial.print("  LED: ");
      Serial.println(estado_led ? "ON" : "OFF");
    }
  }

  ultimo_estado = lectura;
}
