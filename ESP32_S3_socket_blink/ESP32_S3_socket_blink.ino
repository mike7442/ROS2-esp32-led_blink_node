#include <WiFi.h>
#include <Adafruit_NeoPixel.h>

#define RGB_PIN     48      // Onboard RGB LED pin
#define NUM_PIXELS  1       // Only one LED

Adafruit_NeoPixel pixel(NUM_PIXELS, RGB_PIN, NEO_GRB + NEO_KHZ800);

// Настройки Wi-Fi
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

WiFiServer server(8080);  // TCP сервер на порту 8080

void setup() {
  pixel.begin();
  pixel.setBrightness(100);
  
  Serial.begin(115200);
  delay(10);

  // Подключаемся к Wi-Fi
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.begin();
  Serial.println("TCP Server started");

  // Начальное состояние — светодиод выключен
  pixel.setPixelColor(0, 0);
  pixel.show();
}

void loop() {
  WiFiClient client = server.available();   // Проверяем, есть ли новый клиент

  if (client) {
    Serial.println("New client connected");
    while (client.connected()) {
      if (client.available()) {
        char command = client.read();
        if (command == '1') {
          pixel.setPixelColor(0, pixel.Color(255, 0, 0)); // Включить светодиод (красный)
          pixel.show();
          client.println("LED ON");
          Serial.println("LED ON");
        } else if (command == '0') {
          pixel.setPixelColor(0, 0);                      // Выключить светодиод
          pixel.show();
          client.println("LED OFF");
          Serial.println("LED OFF");
        }
      }
      delay(1); // Небольшая задержка, чтобы не нагружать процессор
    }
    client.stop();  // Клиент отключился
    Serial.println("Client disconnected");
  }
}
