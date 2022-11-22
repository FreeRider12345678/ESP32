#ifndef Rotarylib_ROTARYMAPPING_H
#define Rotarylib_ROTARYMAPPING_H

#include <Arduino.h>
#include <BleKeyboard.h>
#include <Rotary.h>

typedef enum
{
    NOTYPE,
    MOUSE,
    VOLUME,
} RotaryType;

class RotaryMapping
{
public:
    RotaryMapping(BleKeyboard &bleKeyboard);
    void SetType(RotaryType type);
    void Action(RotaryState state);

private:
    RotaryType Type;
    BleKeyboard &Ble;

    void MoveDown();
    void MoveUp();
    void Click();
};

#endif