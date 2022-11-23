#include <KeyMap.h>

KeyMap::KeyMap(BleKeyboard &bleKeyboard, int rowCount, int colCount) : Ble(bleKeyboard)
{
    RowCount = rowCount;
    ColCount = colCount;

    KeyMappings = new KeyAction *[rowCount];
    for (int r = 0; r < rowCount; r++)
    {
        KeyMappings[r] = (KeyAction *)malloc(sizeof(KeyAction) * colCount);
        for (int c = 0; c < colCount; c++)
        {
            new (&(KeyMappings[r][c])) KeyAction(bleKeyboard);
        }
    }
}

KeyAction &KeyMap::GetAction(int row, int col)
{
    return KeyMappings[row][col];
}

void KeyMap::Action(Key **keys)
{
    for (int r = 0; r < RowCount; r++)
    {
        for (int c = 0; c < ColCount; c++)
        {
            if (keys[r][c].stateChanged)
            {
                GetAction(r, c).Action(keys[r][c].kstate);
            }
        }
    }
}
