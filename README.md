# Diseño electrónico basado en sistemas embebidos

![ESP32](https://img.shields.io/badge/ESP32-E7352C?style=flat-square&logo=espressif&logoColor=white)
![Arduino](https://img.shields.io/badge/Arduino-00878F?style=flat-square&logo=arduino&logoColor=white)
![PlatformIO](https://img.shields.io/badge/PlatformIO-F5822A?style=flat-square&logo=platformio&logoColor=white)
![C++](https://img.shields.io/badge/C%2B%2B-00599C?style=flat-square&logo=cplusplus&logoColor=white)
![Python](https://img.shields.io/badge/Python-3776AB?style=flat-square&logo=python&logoColor=white)
![TensorFlow](https://img.shields.io/badge/TensorFlow-FF6F00?style=flat-square&logo=tensorflow&logoColor=white)

Prácticas de laboratorio, examen y proyectos de la materia **Diseño Electrónico Basado en Sistemas Embebidos** (Ingeniería en Sistemas Computacionales, UAT — UAM Mante, 2026).

El recorrido va desde E/S digital básica en Arduino Uno hasta estaciones de monitoreo IoT con ESP32 que publican en ThingSpeak, y cierra con un **clasificador de residuos por visión artificial** (MobileNetV2 + OpenCV + Arduino).

---

## Contenido

| Carpeta | Tipo | Placa | Qué hace |
|---|---|---|---|
| [`Practicas Laboratorio/`](Practicas%20Laboratorio/) | Labs 01–03 | Arduino Uno | Salidas digitales (Blink), pulsadores con *debounce*, PWM, LED "respirando" y melodía con buzzer |
| [`Practicas 04_08/`](Practicas%2004_08/) | Labs 04–08 | Arduino Uno (Wokwi) | Lectura analógica (LDR, potenciómetro), DHT22, servo y motor DC, bus I²C con OLED, tarjeta SD y estación de monitoreo con máquina de estados |
| [`EXAMEN/`](EXAMEN/) | Examen | Arduino Uno | Monitor de temperatura y humedad con DHT22, alertas por LED y buzzer, e índice de calor |
| [`ESP32_DHT22_Servo_ThingSpeak/`](ESP32_DHT22_Servo_ThingSpeak/) | Proyecto | ESP32 | Lee DHT22, barre un servo SG90 sin bloquear (`millis()`) y publica temperatura y humedad en ThingSpeak |
| [`ESP32_BMP280_OLED_Thingspeak/`](ESP32_BMP280_OLED_Thingspeak/) | Proyecto | ESP32 | Estación meteorológica: BMP280 + DHT22, muestra lecturas en OLED SSD1306 y las envía a ThingSpeak |
| [`ProyectoTermHumdPBaro/`](ProyectoTermHumdPBaro/) | Proyecto | ESP32 | Termo-higrómetro barométrico: DHT22 + BMP280, calcula punto de rocío y publica 5 campos en ThingSpeak |
| [`Proyecto Integrador/`](Proyecto%20Integrador/) | Proyecto final | PC + Arduino Uno | **Clasificador de aluminio y plástico** con visión artificial (ver abajo) |

### Proyecto integrador: clasificación de residuos con visión artificial

Una cámara detecta el objeto con sustracción de fondo (MOG2), un modelo **MobileNetV2** afinado con *transfer learning* lo clasifica como aluminio o plástico, y Python envía la decisión por puerto serie a un Arduino que mueve un servo para abrir la trampilla correcta. Incluye interfaz en Tkinter con estadísticas en tiempo real.

- Exactitud en el conjunto de prueba: **94.8 %** (1,896 de 2,000 imágenes; ver matriz de confusión en el manual técnico).
- Documentación completa: [manual técnico](Proyecto%20Integrador/README.md), [`Manual Tecnico.pdf`](Proyecto%20Integrador/Manual%20Tecnico.pdf) y [`Manual de Usuario.pdf`](Proyecto%20Integrador/Manual%20de%20Usuario.pdf).
- Proyecto en equipo: Pesina Santander Edgar Gael, Esquivel Rodríguez Guillermo, Rubio Martínez Jesús Rafael, Borjas Arias Ronaldo Antonio y Avalos Castillo Armando de Jesús.

### Simulaciones en Wokwi

| Práctica | Simulación |
|---|---|
| Lab04 — LDR y potenciómetro | [wokwi.com/projects/460693533293543425](https://wokwi.com/projects/460693533293543425) |
| Lab05 — DHT22 | [wokwi.com/projects/460695073394107393](https://wokwi.com/projects/460695073394107393) |
| Lab06 — Servo con potenciómetro | [wokwi.com/projects/461053739245466625](https://wokwi.com/projects/461053739245466625) |
| Lab07 — Escáner I²C y OLED | [wokwi.com/projects/461055946383781889](https://wokwi.com/projects/461055946383781889) |
| Lab08 — Tarjeta SD | [wokwi.com/projects/461232102849610753](https://wokwi.com/projects/461232102849610753) |

---

## Cómo compilar

### Proyectos PlatformIO (carpetas con `platformio.ini`)

1. Instala [VS Code](https://code.visualstudio.com/) con la extensión **PlatformIO IDE** (el repositorio la recomienda automáticamente).
2. Abre la carpeta del proyecto, por ejemplo `ESP32_DHT22_Servo_ThingSpeak/`.
3. **Credenciales:** en los proyectos con WiFi, copia `src/secrets.example.h` como `src/secrets.h` y escribe tu red y tu *Write API Key* de ThingSpeak. Ese archivo está en `.gitignore` y nunca se sube.
4. Compila y carga:

```bash
pio run --target upload
pio device monitor
```

Las bibliotecas (`DHT`, `Adafruit BMP280`, `SSD1306`, `ThingSpeak`, `ESP32Servo`) se descargan solas desde `lib_deps`.

### Sketches de Arduino (`.ino`)

Ábrelos en Arduino IDE 2.x o súbelos a [Wokwi](https://wokwi.com) junto con su `diagram.json` y `libraries.txt`.

> **Nota de hardware:** al usar WiFi, la ESP32 tiene picos de consumo que pueden reiniciarla. Alimenta los sensores con una fuente de 3.3 V aparte y une las tierras (GND).

---

## Estructura

```
.
├── Practicas Laboratorio/        Labs 01–03 (E/S digital, PWM)
├── Practicas 04_08/              Labs 04–08 (sensores, actuadores, I²C, SD)
├── EXAMEN/                       Examen práctico (PlatformIO + evidencias)
├── ESP32_DHT22_Servo_ThingSpeak/ ESP32 + DHT22 + servo → ThingSpeak
├── ESP32_BMP280_OLED_Thingspeak/ ESP32 + BMP280 + OLED → ThingSpeak
├── ProyectoTermHumdPBaro/        ESP32 + DHT22 + BMP280 → ThingSpeak
└── Proyecto Integrador/          Clasificador de residuos (Python + Arduino)
```

## Autor

**Edgar Gael Pesina Santander** — Ingeniería en Sistemas Computacionales, Universidad Autónoma de Tamaulipas.
GitHub: [@EdgarPStder](https://github.com/EdgarPStder)

## Licencia

Código bajo licencia [MIT](LICENSE).
