// Lab05_DHT22_Basico.ino
#include <DHT.h>

#define PIN_DHT 7
#define TIPO_DHT DHT22 
#define PIN_LED_VERDE 8
#define PIN_LED_ROJO 9
#define PIN_BUZZER 6

DHT dht(PIN_DHT, TIPO_DHT);

// Umbrales de alerta
const float TEMP_ALTA = 30.0; // Celsius
const float TEMP_BAJA = 10.0;
const float HUM_ALTA = 80.0; // Porcentaje

void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(PIN_LED_VERDE, OUTPUT);
  pinMode(PIN_LED_ROJO, OUTPUT);
  // COMILLAS DOBLES CORREGIDAS
  Serial.println("Tiempo(s)\tTemp(C)\tTemp(F)\tHumedad%\tHeatIdx\tEstado"); 
}

void loop() {
  delay(2000); // DHT22: esperar al menos 2 s entre lecturas
  
  float humedad = dht.readHumidity();
  float temp_c = dht.readTemperature();
  float temp_f = dht.readTemperature(true); // true = Fahrenheit
  
  // Verificar si la lectura fue valida
  if (isnan(humedad) || isnan(temp_c)) {
    Serial.println("ERROR: Fallo en lectura DHT22"); // COMILLAS CORREGIDAS
    digitalWrite(PIN_LED_ROJO, HIGH);
    return;
  }
  
  // Indice de calor (Heat Index) — sensacion termica
  float heat_idx = dht.computeHeatIndex(temp_c, humedad, false);
  
  // Determinar estado y actuar (COMENTARIO CORREGIDO)
  String estado;
  if (temp_c > TEMP_ALTA || humedad > HUM_ALTA) {
    estado = "ALERTA-CALOR"; // COMILLAS CORREGIDAS
    digitalWrite(PIN_LED_ROJO, HIGH);
    digitalWrite(PIN_LED_VERDE, LOW);
    tone(PIN_BUZZER, 2000, 200);
  } else if (temp_c < TEMP_BAJA) {
    estado = "ALERTA-FRIO"; // COMILLAS CORREGIDAS
    digitalWrite(PIN_LED_ROJO, HIGH);
    digitalWrite(PIN_LED_VERDE, LOW);
    tone(PIN_BUZZER, 500, 500);
  } else {
    estado = "NORMAL"; // COMILLAS CORREGIDAS
    digitalWrite(PIN_LED_VERDE, HIGH);
    digitalWrite(PIN_LED_ROJO, LOW);
  }
  
  // Imprimir datos en formato tabla para Serial Plotter
  Serial.print(millis()/1000); Serial.print("\t");
  Serial.print(temp_c, 1); Serial.print("\t");
  Serial.print(temp_f, 1); Serial.print("\t");
  Serial.print(humedad, 1); Serial.print("\t");
  Serial.print(heat_idx, 1); Serial.print("\t");
  Serial.println(estado);
}