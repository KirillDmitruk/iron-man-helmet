#include "ServoController.h"
#include "HelmetConfig.h"

ServoController::ServoController(int leftPin, int rightPin)
    : leftPin(leftPin), rightPin(rightPin) {}


void ServoController::begin() {
    leftServo.attach(leftPin);
    rightServo.attach(rightPin);
}


void ServoController::setAngles(
    int leftAngle,
    int rightAngle
) {
    leftServo.write(
        constrain(leftAngle, 0, 180)
    );

    rightServo.write(
        constrain(rightAngle, 0, 180)
    );
}


void ServoController::openMask() {
    setAngles(
        HelmetConfig::LEFT_OPEN_ANGLE,
        HelmetConfig::RIGHT_OPEN_ANGLE
    );
}


void ServoController::closeMask() {
    setAngles(
        HelmetConfig::LEFT_CLOSED_ANGLE,
        HelmetConfig::RIGHT_CLOSED_ANGLE
    );
}