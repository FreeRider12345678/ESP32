#include <Rotary.h>

Rotary::Rotary()
{
}

void Rotary::setupPinMode()
{
    pinMode(Output[0], INPUT_PULLUP);
    pinMode(Output[1], INPUT_PULLUP);
    pinMode(Output[2], INPUT_PULLUP);
}

void Rotary::Begin(int output[])
{
    Output = output;
    setupPinMode();

    ALastState = digitalRead(Output[0]);
}

RotaryState Rotary::readRotaryEncoder()
{
    int aState = digitalRead(Output[0]);
    int bState = digitalRead(Output[1]);
    int swState = digitalRead(Output[2]);

    RotaryState retVal = WAIT;

    if (aState != ALastState)
    {
        if (bState != ALastState)
        {
            retVal = DOWN;
        }
        else
        {
            retVal = UP;
        }
    }
    ALastState = aState;

    if (swState == LOW)
    {
        delay(500);
        retVal = CLICK;
    }

    return retVal;
}