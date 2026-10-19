#include <Arduino.h>

#include "HelmetConfig.h"
#include "HelmetController.h"

ServoController mask(
    HelmetConfig::LEFT_SERVO_PIN,
    HelmetConfig::RIGHT_SERVO_PIN
);

LedController leftLed(
    HelmetConfig::LEFT_LED_PIN
);

LedController rightLed(
    HelmetConfig::RIGHT_LED_PIN
);

HelmetController helmet(
    mask,
    leftLed,
    rightLed
);

bool lastButtonReading = HIGH;
bool stableButtonState = HIGH;

unsigned long lastDebounceTime = 0;


void setup() {

    Serial.begin(HelmetConfig::SERIAL_BAUD);

    pinMode(
        HelmetConfig::BUTTON_PIN,
        INPUT_PULLUP
    );

    mask.begin();

    leftLed.begin();
    rightLed.begin();

    helmet.begin();

    Serial.println("Helmet system initialized");
}


void handleButton() {

    bool reading = digitalRead(
        HelmetConfig::BUTTON_PIN
    );

    if (reading != lastButtonReading) {
        lastDebounceTime = millis();
    }

    if (
        millis() - lastDebounceTime >
        HelmetConfig::DEBOUNCE_MS
    ) {
        if (reading != stableButtonState) {

            stableButtonState = reading;

            if (stableButtonState == LOW) {
                helmet.execute(
                    HelmetCommand::TOGGLE
                );
            }
        }
    }

    lastButtonReading = reading;
}


void handleSerial() {

    while (Serial.available() > 0) {

        char command = Serial.read();

        switch (command) {

            case 'o':
                helmet.execute(
                    HelmetCommand::OPEN
                );
                break;

            case 'c':
                helmet.execute(
                    HelmetCommand::CLOSE
                );
                break;

            case 't':
                helmet.execute(
                    HelmetCommand::TOGGLE
                );
                break;
        }
    }
}


void loop() {

    handleButton();

    handleSerial();
}