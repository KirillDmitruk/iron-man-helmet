#pragma once

#include <Arduino.h>
#include <Servo.h>

class ServoController {
private:
    Servo leftServo;
    Servo rightServo;

    int leftPin;
    int rightPin;

public:
    ServoController(int leftPin, int rightPin);

    void begin();

    void setAngles(int leftAngle, int rightAngle);

    void openMask();
    void closeMask();
};