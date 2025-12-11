#include <Arduino.h>
#include "ServoController.h"
#include "LedController.h"

#define LEFT_SERVO_PIN 9
#define RIGHT_SERVO_PIN 10
#define BUTTON_PIN 2
#define LEFT_LED_PIN 6
#define RIGHT_LED_PIN 7

ServoController mask(LEFT_SERVO_PIN, RIGHT_SERVO_PIN);
LedController left_led(LEFT_LED_PIN);
LedController right_led(RIGHT_LED_PIN);

bool isOpen = false;
bool prevState = HIGH;

void setup() {
    Serial.begin(115200);
    pinMode(BUTTON_PIN, INPUT_PULLUP);

    mask.begin();
    left_led.begin();
    right_led.begin();
    left_led.off();
    right_led.off();

    Serial.println("Готов к управлению маской и светодиодами.");
}

void loop() {
    // --- Управление кнопкой ---
    bool currentState = digitalRead(BUTTON_PIN);
    if (prevState == HIGH && currentState == LOW) {
        if (isOpen) {
            mask.closeMask();
            left_led.off();
            right_led.off();
        } else {
            mask.openMask();
            left_led.on();
            right_led.on();
        }
        isOpen = !isOpen;
        delay(250); // антидребезг
    }
    prevState = currentState;

    // --- Управление через Serial ---
    if (Serial.available() > 0) {
        char cmd = Serial.read();
        if (cmd == 'o') { mask.openMask(); isOpen = true; left_led.on(); right_led.on(); }
        else if (cmd == 'c') { mask.closeMask(); isOpen = false; left_led.off(); right_led.off(); }
    }
}
