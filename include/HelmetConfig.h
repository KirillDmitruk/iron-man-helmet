#pragma once

#include <Arduino.h>

namespace HelmetConfig {

    // Servo pins
    constexpr uint8_t LEFT_SERVO_PIN = 9;
    constexpr uint8_t RIGHT_SERVO_PIN = 10;

    // LED pins
    constexpr uint8_t LEFT_LED_PIN = 6;
    constexpr uint8_t RIGHT_LED_PIN = 7;

    // Input
    constexpr uint8_t BUTTON_PIN = 2;

    // Servo positions
    constexpr int LEFT_OPEN_ANGLE = 0;
    constexpr int LEFT_CLOSED_ANGLE = 180;

    constexpr int RIGHT_OPEN_ANGLE = 180;
    constexpr int RIGHT_CLOSED_ANGLE = 0;

    // Timing
    constexpr unsigned long DEBOUNCE_MS = 50;

    // Serial
    constexpr unsigned long SERIAL_BAUD = 115200;
    
    // Motion settings
    constexpr unsigned long MOTION_DURATION_MS = 1200;
    constexpr unsigned long MOTION_UPDATE_MS = 20;
}