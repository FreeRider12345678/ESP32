#ifndef Rotarylib_ROTARYACTION_H
#define Rotarylib_ROTARYACTION_H

#include <Arduino.h>
#include <BleKeyboard.h>
#include <Rotary.h>

typedef enum
{
    NOTYPE,
    MOUSE,
    VOLUME,
} RotaryType;

class RotaryAction
{
public:
    RotaryAction(BleKeyboard &bleKeyboard);
    RotaryType GetType();
    void SetType(RotaryType type);
    void Clear();
    void Action(RotaryState state);

private:
    RotaryType Type;
    BleKeyboard &Ble;

    void MoveDown();
    void MoveUp();
    void Click();
};

#endif