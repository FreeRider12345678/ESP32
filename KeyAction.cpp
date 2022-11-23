#include <KeyAction.h>

KeyAction::KeyAction(BleKeyboard &bleKeyboard) : Ble(bleKeyboard)
{
}

void KeyAction::SetPressConfig(uint8_t *pressConfig, int pressCount)
{
    PressConfig = (uint8_t *)malloc(sizeof(uint8_t) * pressCount);
    for (size_t i = 0; i < pressCount; i++)
    {
        PressConfig[i] = pressConfig[i];
    }

    PressCount = pressCount;
}
void KeyAction::SetHoldConfig(uint8_t *holdConfig, int holdCount)
{
    HoldConfig = (uint8_t *)malloc(sizeof(uint8_t) * holdCount);
    for (size_t i = 0; i < holdCount; i++)
    {
        HoldConfig[i] = holdConfig[i];
    }
    HoldCount = holdCount;
}
void KeyAction::SetReleaseConfig(uint8_t *releaseConfig, int releaseCount)
{
    ReleaseConfig = (uint8_t *)malloc(sizeof(uint8_t) * releaseCount);
    for (size_t i = 0; i < releaseCount; i++)
    {
        ReleaseConfig[i] = releaseConfig[i];
    }

    ReleaseCount = releaseCount;
}
void KeyAction::SetConfig(uint8_t *pressConfig, int pressCount, uint8_t *holdConfig, int holdCount, uint8_t *releaseConfig, int releaseCount)
{
    SetPressConfig(pressConfig, pressCount);
    SetHoldConfig(holdConfig, holdCount);
    SetReleaseConfig(releaseConfig, releaseCount);
}

void KeyAction::Action(KeyState state)
{
    switch (state)
    {
    case PRESSED:
        if (PressCount > 0)
        {
            DoAction(PressConfig, PressCount);
        }
        break;
    case HOLD:
        if (HoldCount > 0)
        {
            DoAction(HoldConfig, HoldCount);
        }
        break;
    case RELEASED:
        if (ReleaseCount > 0)
        {
            DoAction(ReleaseConfig, ReleaseCount);
        }
        break;
    }
}

void KeyAction::DoAction(uint8_t *config, int count)
{
    for (size_t i = 0; i < count; i++)
    {
        Ble.press(config[i]);
    }
    delay(100);
    Ble.releaseAll();
}