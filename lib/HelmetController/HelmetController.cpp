#include "HelmetController.h"

HelmetController::HelmetController(
    ServoController& servo,
    LedController& leftLed,
    LedController& rightLed
)
    : servo(servo),
      leftLed(leftLed),
      rightLed(rightLed) {}


void HelmetController::begin() {
    leftLed.off();
    rightLed.off();

    state = HelmetState::UNKNOWN;
}


void HelmetController::execute(HelmetCommand command) {

    switch (command) {

        case HelmetCommand::OPEN:
            if (state == HelmetState::OPEN) {
                return;
            }

            servo.openMask();

            leftLed.on();
            rightLed.on();

            state = HelmetState::OPEN;
            break;

        case HelmetCommand::CLOSE:
            if (state == HelmetState::CLOSED) {
                return;
            }

            servo.closeMask();

            leftLed.off();
            rightLed.off();

            state = HelmetState::CLOSED;
            break;

        case HelmetCommand::TOGGLE:
            // UNKNOWN intentionally requires explicit OPEN/CLOSE.
            if (state == HelmetState::OPEN) {
                execute(HelmetCommand::CLOSE);
            }
            else if (state == HelmetState::CLOSED) {
                execute(HelmetCommand::OPEN);
            }
            break;
    }
}


HelmetState HelmetController::getState() const {
    return state;
}