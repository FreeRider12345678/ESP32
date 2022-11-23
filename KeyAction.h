#ifndef Keylib_KEYACTION_H_
#define Keylib_KEYACTION_H_

#include <Arduino.h>
#include <BleKeyboard.h>
#include <Key.h>

class KeyAction
{
public:
    KeyAction(BleKeyboard &bleKeyboard);
    void SetPressConfig(uint8_t *pressConfig, int pressCount);
    void SetHoldConfig(uint8_t *holdConfig, int holdCount);
    void SetReleaseConfig(uint8_t *releaseConfig, int releaseCount);
    void SetConfig(uint8_t *pressConfig, int pressCount, uint8_t *holdConfig, int holdCount, uint8_t *releaseConfig, int releaseCount);
    void Action(KeyState state);

private:
    BleKeyboard &Ble;

    uint8_t *PressConfig;
    uint8_t *HoldConfig;
    uint8_t *ReleaseConfig;

    int PressCount = 0;
    int HoldCount = 0;
    int ReleaseCount = 0;

    void DoAction(uint8_t *config, int count);
    void CopyArray(uint8_t *source, int count, uint8_t *target);
};

#endif