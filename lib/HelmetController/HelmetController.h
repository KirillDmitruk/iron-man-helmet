#pragma once

#include <Arduino.h>

#include "HelmetState.h"
#include "ServoController.h"
#include "LedController.h"

class HelmetController {
private:
    ServoController& servo;
    LedController& leftLed;
    LedController& rightLed;

    HelmetState state = HelmetState::UNKNOWN;

public:
    HelmetController(
        ServoController& servo,
        LedController& leftLed,
        LedController& rightLed
    );

    void begin();

    void execute(HelmetCommand command);

    HelmetState getState() const;
};