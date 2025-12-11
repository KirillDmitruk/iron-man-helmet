#ifndef LED_CONTROLLER_H
#define LED_CONTROLLER_H

#include <Arduino.h>

class LedController {
private:
    int pin;  // пин, к которому подключены светодиоды
public:
    LedController(int pin);
    void begin();             // инициализация
    void on();                // включить светодиоды
    void off();               // выключить светодиоды
};

#endif
