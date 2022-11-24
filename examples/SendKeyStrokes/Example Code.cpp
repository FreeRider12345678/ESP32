#include <Arduino.h>
#include <BleKeyboard.h>
#include <Key.h>
#include <KeyMatrix.h>
#include <KeyAction.h>
#include <KeyMap.h>
#include <Rotary.h>
#include <RotaryAction.h>

// Bluetooth Low Energy
BleKeyboard bleKeyboard;

// Rotary Encoders
Rotary RotaryLeft;
Rotary RotaryRight;
RotaryAction RotaryActionLeft = *new RotaryAction(bleKeyboard);
RotaryAction RotaryActionRight = *new RotaryAction(bleKeyboard);
int rotaryLeftPins[] = {12, 13, 14};  // Left Rotary Encoder
int rotaryRightPins[] = {26, 27, 25}; // Right Rotary Encoder

// Key Matrix
Key **key;
KeyMatrix Matrix;
byte cols[] = {15, 2, 0, 4};
byte rows[] = {5, 17, 16};
const int colCount = sizeof(cols) / sizeof(cols[0]);
const int rowCount = sizeof(rows) / sizeof(rows[0]);
KeyMap KeyConfigs = *new KeyMap(bleKeyboard, rowCount, colCount);

void initRotary()
{
  RotaryActionLeft.SetType(MOUSE);
  RotaryActionRight.SetType(VOLUME);
}
void initKeyMap()
{
  uint8_t press1[] = {KEY_LEFT_CTRL, uint8_t('c')};
  uint8_t release1[] = {KEY_LEFT_CTRL, uint8_t('v')};
  KeyConfigs.GetAction(0, 0).SetPressConfig(press1, 2);
  KeyConfigs.GetAction(0, 0).SetReleaseConfig(release1, 2);

  uint8_t release2[] = {KEY_BACKSPACE};
  KeyConfigs.GetAction(0, 3).SetReleaseConfig(release2, 1);

  uint8_t press3[] = {KEY_DOWN_ARROW};
  uint8_t hold3[] = {KEY_DELETE};
  uint8_t release3[] = {KEY_UP_ARROW};
  KeyConfigs.GetAction(2, 3).SetConfig(press3, 1, hold3, 1, release3, 1);
}

void setup()
{
  Serial.begin(9600);

  bleKeyboard.begin();

  RotaryLeft.Begin(rotaryLeftPins);
  RotaryRight.Begin(rotaryRightPins);

  key = Matrix.Begin(rows, rowCount, cols, colCount, 500, 0);

  initRotary();
  initKeyMap();
}

void loop()
{
  RotaryActionRight.Action(RotaryRight.readRotaryEncoder());
  RotaryActionLeft.Action(RotaryLeft.readRotaryEncoder());

  Matrix.readKeys();
  KeyConfigs.Action(key);
}
