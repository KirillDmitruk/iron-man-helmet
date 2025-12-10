#include <Arduino.h>
#include "ServoController.h"

// Укажи пины подключения серв
#define LEFT_SERVO_PIN 9
#define RIGHT_SERVO_PIN 10

ServoController mask(LEFT_SERVO_PIN, RIGHT_SERVO_PIN);

void setup() {
    Serial.begin(115200);
    mask.begin();

    Serial.println("Готов к управлению маской.");
    Serial.println("Введите 'o' для открытия, 'c' для закрытия.");
}

void loop() {
    if (Serial.available() > 0) {
        char cmd = Serial.read();

        if (cmd == 'o') {
            mask.openMask();
        }
        else if (cmd == 'c') {
            mask.closeMask();
        }
    }
}
