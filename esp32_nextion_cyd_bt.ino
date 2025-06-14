//##########################################################################################
//####    ESP32-2432S028R CHEAP YELLOW DISPLAY MMDVM NEXTION EMULADOR 2025 by EA4AOJ    ####
//##########################################################################################

#include <TFT_eSPI.h>
#include <SPI.h>
#include <XPT2046_Touchscreen.h>
#include <regex>
#include <map>
#include <BluetoothSerial.h>


BluetoothSerial SerialBT;

// Definimos las patillas del esp32 que corresponden a los leds (led multicolor)
#define CYD_LED_BLUE 17
#define CYD_LED_RED 4
#define CYD_LED_GREEN 16

// Configuración de la pantalla táctil
#define XPT2046_IRQ 36
#define XPT2046_MOSI 32
#define XPT2046_MISO 39
#define XPT2046_CLK 25
#define XPT2046_CS 33

SPIClass mySpi = SPIClass(VSPI);
XPT2046_Touchscreen touchscreen(XPT2046_CS, XPT2046_IRQ);

TFT_eSPI tft = TFT_eSPI();

String estacion = "N/A", estacionAnt = "";
String fechaHora = "N/A", fechaHoraAnt = "";
String rx = "N/A", rxAnt = "";
String tx = "N/A", txAnt = "";
String tg = "N/A", tgAnt = "";
String estado = "N/A", estadoAnt = "";
String ber = "N/A", berAnt = "";
String rssi = "N/A", rssiAnt = "";
String temp = "N/A", tempAnt = "";
String ip = "N/A", ipAnt = "";
String pantallaEstadoAnterior = "";

bool datosRecibidos = false;

bool backlightOn = true;  // Estado inicial backlight encendido
unsigned long lastTouchToggle = 0;
const unsigned long debounceDelay = 500; // 500 ms debounce para no cambiar varias veces rápido

unsigned long lastBERTime = 0;
unsigned long lastRSSITime = 0;
const unsigned long timeout = 1400;

String buffer = "";
unsigned long lastCharTime = 0;

// Nueva variable para el estado de la pantalla
String pantallaEstado = "1";  // Estado inicial: "reposo"

void setup() {
  Serial.begin(9600);
  SerialBT.setPin("1234", 4);
  SerialBT.begin("ESP32Nextion");
  
  mySpi.begin(XPT2046_CLK, XPT2046_MISO, XPT2046_MOSI, XPT2046_CS);
  touchscreen.begin(mySpi);

  pinMode(TFT_BL, OUTPUT);
    
  // Ponemos los pins del esp32 como salida
  pinMode(CYD_LED_RED, OUTPUT);
  pinMode(CYD_LED_GREEN, OUTPUT);
  pinMode(CYD_LED_BLUE, OUTPUT);

  digitalWrite(CYD_LED_RED, LOW); // LOW encendido
  digitalWrite(CYD_LED_GREEN, HIGH); // HIGH apagado
  digitalWrite(CYD_LED_BLUE, HIGH); // // HIGH apagado
  
  tft.init();
  tft.setRotation(3);
  tft.fillScreen(TFT_BLACK);
  tft.setTextFont(4);
  tft.setTextDatum(TL_DATUM);
  tft.setTextColor(TFT_CYAN);
  tft.setCursor(45, 90);
  tft.println("Esperando datos...");
  
}

void loop() {
  // 🔷 UART cableada
  while (Serial.available()) {
    char c = Serial.read();
//  SerialBT.write(c);           // Lo envío por Bluetooth (comentado para que no reenvie)
    buffer += c;
    lastCharTime = millis();
  }

  // 🔷 Bluetooth
  while (SerialBT.available()) {
    char c = SerialBT.read();
//  Serial.write(c);             // Lo envío por UART físico (comentado para que no reenvie)
    buffer += c;
    lastCharTime = millis();
  }

  if (millis() - lastBERTime > timeout) {
    ber = "N/A";
  }
  if (millis() - lastRSSITime > timeout) {
    rssi = "N/A";
  }

  if (buffer.length() > 0 && millis() - lastCharTime > 10) {
    Serial.println("Recibido: " + buffer);
    if (!datosRecibidos) {
      displayReposo();
      datosRecibidos = true;
    }

    parseData(buffer);
    buffer = "";
  }

  if (pantallaEstado == "1") {
    drawpantallareposo(false);
  } else {
    drawpantallaactiva(false);
  }

  if (touchscreen.touched()) {
    unsigned long now = millis();
    if (now - lastTouchToggle > debounceDelay) {
      backlightOn = !backlightOn;
      digitalWrite(TFT_BL, backlightOn ? TFT_BACKLIGHT_ON : !TFT_BACKLIGHT_ON);
      lastTouchToggle = now;
    }
    while (touchscreen.touched()) delay(10);
  }
}
 
void drawBoxreposo(int x, int y, String label, String value, uint16_t boxColor, uint16_t textColor) {
  tft.fillRoundRect(x, y, 150, 40, 5, boxColor); // Altura aumentada a 40px
  tft.setTextFont(1);
  
  // Configuración específica para Frecuencia RX
  if(label == "RX") {
    tft.setTextSize(2);//tamaño de la fuente modificada la por defecto era (1)
    tft.setTextColor(textColor, boxColor); 
    // Ajustar posición del texto
    tft.setCursor(x + 8, y + 12); // Posición vertical modificada      
    tft.print(value);
    
  }
  // Configuración específica para Frecuencia TX
  else if(label == "TX") {      
    tft.setTextSize(2);//tamaño de la fuente modificada la por defecto era (1)
    tft.setTextColor(textColor, boxColor);
    // Ajustar posición del texto
    tft.setCursor(x + 8, y + 12); // Posición vertical modificada
    tft.print(value);
}

  else {
    // Configuración original para otros elementos
    tft.setTextSize(1);
    tft.setTextColor(textColor, boxColor);
    tft.setCursor(x + 5, y + 5);
    tft.print(label + ": ");
    tft.setCursor(x + 5, y + 17);
    tft.print(value);
  }
}

void drawBoxactividad(int x, int y, String label, String value, uint16_t boxColor, uint16_t textColor) {
  tft.fillRoundRect(x, y, 150, 30, 5, boxColor);
  tft.setTextFont(1);
  tft.setTextSize(1);
  tft.setTextColor(textColor, boxColor);
  tft.setCursor(x + 5, y + 5);
  tft.print(label + ": ");
  tft.setCursor(x + 5, y + 17);
  tft.print(value);
}

// Variables globales para el scroll
unsigned long indicativoScrollTime = 0;
int indicativoOffset = 0;
bool indicativoScrollPaused = false;
unsigned long indicativoPauseTime = 0;

void drawBoxindicativo(int x, int y, String label, String value, uint16_t boxColor, uint16_t textColor) {
  const int boxWidth = 305;
  const int boxHeight = 50;
  const int padding = 0;
  const int scrollSpeed = 20;
  const int pauseDuration = 500;

  int visibleWidth = boxWidth - 2 * padding;
  int textWidth = tft.textWidth(value);

  // Ajustes de márgenes
  int marginLeft = padding ;  // margen izquierdo ajustable
  int marginTop = 0;          // margen superior ajustable

  // Dibuja la caja exterior
  tft.fillRoundRect(x, y - 5, boxWidth, boxHeight, 5, boxColor);

  // Limita el área de dibujo solo al área del texto dentro de la caja, con márgenes ajustados
  tft.setViewport(x + marginLeft, y - marginTop, visibleWidth - (marginLeft - padding), boxHeight - (10 - (marginTop - 5)));

  // Limpia solo la zona del texto (no toda la caja)
  tft.fillRect(x + marginLeft, y - marginTop, visibleWidth - (marginLeft - padding), boxHeight - (10 - (marginTop - 5)), boxColor);

  tft.setTextFont(4);
  tft.setTextColor(textColor, boxColor);
  tft.setTextWrap(false);

  if (textWidth <= visibleWidth) {
    // Si cabe, mostrar directamente sin scroll
    indicativoOffset = 0;
    indicativoScrollPaused = false;
    tft.setCursor(x + marginLeft, y + marginTop);
    tft.print(value);
  } else {
    unsigned long now = millis();

    // Control del scroll
    if (!indicativoScrollPaused && now - indicativoScrollTime > scrollSpeed) {
      indicativoOffset++;
      indicativoScrollTime = now;

      if (indicativoOffset > textWidth + 30) {
        indicativoScrollPaused = true;
        indicativoPauseTime = now;
        indicativoOffset = 0;
      }
    }

    // Control de pausa
    if (indicativoScrollPaused && now - indicativoPauseTime > pauseDuration) {
      indicativoScrollPaused = false;
      indicativoScrollTime = now;
    }

    int scrollX = x + marginLeft - indicativoOffset;

    // Imprime el texto desplazado
    tft.setCursor(scrollX, y + marginTop);
    tft.print(value);

    // Segunda pasada para continuidad
    if (textWidth - indicativoOffset < visibleWidth) {
      tft.setCursor(scrollX + textWidth + 30, y + marginTop);
      tft.print(value);
    }
  }

  // Restaurar área de dibujo completa
  tft.resetViewport();
}

void displayReposo() {
  digitalWrite(CYD_LED_RED, HIGH); 
  digitalWrite(CYD_LED_GREEN, HIGH);
  digitalWrite(CYD_LED_BLUE, LOW);
  tft.fillScreen(TFT_BLACK);
     
  drawBoxreposo(5, 10, "Escuchado", estacion, TFT_NAVY, TFT_WHITE);
  drawBoxreposo(160, 10, "Estacion", estado, TFT_PURPLE, TFT_WHITE);
  drawBoxreposo(5, 150, "RX", rx, TFT_BLUE, TFT_WHITE);  // Modificado
  drawBoxreposo(160, 150, "TX", tx, TFT_BLUE, TFT_WHITE);
  drawBoxreposo(5, 190, "Temperatura", temp, TFT_ORANGE , TFT_BLACK),tft.setTextSize(2);
  drawBoxreposo(160, 190, "IP", ip, TFT_BROWN, TFT_WHITE);
}

void displayActividad() {
  digitalWrite(CYD_LED_RED, HIGH); 
  digitalWrite(CYD_LED_GREEN, LOW);
  digitalWrite(CYD_LED_BLUE, HIGH);
  tft.fillScreen(TFT_BLACK);
  String indicativo = estacion.substring(0, 30);  // Primeros 10 caracteres
  drawBoxindicativo(5, 10, "", indicativo, TFT_NAVY, TFT_WHITE);
  drawBoxactividad(5, 70, "Frecuencia RX", rx, TFT_BLUE, TFT_WHITE);
  drawBoxactividad(160, 70, "Frecuencia TX", tx, TFT_BLUE, TFT_WHITE);
  drawBoxactividad(5, 110, "TG", tg, TFT_NAVY, TFT_WHITE);
  drawBoxactividad(160, 110, "Estado", estado, TFT_PURPLE, TFT_WHITE);
  drawBoxactividad(5, 150, "BER", ber, TFT_MAROON, TFT_WHITE);
  drawBoxactividad(160, 150, "RSSI", rssi, TFT_ORANGE, TFT_BLACK);
  drawBoxactividad(5, 190, "Temperatura", temp, TFT_CYAN, TFT_BLACK);
  drawBoxactividad(160, 190, "IP", ip, TFT_BROWN, TFT_WHITE);
}

void drawpantallareposo(bool fullRedraw) {
  
  if (fullRedraw || fechaHora != fechaHoraAnt) {
  String hora = fechaHora.substring(9);
   String fecha = fechaHora.substring(0, 8);   // "09/06/25"
    
tft.setTextSize(6);
tft.setTextColor(TFT_WHITE, TFT_BLACK);
tft.drawString(hora, 15, 75); 
tft.setTextSize(1);
tft.setTextColor(TFT_DARKGREY, TFT_BLACK);
tft.drawString(fecha, 20, 125, 2);    
  
fechaHoraAnt = fechaHora;
}
  tft.setTextSize(1);

  if (fullRedraw || estacion != estacionAnt) {
    String indicativo = estacion.substring(0, 20);  // Primeros 30 caracteres
    drawBoxreposo(5, 10, "Escuchado", indicativo, TFT_NAVY, TFT_WHITE);
    estacionAnt = indicativo;
  }
  
  if (fullRedraw || estado != estadoAnt) {
    drawBoxreposo(160, 10, "Estacion", estado, TFT_PURPLE, TFT_WHITE);
    estadoAnt = estado;
  }

  if (fullRedraw || rx != rxAnt) {
    drawBoxreposo(5, 150, "Frecuencia RX", rx, TFT_BLUE, TFT_WHITE);
    rxAnt = rx;
  }
  
  if (fullRedraw || tx != txAnt) {
    drawBoxreposo(160, 150, "Frecuencia TX", tx, TFT_PURPLE, TFT_WHITE);
    txAnt = tx;
  }

  
  if (fullRedraw || temp != tempAnt) {
    drawBoxreposo(5, 190, "Temperatura", temp, TFT_CYAN, TFT_BLACK);
    tempAnt = temp;
    tft.setTextSize(2);
  }
  
  if (fullRedraw || ip != ipAnt) {
    drawBoxreposo(160, 190,  "IP", ip, TFT_BROWN, TFT_WHITE);
    ipAnt = ip;
  }
}

void drawpantallaactiva(bool fullRedraw) {
  if (fullRedraw || estacion != estacionAnt) {
    String indicativo = estacion.substring(0, 25);  // Primeros 30 caracteres
    drawBoxindicativo(5, 10,  "", indicativo, TFT_NAVY, TFT_WHITE);
    estacionAnt = indicativo;
  }
  
  if (fullRedraw || rx != rxAnt) {
    tft.setTextSize(1);
    drawBoxactividad(5, 70,  "Frecuencia RX", rx, TFT_BLUE, TFT_WHITE);
    rxAnt = rx;
  }
  if (fullRedraw || tx != txAnt) {
    drawBoxactividad(160, 70, "Frecuencia TX", tx, TFT_BLUE, TFT_WHITE);
    txAnt = tx;
  }
  if (fullRedraw || tg != tgAnt) {
    drawBoxactividad(5, 110, "TG", tg, TFT_NAVY, TFT_WHITE);
    tgAnt = tg;
  }
  if (fullRedraw || estado != estadoAnt) {
    drawBoxactividad(160, 110, "Estado", estado, TFT_PURPLE, TFT_WHITE);
    estadoAnt = estado;
  }
  if (fullRedraw || ber != berAnt) {
    drawBoxactividad(5, 150, "BER", ber, TFT_MAROON, TFT_WHITE);
    berAnt = ber;
  }
  if (fullRedraw || rssi != rssiAnt) {
    drawBoxactividad(160, 150, "RSSI", rssi, TFT_ORANGE, TFT_BLACK);
    rssiAnt = rssi;
  }
  if (fullRedraw || temp != tempAnt) {
    drawBoxactividad(5, 190, "Temperatura", temp, TFT_CYAN, TFT_BLACK);
    tempAnt = temp;
    tft.setTextSize(2);
  }
  if (fullRedraw || ip != ipAnt) {
    drawBoxactividad(160, 190,  "IP", ip, TFT_BROWN, TFT_WHITE);
    ipAnt = ip;
  }
}

void parseData(const String& data) {
  std::map<String, std::regex> patterns = {
    {"Fecha y Hora", std::regex("t2\\.txt=\"([^\"]+)\"")},
    {"Estacion", std::regex("t[02]\\.txt=\"([^\"]+)\"")},
    {"RX", std::regex("t30\\.txt=\"([^\"]+)\"")},
    {"TX", std::regex("t32\\.txt=\"([^\"]+)\"")},
    {"TG", std::regex("t[13]\\.txt=\"([^\"]+)\"")},
    {"Estado", std::regex("t0\\.txt=\"([^\"]+)\"")},
    {"BER", std::regex("t[47]\\.txt=\"([^\"]+)\"")},
    {"RSSI", std::regex("t[35]\\.txt=\"([^\"]+)\"")},
    {"Temp", std::regex("t20\\.txt=\"([^\"]+)\"")},
    {"IP", std::regex("t3\\.txt=\"([^\"]+)\"")},
    {"PantallaEstado", std::regex("MMDVM\\.status\\.val=(\\d+)")}
  };

  std::string input = data.c_str();

  bool huboStatusVal = false;
  bool posibleReposoPorFecha = false;
  bool posibleActividad = false;

  // Para cada patrón, iterar sobre todas las coincidencias en input
  for (const auto& [campo, patron] : patterns) {
    auto begin = std::sregex_iterator(input.begin(), input.end(), patron);
    auto end = std::sregex_iterator();

    for (auto it = begin; it != end; ++it) {
      std::smatch match = *it;
      String valor = match[1].str().c_str();

      // Validaciones básicas
      if (campo == "Fecha y Hora" && valor.indexOf(':') == -1) continue;
      if (campo == "RSSI" && !valor.startsWith("-")) continue;
      if (campo == "IP" && valor.indexOf('.') == -1) continue;
      if (campo == "BER" && valor.indexOf('%') == -1) continue;
      if (campo == "TG" && valor.indexOf("TG") == -1 && valor.indexOf("DG-ID") == -1) continue;

      String limpio = valor;
      limpio.trim();
      if (campo == "Estacion" &&
      !(limpio.startsWith("2 N ") || limpio.startsWith("2 R ") || 
      limpio.startsWith("N ") || limpio.startsWith("R "))) continue;


      // Asignar variables según el campo
      if (campo == "Estacion") {
      if (valor.indexOf("/") != -1 && valor.indexOf(":") != -1) {
      fechaHora = valor;
       } else {
       estacion = valor;
  }

      } else if (campo == "Fecha y Hora") {
        if (valor.indexOf("/") != -1) {
          fechaHora = valor;
          posibleReposoPorFecha = true;
        }
      } else {
        if (campo == "RX") rx = valor;
        else if (campo == "TX") tx = valor;
        else if (campo == "IP") ip = valor;
        else if (campo == "Estado") estado = valor;
        else if (campo == "BER") {
          ber = valor;
          lastBERTime = millis();
        } else if (campo == "RSSI") {
          rssi = valor;
          lastRSSITime = millis();
        } else if (campo == "Temp") {
          String limpia = "";
          for (int i = 0; i < valor.length(); i++) {
            char c = valor[i];
            if (isdigit(c) || c == '.') {
              limpia += c;
            }
          }
          temp = limpia + " deg C";
        } else if (campo == "TG") tg = valor;
      }
    }
  }

  // Verificar si llegó MMDVM.status.val
  {
    auto begin = std::sregex_iterator(input.begin(), input.end(), patterns["PantallaEstado"]);
    auto end = std::sregex_iterator();

    for (auto it = begin; it != end; ++it) {
      std::smatch match = *it;
      String valPantallaEstado = match[1].str().c_str();
      if (valPantallaEstado == "1") {
        pantallaEstado = "1";  // Reposo
      } else {
        pantallaEstado = "3";  // Actividad (para cualquier otro número)
      }
      huboStatusVal = true;
    }
  }

  // Si no hubo status.val, usar heurísticas alternativas // C4FM usa t1.txt para el DG ID
  if (!huboStatusVal) {
    if (data.indexOf("t1.txt=") != -1) {
      posibleActividad = true;
    }

    if (posibleActividad) {
      pantallaEstado = "3";  // Actividad
    } else if (posibleReposoPorFecha) {
      pantallaEstado = "1";  // Reposo
    }
  }

  // Cambiar pantalla solo si el estado ha cambiado
  if (pantallaEstado != pantallaEstadoAnterior) {
    if (pantallaEstado == "1") {
      displayReposo();
    } else {
      displayActividad();
    }
    pantallaEstadoAnterior = pantallaEstado;
  }
}
