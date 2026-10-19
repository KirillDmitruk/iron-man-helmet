#include "ServoController.h"
#include "HelmetConfig.h"

ServoController::ServoController(
    int leftPin,
    int rightPin
)
    : leftPin(leftPin),
      rightPin(rightPin) {}


void ServoController::begin() {
    leftServo.attach(leftPin);
    rightServo.attach(rightPin);

    // No automatic position command on startup.
}


void ServoController::openMask() {
    leftServo.write(
        HelmetConfig::LEFT_OPEN_ANGLE
    );

    rightServo.write(
        HelmetConfig::RIGHT_OPEN_ANGLE
    );
}


void ServoController::closeMask() {
    leftServo.write(
        HelmetConfig::LEFT_CLOSED_ANGLE
    );

    rightServo.write(
        HelmetConfig::RIGHT_CLOSED_ANGLE
    );
}