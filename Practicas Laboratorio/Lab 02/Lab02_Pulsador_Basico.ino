// Lab02_Pulsador_Basico.ino
/* =================================================
   Lab 02 — Lectura básica con Pull-down externo
   Conexión:
     Pulsador: un lado a 5V, otro lado a Pin 2
     R 10kΩ entre Pin 2 y GND  (pull-down)
     LED verde: ánodo -> R 220Ω -> Pin 8
                cátodo -> GND
   Lógica: sin pulsar = LOW, pulsando = HIGH
   ================================================= */

const int PIN_BOTON = 2;   // Entrada digital
const int PIN_LED   = 8;   // Salida digital

void setup() {
  pinMode(PIN_BOTON, INPUT);    // Entrada normal (R pull-down externa)
  pinMode(PIN_LED,   OUTPUT);
  Serial.begin(9600);
  Serial.println("Lab 02 — Lectura de pulsador (pull-down externo)");
  Serial.println("Estado inicial: BOTON SUELTO");
}

void loop() {
  int estado = digitalRead(PIN_BOTON);   // Lee HIGH o LOW

  if (estado == HIGH) {
    digitalWrite(PIN_LED, HIGH);          // LED encendido
    Serial.println("Boton: PRESIONADO");
  } else {
    digitalWrite(PIN_LED, LOW);           // LED apagado
  }

  delay(50);   // Pequeño retardo para no saturar el serial
}
