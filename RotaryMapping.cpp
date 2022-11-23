#include <RotaryMapping.h>
RotaryMapping::RotaryMapping(BleKeyboard &bleKeyboard) : Ble(bleKeyboard)
{
}
void RotaryMapping::SetType(RotaryType type)
{
    Type = type;
}

void RotaryMapping::Action(RotaryState state)
{
    switch (state)
    {
    case DOWN:
        MoveDown();
        break;
    case UP:
        MoveUp();
        break;
    case CLICK:
        Click();
        break;
    }
}

void RotaryMapping::MoveDown()
{
    switch (Type)
    {
    case VOLUME: /* Media Volume */
        Ble.write(KEY_MEDIA_VOLUME_DOWN);
        break;
    case MOUSE: // Mouse Wheel
        Ble.move(0, 0, -1, 0);
        break;
    }
}

void RotaryMapping::MoveUp()
{
    switch (Type)
    {
    case VOLUME: /* Media Volume */
        Ble.write(KEY_MEDIA_VOLUME_UP);
        break;
    case MOUSE: // Mouse Wheel
        Ble.move(0, 0, +1, 0);
        break;
    }
}

void RotaryMapping::Click()
{
    switch (Type)
    {
    case VOLUME: /* Media Volume */
        Ble.write(KEY_MEDIA_MUTE);
        break;
    case MOUSE: // Mouse Wheel
        Ble.press(KEY_DELETE);
        delay(100);
        Ble.releaseAll();
                // code für Maus-Rad
    default:
        break;
    }
}