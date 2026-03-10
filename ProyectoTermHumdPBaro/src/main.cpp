#include <Arduino.h>
#include <DHT.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include <WiFi.h>
#include <ThingSpeak.h>
#include "secrets.h"

// ─── Pines ────────────────────────────────────────────────
#define DHT_PIN      5    // DATA del DHT22
#define BME_SDA      21    // I2C SDA
#define BME_SCL      22   // I2C SCL

// ─── Configuración Sensores ───────────────────────────────
#define DHT_TYPE DHT22
DHT dht(DHT_PIN, DHT_TYPE);
Adafruit_BMP280 bmp; 

// ─── Configuración WiFi / ThingSpeak ──────────────────────
char ssid[]  = SECRET_SSID;
char pass[]  = SECRET_PASS;
WiFiClient client;

unsigned long myChannelNumber  = SECRET_CH_ID;
const char* myWriteAPIKey    = SECRET_WRITE_APIKEY;

// ─── Tiempos (No-Blocking) ────────────────────────────────
unsigned long lastSensors    = 0;
unsigned long lastThingSpeak = 0;

const unsigned long INTERVALO_SENSORS   = 2000;   // Lectura cada 2s
const unsigned long INTERVALO_THINGSPEAK = 10000;  // Envío cada 10s (Seguro para ThingSpeak)

// ─── Variables de Datos ───────────────────────────────────
float temp1 = NAN, humedad = NAN;
float temp2 = NAN, presion = NAN;
float tdp   = NAN, st      = NAN;

// ─── Helpers ──────────────────────────────────────────────
void conectarWiFi() {
    if (WiFi.status() == WL_CONNECTED) return;
    
    Serial.printf("\nConectando a %s", ssid);
    WiFi.begin(ssid, pass);
    
    int intentos = 0;
    while (WiFi.status() != WL_CONNECTED && intentos < 20) {
        delay(500);
        Serial.print(".");
        intentos++;
    }
    
    if (WiFi.status() == WL_CONNECTED) {
        Serial.printf("\nWiFi conectado — IP: %s\n", WiFi.localIP().toString().c_str());
    }
}

float calcularPuntoRocio(float t, float h) {
    // Fórmula de Magnus-Tetens
    float a = 17.27;
    float b = 237.7;
    float alpha = ((a * t) / (b + t)) + log(h / 100.0);
    return (b * alpha) / (a - alpha);
}

// ─── Setup ────────────────────────────────────────────────
void setup() {
    Serial.begin(115200);
    Serial.println("\n=== ESTACIÓN METEOROLÓGICA: CIUDAD MANTE ===");

    // Inicializar Sensores
    dht.begin();
    if (!bmp.begin(0x76)) {
        Serial.println("[ERROR] No se encuentra el sensor BMP280 (I2C 0x76)");
    }

    // WiFi + ThingSpeak
    WiFi.mode(WIFI_STA);
    conectarWiFi();
    ThingSpeak.begin(client);
    
    Serial.println("Sistema en línea. Esperando primera lectura...");
}

// ─── Loop ─────────────────────────────────────────────────
void loop() {
    unsigned long ahora = millis();
    
    // Mantener conexión WiFi activa
    conectarWiFi();

    // ── Lectura y Cálculos cada 2 segundos ──────────────────
    if (ahora - lastSensors >= INTERVALO_SENSORS) {
        lastSensors = ahora;
        
        temp1   = dht.readTemperature(); // Temperatura DHT22
        humedad = dht.readHumidity();    // Humedad DHT22
        temp2   = bmp.readTemperature(); // Temperatura BME280
        presion = bmp.readPressure() / 100.0F; // Presión en hPa

        if (!isnan(temp1) && !isnan(humedad)) {
            // Sensación térmica usando la librería de Adafruit
            st  = dht.computeHeatIndex(temp1, humedad, false);
            // Punto de rocío calculado
            tdp = calcularPuntoRocio(temp1, humedad);
            
            Serial.printf("[LOCAL] T1:%.1f°C | H:%.1f%% | P:%.1f hPa | T2:%.1f°C | TDP:%.1f°C | ST:%.1f°C\n", 
              temp1,    // T1 (DHT22)
              humedad,  // Humedad (DHT22)
              presion,  // Presión (BMP280)
              temp2,    // T2 (BMP280)
              tdp,      // Punto de Rocío
              st);      // Sensación Térmica

        } else {
            Serial.println("[ERROR] Fallo en lectura de sensores DHT22");
        }
    }

    // ── Envío a ThingSpeak cada 20 segundos ─────────────────
    if (ahora - lastThingSpeak >= INTERVALO_THINGSPEAK) {
        lastThingSpeak = ahora;

        if (!isnan(temp1) && !isnan(humedad)) {
            ThingSpeak.setField(1, temp1);   // Campo 1: Temp DHT
            ThingSpeak.setField(2, humedad); // Campo 2: Humedad
            ThingSpeak.setField(3, presion); // Campo 3: Presión
            ThingSpeak.setField(4, temp2);   // Campo 4: Temp BME
            ThingSpeak.setField(5, tdp);     // Campo 5: Punto Rocío
            ThingSpeak.setField(6, st);      // Campo 6: Sensación Térmica

            int respuesta = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);

            if (respuesta == 200) {
                Serial.println("[ThingSpeak] Datos enviados con éxito.");
            } else {
                Serial.printf("[ThingSpeak] Error en el envío. Código HTTP: %d\n", respuesta);
            }
        }
    }
}
