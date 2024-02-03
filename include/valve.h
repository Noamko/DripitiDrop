#pragma once
#include <Arduino.h>
class Valve {
    public:
        Valve(uint8_t pin);
        void open(int seconds);
        void reset();
        void close();
    private:
        uint8_t pin;
        uint8_t state;
        esp_timer_handle_t timer;
};