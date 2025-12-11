#include "ServoController.h"

ServoController::ServoController(int leftPin, int rightPin)
    : leftPin(leftPin), rightPin(rightPin) {}

void ServoController::begin() {
    leftServo.attach(leftPin);
    rightServo.attach(rightPin);

    // начальные позиции маски (закрыта)
    leftServo.write(0);
    rightServo.write(0);
}

void ServoController::openMask() {
    Serial.println("Открываю маску...");
    leftServo.write(180);
    rightServo.write(180);
}

void ServoController::closeMask() {
    Serial.println("Закрываю маску...");
    leftServo.write(0);
    rightServo.write(0);
}
