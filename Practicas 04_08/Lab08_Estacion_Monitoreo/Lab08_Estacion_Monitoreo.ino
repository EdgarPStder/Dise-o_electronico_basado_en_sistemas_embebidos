#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <DHT.h>
#include <Adafruit_SSD1306.h>

//Pines
#define PIN_DHT A0
#define PIN_CS_SD 10
#define PIN_BTN 8
#define PIN_LED_R 5
#define PIN_LED_G 3
#define PIN_LED_B 7
#define PIN_BUZZER 4

DHT dht(PIN_DHT,DHT22);
Adafruit_SSD1306 oled(128, 64, &Wire, -1);

//Maquina de estados
enum Estados {MONITOR, ALERTA, LOG};
Estados estado_actual = MONITOR;

//Variables globales
float temp_c, humedad;
unsigned long t_ultimo_guardado = 0;
unsigned long t_btn_presionado = 0;
int total_registros = 0;
const int INTERVALO_GUARDADO = 10000; // 10 segundos

//Funciones auxiliares
void setLED(bool r, bool g, bool bl){
    analogWrite(PIN_LED_R, r? 150: 0);
    analogWrite(PIN_LED_G, g? 150: 0);
    analogWrite(PIN_LED_B, bl? 150: 0);

}

void guradarEnSD(){
    File f = SD.open("datos.csv", FILE_WRITE);
    if (f){
        f.print(millis()/1000); f.print(",");
        f.print(temp_c, 1); f.print(",");
        f.println(humedad, 1);
        f.close();
        total_registros++;
        Serial.print("Guardado #"); Serial.println(total_registros);
    }   
}

void setup() {
    Serial.begin(9600);
    dht.begin();
    pinMode(PIN_BTN, INPUT_PULLUP);

    oled.begin(SSD1306_SWITCHCAPVCC, 0x3c);
    oled.clearDisplay(); oled.display();

    if (SD.begin(PIN_CS_SD)){
        //Escribir encabezado CSV si el archivo no existe
        if (!SD.exists("datos.csv")){
            File f = SD.open("datos.csv", FILE_WRITE);
            f.println("timepo_s, temp_c, humedad_pct");
            f.close();
        }
        Serial.println("SD lista.");
    }
    Serial.println("Sistema iniciado. Estado: MONITOR");
}

void loop() {
    // Leer Sensores
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    if (!isnan(h) && !isnan(t)) { humedad = h; temp_c = t; }

    // Transiciones de estado
    bool btn = (digitalRead(PIN_BTN) == LOW);

    // Boton presionado 3s --> estado LOG
    if (btn) {
        if (t_btn_presionado == 0) t_btn_presionado = millis();
        if (millis() - t_btn_presionado > 3000) estado_actual = LOG;
    } else {
        t_btn_presionado = 0;
        if (estado_actual == LOG) estado_actual = MONITOR;
    }

    // Condicion alerta
    if (temp_c > 35.0 || humedad > 85.0)
        estado_actual = ALERTA;
    else
        estado_actual = MONITOR; // Auto-Recuperacion

    // Acciones por estado
    oled.clearDisplay();
    oled.setTextSize(1);

    switch (estado_actual)
    {
        case MONITOR:
            setLED(false, true, false); // Verde
            oled.setCursor(0,0); oled.print("MONITOR");
            oled.setTextSize(2);
            oled.setCursor(0,16); oled.print(temp_c, 1); oled.print("C");
            oled.setTextSize(1);
            oled.setCursor(0,40); oled.print("Hum: "); oled.print(humedad, 1); oled.print("%");
            oled.setCursor(0,54); oled.print("Reg: "); oled.print(total_registros);

            if (millis() - t_ultimo_guardado >= INTERVALO_GUARDADO) {
                guradarEnSD();
                t_ultimo_guardado = millis();
            }
            break;
        case ALERTA:
            setLED(true, false, false); // Rojo
            tone(PIN_BUZZER, 1500, 300);
            oled.setCursor(25,0); oled.print("!!! ALERTA !!!");
            oled.setTextSize(2);
            oled.setCursor(0,16); oled.print(temp_c,1); oled.print("C");
            oled.setTextSize(1);
            oled.setCursor(0,42);
            if (temp_c > 35) oled.print("TEMPERATURA ALTA");
            if (humedad > 85) oled.print("HUMEDAD ALTA");
            break;
        case LOG:
            setLED(false, false, true); // Azul
            oled.setCursor(10,10); oled.print("MODO REGISTRO");
            oled.setCursor(10,28); oled.print("Total: ");
            oled.setTextSize(2);
            oled.setCursor(10,40); oled.print(total_registros);
            oled.setTextSize(1);
            oled.setCursor(0,58); oled.print("Suelta el boton");
            break;
    }
    oled.display();
    delay(500);
}
