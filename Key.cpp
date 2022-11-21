#include <Key.h>

// constructor
Key::Key()
{
    kstate = IDLE;
    stateChanged = false;
    HoldTime = 500;
}
Key::Key(uint holdTime)
{
    kstate = IDLE;
    stateChanged = false;
    HoldTime = holdTime;
}

void Key::transitionTo(KeyState nextState)
{
    kstate = nextState;
    stateChanged = true;
}

void Key::key_update(boolean isPressed)
{
    stateChanged = false;

    switch (kstate)
    {
    case IDLE:
        if (isPressed)
        {
            transitionTo(PRESSED);
            holdTimer = millis();
        } // Get ready for next HOLD state.
        break;
    case PRESSED:
        if (!isPressed) // or for a key to be RELEASED.
            transitionTo(RELEASED);
        else if ((millis() - holdTimer) > HoldTime) // Waiting for a key HOLD...
            transitionTo(HOLD);
        break;
    case HOLD:
        if (!isPressed)
            transitionTo(RELEASED);
        else if ((millis() - holdTimer) > HoldTime)
            transitionTo(HOLD);
        break;
    case RELEASED:
        transitionTo(IDLE);
        break;
    }
}
