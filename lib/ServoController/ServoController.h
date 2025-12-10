#ifndef SERVO_CONTROLLER_H
#define SERVO_CONTROLLER_H

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
    void openMask();
    void closeMask();
};
#endif