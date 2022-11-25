#ifndef Keypadlib_CONFIGWRITER_H_
#define Keypadlib_CONFIGWRITER_H_

#include <string>
#include <vector>
#include <Arduino.h>

class ConfigWriter
{
public:
    ConfigWriter(BleKeyboard& bleKeyboard, KeyMap& keyMap, RotaryAction* rotaryActions);
    void SetConfig(std::string configString);
private:
    BleKeyboard& Ble;
    KeyMap& KeyMap;
    RotaryAction* RotaryActions;

    void Tokenize(std::string const& str, const char delim, std::vector<std::string>& out);
    void SetConfigElement(std::string configElement);
    uint8_t* GetKeyConfig(std::string configElement, int& count);
    RotaryType GetRotaryType(std::string config);
    uint8_t GetKeyCode(std::string key);
};

#endif