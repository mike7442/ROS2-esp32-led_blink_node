/*
 * Filename: simple_GPIO_TCP_control.ino
 * Description: Control a digital pin (e.g., D48 or any GPIO) via TCP ('1' to HIGH, '0' to LOW).
 *              Works on regular ESP32 / ESP32-C3 / ESP8266.
 * Author: Based on user request
 */

#include <WiFi.h>

// Пин, которым будем управлять
const int ledPin = 48; // Можно заменить на любой GPIO

// Настройки Wi-Fi
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

WiFiServer server(8080);  // TCP сервер на порту 8080

void setup() {
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

  // Настройка пина как выход
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);  // Начальное состояние — выключен
}

void loop() {
  WiFiClient client = server.available();   // Проверяем, есть ли новый клиент

  if (client) {
    Serial.println("New client connected");
    while (client.connected()) {
      if (client.available()) {
        char command = client.read();
        if (command == '1') {
          digitalWrite(ledPin, HIGH);  // Включить пин
          client.println("Pin ON");
          Serial.println("Pin ON");
        } else if (command == '0') {
          digitalWrite(ledPin, LOW);   // Выключить пин
          client.println("Pin OFF");
          Serial.println("Pin OFF");
        }
      }
      delay(1); // Небольшая задержка
    }
    client.stop();  // Клиент отключился
    Serial.println("Client disconnected");
  }
}
