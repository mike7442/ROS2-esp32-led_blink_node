#include <Adafruit_NeoPixel.h>

#define RGB_PIN     48      // Onboard RGB LED pin
#define NUM_PIXELS  1       // Only one LED

Adafruit_NeoPixel pixel(NUM_PIXELS, RGB_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  pixel.begin();
  pixel.setBrightness(100); // Adjust brightness (0-255)
  Serial.begin(115200);

  // Начальное состояние — светодиод выключен
  pixel.setPixelColor(0, 0);
  pixel.show();
}

void loop() {
  if (Serial.available() > 0) {
    char command = Serial.read();

    if (command == '1') {
      // Включаем светодиод постоянным цветом (красный: 255,0,0)
      pixel.setPixelColor(0, pixel.Color(255, 0, 0)); // Можно изменить на любой другой цвет
      pixel.show();
      Serial.println("LED ON");
    } else if (command == '0') {
      // Выключаем светодиод
      pixel.setPixelColor(0, 0);
      pixel.show();
      Serial.println("LED OFF");
    }
  }
}
