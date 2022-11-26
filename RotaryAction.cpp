#include <RotaryAction.h>
RotaryAction::RotaryAction(BleKeyboard &bleKeyboard) : Ble(bleKeyboard)
{
}
void RotaryAction::Clear()
{
    Type = NOTYPE;
}

void RotaryAction::SetType(RotaryType type)
{
    Type = type;
}

RotaryType RotaryAction::GetType()
{
    return Type;
}

void RotaryAction::Action(RotaryState state)
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

void RotaryAction::MoveDown()
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

void RotaryAction::MoveUp()
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

void RotaryAction::Click()
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