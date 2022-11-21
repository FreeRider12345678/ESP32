#include <KeyMatrix.h>

Key **KeyMatrix::Begin(byte inputPinDef[], int inputCount, byte outputPinDef[], int outputCount, int SetHoldTime, int SetScanDelay)
{
    inputPins = inputPinDef;
    rowCount = inputCount;

    outputPins = outputPinDef;
    colCount = outputCount;

    holdTime = SetHoldTime;
    scanDelay = SetScanDelay;

    InitPins();
    InitKeys();

    return key;
}

void KeyMatrix::InitKeys()
{
    key = new Key *[rowCount];
    for (int r = 0; r < rowCount; r++)
    {
        key[r] = new Key[colCount];
        for (int c = 0; c < colCount; c++)
        {
            key[r][c] = *new Key(holdTime);
        }
    }
}

void KeyMatrix::InitPins()
{
    for (int i = 0; i < rowCount; ++i)
    {
        pinMode(inputPins[i], INPUT_PULLDOWN);
    }

    for (int i = 0; i < colCount; ++i)
    {
        pinMode(outputPins[i], OUTPUT);
    }
}

void KeyMatrix::readKeys()
{
    for (int c = 0; c < colCount; c++)
    {
        digitalWrite(outputPins[c], HIGH);
        for (int r = 0; r < rowCount; r++)
        {
            bool isPressed = digitalRead(inputPins[r]) == HIGH;
            key[r][c].key_update(isPressed);
            delay(scanDelay);
        }
        digitalWrite(outputPins[c], LOW);
    }
}
