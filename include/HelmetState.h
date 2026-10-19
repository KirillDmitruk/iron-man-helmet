#pragma once

enum class HelmetState {
    UNKNOWN,
    CLOSED,
    OPENING,
    OPEN,
    CLOSING,
    STOPPED,
    FAULT
};

enum class HelmetCommand {
    INITIALIZE_CLOSED,
    OPEN,
    CLOSE,
    TOGGLE,
    STOP
};