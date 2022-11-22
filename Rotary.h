#ifndef Rotarylib_ROTARY_H
#define Rotarylib_ROTARY_H

#include <Arduino.h>

typedef enum
{
    WAIT,
    DOWN,
    UP,
    CLICK,
} RotaryState;

typedef enum
{
    SWOPEN,
    SWCLOSE,
} ClickState;

class Rotary
{
public:
    Rotary();
    void Begin(int output[]);
    RotaryState readRotaryEncoder();

private:
    int *Output;
    int ALastState;

    void setupPinMode();
    ClickState clkState;
};

#endif