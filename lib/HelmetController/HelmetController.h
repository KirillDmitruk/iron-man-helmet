#pragma once

#include <Arduino.h>

#include "HelmetState.h"
#include "MotionController.h"
#include "LedController.h"

class HelmetController {
private:
    MotionController& motion;
    LedController& leftLed;
    LedController& rightLed;

    HelmetState state = HelmetState::UNKNOWN;

public:
    HelmetController(
        MotionController& motion,
        LedController& leftLed,
        LedController& rightLed
    );

    void begin();
    void update();

    bool execute(HelmetCommand command);

    HelmetState getState() const;
};