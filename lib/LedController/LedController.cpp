#include "LedController.h"

LedController::LedController(int p) {
    pin = p;
}

void LedController::begin() {
    pinMode(pin, OUTPUT);
    off();
}

void LedController::on() {
    digitalWrite(pin, HIGH); // питание на пин - LED загорается
}

void LedController::off() {
    digitalWrite(pin, LOW);  // питание на пин - LED гаснет
}
