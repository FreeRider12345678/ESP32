#ifndef Keypadlib_CONFIGWRITER_H_
#define Keypadlib_CONFIGWRITER_H_

#include <string>
#include <vector>
#include <Arduino.h>
#include <BleKeyboard.h>
#include <RotaryAction.h>
#include <KeyMap.h>

class ConfigWriter
{
public:
    ConfigWriter();
    void SetConfig(std::string configString, KeyMap &keyMap, std::vector<RotaryAction> &rotaryActions);

private:
    void Tokenize(std::string const &str, const char delim, std::vector<std::string> &out);
    void ClearConfigs(KeyMap &keyMap, std::vector<RotaryAction> &rotaryActions);
    void SetConfigElement(std::string configElement, KeyMap &keyMap, std::vector<RotaryAction> &rotaryActions);
    uint8_t *GetKeyConfig(std::string configElement, int &count);
    RotaryType GetRotaryType(std::string config);
    uint8_t GetKeyCode(std::string key);
};

#endif