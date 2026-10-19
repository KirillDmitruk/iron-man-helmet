#include <Arduino.h>

#include "HelmetConfig.h"
#include "HelmetController.h"
#include "MotionController.h"

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

MotionController motion(mask);

HelmetController helmet(
    motion,
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

    Serial.println("Helmet initialized");
    Serial.println("Position UNKNOWN");
    Serial.println("Calibrate before sending i");
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
                helmet.execute(HelmetCommand::TOGGLE);
            }
        }
    }

    lastButtonReading = reading;
}


void handleSerial() {
    while (Serial.available() > 0) {
        char input = Serial.read();

        HelmetCommand command;

        switch (input) {
            case 'i':
                command = HelmetCommand::INITIALIZE_CLOSED;
                break;

            case 'o':
                command = HelmetCommand::OPEN;
                break;

            case 'c':
                command = HelmetCommand::CLOSE;
                break;

            case 't':
                command = HelmetCommand::TOGGLE;
                break;

            case 's':
                command = HelmetCommand::STOP;
                break;

            default:
                continue;
        }

        bool accepted = helmet.execute(command);

        Serial.println(
            accepted ? "COMMAND ACCEPTED" : "COMMAND REJECTED"
        );
    }
}


void loop() {
    handleButton();
    handleSerial();

    helmet.update();
}