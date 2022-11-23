#ifndef Keylib_KEYMAP_H_
#define Keylib_KEYMAP_H_

#include <Arduino.h>
#include <BleKeyboard.h>
#include <Key.h>
#include <KeyAction.h>

class KeyMap
{
public:
    KeyMap(BleKeyboard &bleKeyboard, int rowCount, int colcount);
    void Action(Key **keys);
    KeyAction &GetAction(int row, int col);

private:
    BleKeyboard &Ble;

    int RowCount = 0;
    int ColCount = 0;
    KeyAction **KeyMappings;
};

#endif