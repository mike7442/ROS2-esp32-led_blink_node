// Пин, к которому подключен светодиод
const int ledPin = 5; // Встроенный светодиод на большинстве Arduino

void setup() {
  // Инициализация UART
  Serial.begin(115200);

  // Настройка пина светодиода как выход
  pinMode(ledPin, OUTPUT);

  // Начальное состояние — светодиод выключен
  digitalWrite(ledPin, LOW);
}

void loop() {
  if (Serial.available() > 0) {
    // Чтение одного байта
    char command = Serial.read();

    if (command == '1') {
      digitalWrite(ledPin, HIGH); // Включить светодиод
    } else if (command == '0') {
      digitalWrite(ledPin, LOW);  // Выключить светодиод
    }
  }
}
