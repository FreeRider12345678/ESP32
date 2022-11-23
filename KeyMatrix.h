#ifndef Keypadlib_KEYMATRIX_H_
#define Keypadlib_KEYMATRIX_H_

#include <Arduino.h>
#include <Key.h>

class KeyMatrix
{
public:
    Key **Begin(byte inputPinDef[], int inputCount, byte outputPinDef[], int outputCount, int SetHoldTime, int SetScanDelay);

    void readKeys();

private:
    byte *inputPins;
    byte *outputPins;
    int rowCount = 0;
    int colCount = 0;
    Key **key;

    int holdTime;
    int scanDelay;

    void InitKeys();
    void InitPins();
};

#endif