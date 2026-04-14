// Lab08_SD_Basico.ino
#include <SPI.h>
#include <SD.h>

const int PIN_CS_SD = 10;

void setup() {
  Serial.begin(9600);
  Serial.print("Inicializando SD...");
  
  if (!SD.begin(PIN_CS_SD)) {
    Serial.println(" ERROR. Verifica conexiones y formato FAT32.");
    return;
  }
  Serial.println(" OK");
  
  // Listar archivos en la raiz
  File root = SD.open("/");
  Serial.println("Archivos en la SD:");
  
  while (true) {
    File entry = root.openNextFile();
    if (!entry) break;
    Serial.print("  ");
    Serial.print(entry.name());
    Serial.print("  ");
    Serial.println(entry.size());
    entry.close();
  }
  
  // Crear y escribir un archivo de prueba
  File archivo = SD.open("TEST.TXT", FILE_WRITE);
  if (archivo) {
    archivo.println("Lab 08 - Prueba de escritura SD");
    archivo.println("Sistema embebido OK");
    archivo.close();
    Serial.println("Archivo TEST.TXT creado correctamente.");
  } else {
    Serial.println("Error al crear o abrir TEST.TXT");
  }

  // --- LEER EL CONTENIDO DEL ARCHIVO ---
  Serial.println("\n--- Leyendo el contenido de TEST.TXT ---");
  File lectura = SD.open("TEST.TXT");
  if (lectura) {
    while (lectura.available()) {
      Serial.write(lectura.read()); // Lee letra por letra y la imprime
    }
    lectura.close();
    Serial.println("\n----------------------------------------");
  } else {
    Serial.println("Error al intentar abrir el archivo para leerlo.");
  }
}

void loop() {
  // El loop se queda vacío ya que solo es una prueba de inicio
}