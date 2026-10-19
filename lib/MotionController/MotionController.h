#pragma once

#include <Arduino.h>
#include "ServoController.h"

class MotionController {
private:
    ServoController& servo;

    float startLeft = 0;
    float startRight = 0;

    float currentLeft = 0;
    float currentRight = 0;

    float targetLeft = 0;
    float targetRight = 0;

    unsigned long startTime = 0;
    unsigned long duration = 0;
    unsigned long lastUpdate = 0;

    bool moving = false;
    bool initialized = false;

    float easeInOut(float progress) const;

public:
    explicit MotionController(ServoController& servo);

    void initializePosition(int left, int right);

    bool moveTo(
        int left,
        int right,
        unsigned long durationMs
    );

    void update();

    void stop();

    bool isMoving() const;
    bool isInitialized() const;
};