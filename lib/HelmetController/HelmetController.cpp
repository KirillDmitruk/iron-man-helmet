#include "HelmetController.h"
#include "HelmetConfig.h"

HelmetController::HelmetController(
    MotionController& motion,
    LedController& leftLed,
    LedController& rightLed
)
    : motion(motion),
      leftLed(leftLed),
      rightLed(rightLed) {}


void HelmetController::begin() {
    leftLed.off();
    rightLed.off();

    state = HelmetState::UNKNOWN;
}


void HelmetController::update() {
    motion.update();

    if (motion.isMoving()) {
        return;
    }

    if (state == HelmetState::OPENING) {
        state = HelmetState::OPEN;

        leftLed.on();
        rightLed.on();
    }
    else if (state == HelmetState::CLOSING) {
        state = HelmetState::CLOSED;

        leftLed.off();
        rightLed.off();
    }
}


bool HelmetController::execute(HelmetCommand command) {

    if (command == HelmetCommand::STOP) {
        motion.stop();
        state = HelmetState::STOPPED;
        return true;
    }

    if (command == HelmetCommand::INITIALIZE_CLOSED) {
        if (motion.isMoving()) {
            return false;
        }

        motion.initializePosition(
            HelmetConfig::LEFT_CLOSED_ANGLE,
            HelmetConfig::RIGHT_CLOSED_ANGLE
        );

        state = HelmetState::CLOSED;

        leftLed.off();
        rightLed.off();

        return true;
    }

    if (!motion.isInitialized()) {
        return false;
    }

    if (motion.isMoving()) {
        return false;
    }

    if (command == HelmetCommand::TOGGLE) {
        if (state == HelmetState::OPEN) {
            command = HelmetCommand::CLOSE;
        }
        else if (state == HelmetState::CLOSED) {
            command = HelmetCommand::OPEN;
        }
        else {
            return false;
        }
    }

    switch (command) {

        case HelmetCommand::OPEN:
            if (state == HelmetState::OPEN) {
                return true;
            }

            if (state != HelmetState::CLOSED) {
                return false;
            }

            if (!motion.moveTo(
                HelmetConfig::LEFT_OPEN_ANGLE,
                HelmetConfig::RIGHT_OPEN_ANGLE,
                HelmetConfig::MOTION_DURATION_MS
            )) {
                return false;
            }

            state = HelmetState::OPENING;
            return true;


        case HelmetCommand::CLOSE:
            if (state == HelmetState::CLOSED) {
                return true;
            }

            if (state != HelmetState::OPEN) {
                return false;
            }

            if (!motion.moveTo(
                HelmetConfig::LEFT_CLOSED_ANGLE,
                HelmetConfig::RIGHT_CLOSED_ANGLE,
                HelmetConfig::MOTION_DURATION_MS
            )) {
                return false;
            }

            state = HelmetState::CLOSING;
            return true;

        default:
            return false;
    }
}


HelmetState HelmetController::getState() const {
    return state;
}