#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_BMP085.h>

#define OLED_W 128
#define OLED_H 64
#define OLED_ADDR 0x3C

Adafruit_BMP085 bmp;
Adafruit_SSD1306 display(OLED_W, OLED_H, &Wire, -1);

// Presion al nivel del mar en PASCALES para el BMP180 (1013.25 hPa * 100)
const float PRESION_MAR = 101325.0; 

void setup() {
  Serial.begin(9600);
  
  // Iniciar OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    Serial.println("ERROR: OLED no encontrada en 0x3C");
    while (true);
  }
  
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(20, 28);
  display.println("Iniciando BMP180...");
  display.display();
  
  // Iniciar BMP180 (No requiere pasarle direccion I2C)
  if (!bmp.begin()) {
    Serial.println("ERROR: BMP180 no encontrado");
    display.clearDisplay();
    display.setCursor(5, 28);
    display.println("ERROR: BMP180");
    display.display();
    while (true);
  }
  
  Serial.println("BMP180 y OLED listos.");
  Serial.println("Tiempo\tTemp(C)\tPresion(hPa)\tAltitud(m)");
}

void loop() {
  float temp = bmp.readTemperature(); // Celsius
  float presion_pa = bmp.readPressure(); // En Pascales
  float presion_hpa = presion_pa / 100.0; // Convertir a hPa para mostrar
  float altitud = bmp.readAltitude(PRESION_MAR);
  
  // ── Mostrar en OLED ───────────────────────────────────
  display.clearDisplay();
  
  // Titulo
  display.setTextSize(1);
  display.setCursor(30, 0);
  display.println("-- BMP180 --");
  
  // Temperatura grande
  display.setTextSize(2);
  display.setCursor(0, 14);
  display.print(temp, 1);
  display.println(" C");
  
  // Presion y altitud en texto pequeño
  display.setTextSize(1);
  display.setCursor(0, 38);
  display.print("P: ");
  display.print(presion_hpa, 1);
  display.println(" hPa");
  
  display.setCursor(0, 50);
  display.print("Alt: ");
  display.print(altitud, 0);
  display.println(" m");
  
  display.display(); // Enviar buffer a la pantalla
  
  // ── Imprimir en Serial ────────────────────────────────
  Serial.print(millis()/1000); Serial.print("\t");
  Serial.print(temp, 2); Serial.print("\t");
  Serial.print(presion_hpa, 2); Serial.print("\t");
  Serial.println(altitud, 1);
  
  delay(1000);
}