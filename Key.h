#ifndef Keypadlib_KEY_H_
#define Keypadlib_KEY_H_

#include <Arduino.h>

#define OPEN LOW
#define CLOSED HIGH

typedef unsigned int uint;
typedef enum
{
    IDLE,
    PRESSED,
    HOLD,
    RELEASED
} KeyState;

const char NO_KEY = '\0';

class Key
{
public:
    KeyState kstate;
    boolean stateChanged;
    unsigned long holdTimer;

    // methods
    Key();
    Key(uint holdTime);
    void key_update(boolean isPressed);

private:
    uint HoldTime;

    void transitionTo(KeyState nextState);
};

#endif