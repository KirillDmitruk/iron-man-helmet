#include "MotionController.h"

MotionController::MotionController(ServoController& servo)
    : servo(servo) {}


float MotionController::easeInOut(float t) const{
    return t * t * (3.0f - 2.0f * t);
}


void MotionController::initializePosition(
    int left,
    int right
) {
    currentLeft = left;
    currentRight = right;

    startLeft = left;
    startRight = right;

    targetLeft = left;
    targetRight = right;

    moving = false;
    initialized = true;
}


bool MotionController::moveTo(
    int left,
    int right,
    unsigned long durationMs
) {
    if (!initialized || moving || durationMs == 0) {
        return false;
    }

    if (left < 0 || left > 180 ||
        right < 0 || right > 180) {
        return false;
    }

    startLeft = currentLeft;
    startRight = currentRight;

    targetLeft = left;
    targetRight = right;

    duration = durationMs;
    startTime = millis();
    lastUpdate = startTime;

    moving = true;

    return true;
}


void MotionController::update() {
    if (!moving) {
        return;
    }

    unsigned long now = millis();
    unsigned long elapsed = now - startTime;

    if (now - lastUpdate < 20 && elapsed < duration) {
        return;
    }

    lastUpdate = now;

    float progress = (float)elapsed / duration;

    if (progress >= 1.0f) {
        progress = 1.0f;
    }

    float smoothProgress = easeInOut(progress);

    currentLeft = startLeft +
        (targetLeft - startLeft) * smoothProgress;

    currentRight = startRight +
        (targetRight - startRight) * smoothProgress;

    servo.setAngles(
        round(currentLeft),
        round(currentRight)
    );

    if (progress >= 1.0f) {
        moving = false;
    }
}


void MotionController::stop() {
    moving = false;

    // A physical servo may still be moving.
    initialized = false;
}


bool MotionController::isMoving() const {
    return moving;
}


bool MotionController::isInitialized() const {
    return initialized;
}