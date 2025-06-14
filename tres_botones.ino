#include <TFT_eSPI.h>              // Librería pantalla TFT
#include <SPI.h>
#include <XPT2046_Touchscreen.h>   // Librería pantalla táctil

// Pines para la pantalla táctil (ajusta según tu hardware)
#define XPT2046_CS 33
#define XPT2046_IRQ 36
#define TFT_BL 14  // Pin backlight

TFT_eSPI tft = TFT_eSPI();
XPT2046_Touchscreen ts(XPT2046_CS, XPT2046_IRQ);

struct Boton {
  int x, y, w, h;
  const char* label;
};

// Definimos 3 botones
Boton botones[3] = {
  {10, 200, 95, 30, "Boton 1"},
  {115, 200, 95, 30, "Boton 2"},
  {220, 200, 95, 30, "Boton 3"}
};

void dibujarBotones() {
  tft.fillScreen(TFT_BLACK);
  tft.setTextSize(2);
  tft.setTextColor(TFT_WHITE);
  for (int i = 0; i < 3; i++) {
    tft.fillRoundRect(botones[i].x, botones[i].y, botones[i].w, botones[i].h, 6, TFT_DARKGREY);
    tft.drawRoundRect(botones[i].x, botones[i].y, botones[i].w, botones[i].h, 6, TFT_WHITE);
    tft.setCursor(botones[i].x + 10, botones[i].y + 8);
    tft.print(botones[i].label);
  }
}

void setup() {
  Serial.begin(115200);
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);

  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, HIGH);  // Enciende backlight

  ts.begin();
  ts.setRotation(1);

  dibujarBotones();
}

void loop() {
  if (ts.touched()) {
    TS_Point p = ts.getPoint();

    // Mapear valores táctiles a coordenadas TFT (ajusta según calibración)
    int tx = map(p.x, 3700, 200, 0, 320);
    int ty = map(p.y, 300, 3800, 0, 240);

    Serial.printf("Tocaste en x=%d y=%d\n", tx, ty);

    // Detectar qué botón fue tocado
    for (int i = 0; i < 3; i++) {
      if (tx >= botones[i].x && tx <= botones[i].x + botones[i].w &&
          ty >= botones[i].y && ty <= botones[i].y + botones[i].h) {
        tft.fillRect(0, 0, 320, 180, TFT_BLACK);
        tft.setCursor(10, 10);
        tft.setTextColor(TFT_YELLOW);
        tft.setTextSize(3);
        tft.printf("Tocaste %s", botones[i].label);
        delay(500);  // Pausa para que se vea el mensaje
        dibujarBotones();
      }
    }

    // Esperar a que suelte el dedo para evitar múltiples activaciones
    while (ts.touched()) {
      delay(10);
    }
  }
}
