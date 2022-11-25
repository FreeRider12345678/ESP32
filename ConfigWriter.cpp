#include <string>
#include <vector>
#include <ConfigWriter.h>

ConfigWriter::ConfigWriter(BleKeyboard& bleKeyboard, KeyMap& keyMap, RotaryAction* rotaryActions) : Ble(bleKeyboard)
{
	KeyMap = keyMap;
	RotaryActions = rotaryActions;
}

void ConfigWriter::Tokenize(std::string const& str, const char delim, std::vector<std::string>& out)
{
	size_t start;
	size_t end = 0;

	while ((start = str.find_first_not_of(delim, end)) != std::string::npos)
	{
		end = str.find(delim, start);
		out.push_back(str.substr(start, end - start));
	}
}

void ConfigWriter::SetConfig(std::string configString)
{
	// configs have following syntax:
	// <typeid>.<row>.<col>:<config>;
	// <typeid> := r | k
	// <row> := 1-digit-number
	// <col> := 1-digit-number
	// <config> := <rotaryconfig> | <keyconfig>
	// <rotaryconfig> := mouse | volume
	// <keyconfig> := <pressconfig>,<holdconfig>,<releaseconfig>
	// <pressconfig> := <key>[+<key>]*
	// <holdconfig> := <key>[+<key>]*
	// <releaseconfig> := <key>[+<key>]*

	// split configs
	const char delim = ';';
	std::vector<std::string> out;
	Tokenize(configString, delim, out);

	// loop through configs
	for (auto& config : out)
	{
		SetConfig(config);
	}
}

void ConfigWriter::SetConfigElement(std::string configElement)
{
	// get name, row, col
	char type = configElement[0];	// first character holds type
	int row = a - configElement[2]; // 3rd character holds row number
	int col = a - configElement[4]; // 5th character holds col number

	// get element
	str config = configElement.substr(6, str.length() - 8);

	// config rotary or key
	if (type == 'r')
	{
		// rotary
		RotaryAction rotary = RotaryActions[col];
		RotaryType rotaryType = GetRotaryType(config);
		rotary.SetType(rotaryType);
	}
	else if (type == 'k')
	{
		// key
		KeyAction key = KeyMap.GetAction(row, col);

		// split arrays
		const char delim = ',';
		std::vector<std::string> out;
		Tokenize(configString, delim, out);

		// get configs
		int count;
		uint8_t* press = GetKeyConfig(out[0], count);
		key.SetPressConfig(press, count);

		uint8_t* hold = GetKeyConfig(out[1], count);
		key.SetHoldConfig(hold, count);

		uint8_t* release = GetKeyConfig(out[2], count);
		key.SetReleaseConfig(release, count);
	}
}

uint8_t* ConfigWriter::GetKeyConfig(std::string configElement, int& count)
{
	// split keys
	const char delim = '+';
	std::vector<std::string> keys;
	Tokenize(configString, delim, keys);

	// Get key codes
	count = keys.size();
	uint8_t* arr = (uint8_t*)malloc(sizeof(uint8_t) * keys.size());
	for (size_t i = 0; i < count; i++)
	{
		arr[i] = GetKeyCode(keys[i]);
	}

	return arr;
}

RotaryType ConfigWriter::GetRotaryType(std::string config)
{
	switch (config)
	{
	case "mouse":
		return MOUSE;
	case "volume":
		return VOLUME;
	default:
		return NOTYPE;
	}
}

uint8_t ConfigWriter::GetKeyCode(std::string key)
{
	switch (key)
	{
	case "ctrl":
		return KEY_LEFT_CTRL;
	case "shift":
		return KEY_LEFT_SHIFT;
	case "alt":
		return KEY_LEFT_ALT;
	case "altgr":
		return KEY_RIGHT_ALT;
	case "up":
		return KEY_UP_ARROW;
	case "down":
		return KEY_DOWN_ARROW;
	case "left":
		return KEY_LEFT_ARROW;
	case "right":
		return KEY_RIGHT_ARROW;
	case "back":
		return KEY_BACKSPACE;
	case "tab":
		return KEY_TAB;
	case "cr":
		return KEY_RETURN;
	case "esc":
		return KEY_ESC;
	case "ins":
		return KEY_INSERT;
	case "del":
		return KEY_DELETE;
	case "pageup":
		return KEY_PAGE_UP;
	case "pagedown":
		return KEY_PAGE_DOWN;
	case "home":
		return KEY_HOME;
	case "end":
		return KEY_END;
	case "caps":
		return KEY_CAPS_LOCK;
	case "win":
		return KEY_LEFT_GUI;
	case "f1":
		return KEY_F1;
	case "f2":
		return KEY_F2;
	case "f3":
		return KEY_F3;
	case "f4":
		return KEY_F4;
	case "f5":
		return KEY_F5;
	case "f6":
		return KEY_F6;
	case "f7":
		return KEY_F7;
	case "f8":
		return KEY_F8;
	case "f9":
		return KEY_F9;
	case "f10":
		return KEY_F10;
	case "f11":
		return KEY_F11;
	case "f12":
		return KEY_F12;
	case "f13":
		return KEY_F13;
	case "f14":
		return KEY_F14;
	case "f15":
		return KEY_F15;
	case "f16":
		return KEY_F16;
	case "f17":
		return KEY_F17;
	case "f18":
		return KEY_F18;
	case "f19":
		return KEY_F19;
	case "f20":
		return KEY_F20;
	case "f21":
		return KEY_F21;
	case "f22":
		return KEY_F22;
	case "f23":
		return KEY_F23;
	case "f24":
		return KEY_F24;
	}
	return 0;
}
