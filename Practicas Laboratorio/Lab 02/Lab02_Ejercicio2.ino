// Lab02_Ejercicio2.ino
/* =================================================
   Lab 02 — Ejercicio 2
   El LED parpadea tantas veces como indica el conteo
   de pulsaciones acumuladas.
   Ejemplo: 3 pulsaciones → LED parpadea 3 veces.
   
   Conexión:
     Pulsador: Pin 2 -> GND  (pull-up interno)
     LED     : Pin 13 (LED integrado)
   ================================================= */

const int PIN_BOTON          = 2;
const int PIN_LED            = 13;
const unsigned long DEBOUNCE_MS = 20;

int           ultimo_estado = HIGH;
unsigned long t_cambio      = 0;
int           conteo        = 0;

// ── Parpadea el LED 'veces' veces ─────────────────
void parpadearN(int veces) {
  Serial.print("Parpadeando ");
  Serial.print(veces);
  Serial.println(" veces...");

  for (int i = 0; i < veces; i++) {
    digitalWrite(PIN_LED, HIGH);
    delay(200);
    digitalWrite(PIN_LED, LOW);
    delay(200);
  }

  // Pausa final para distinguir la secuencia
  delay(600);
  Serial.println("Secuencia completada.");
}

void setup() {
  pinMode(PIN_BOTON, INPUT_PULLUP);
  pinMode(PIN_LED,   OUTPUT);
  Serial.begin(9600);
  Serial.println("Lab 02 Ejercicio 2 — LED parpadea N veces");
  Serial.println("Presiona el pulsador; el LED parpadeara segun el conteo.");
}

void loop() {
  int lectura = digitalRead(PIN_BOTON);

  if (lectura != ultimo_estado) t_cambio = millis();

  if ((millis() - t_cambio) > DEBOUNCE_MS) {
    // Flanco de bajada: botón presionado
    if (lectura == LOW && ultimo_estado == HIGH) {
      conteo++;
      Serial.print("Conteo: ");
      Serial.println(conteo);
      parpadearN(conteo);   // Parpadea exactamente 'conteo' veces
    }
  }

  ultimo_estado = lectura;
}
