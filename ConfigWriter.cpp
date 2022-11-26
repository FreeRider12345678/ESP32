#include <string>
#include <vector>
#include <ConfigWriter.h>

ConfigWriter::ConfigWriter()
{
}

void ConfigWriter::Tokenize(std::string const &str, const char delim, std::vector<std::string> &out)
{
	size_t start;
	size_t end = 0;

	while ((start = str.find_first_not_of(delim, end)) != std::string::npos)
	{
		end = str.find(delim, start);
		out.push_back(str.substr(start, end - start));
	}
}

void ConfigWriter::ClearConfigs(KeyMap &keyMap, std::vector<RotaryAction> &rotaryActions)
{
	for (size_t r = 0; r < keyMap.RowCount; r++)
	{
		for (size_t c = 0; c < keyMap.ColCount; c++)
		{
			keyMap.GetAction(r, c).ClearConfig();
		}
	}

	for (auto &rotary : rotaryActions)
	{
		rotary.Clear();
	}
}

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
void ConfigWriter::SetConfig(std::string configString, KeyMap &keyMap, std::vector<RotaryAction> &rotaryActions)
{
	// clear all configs
	ClearConfigs(keyMap, rotaryActions);

	// split configs
	const char delim = ';';
	std::vector<std::string> out;
	Tokenize(configString, delim, out);

	// loop through configs
	for (auto &config : out)
	{
		SetConfigElement(config, keyMap, rotaryActions);
	}
}

void ConfigWriter::SetConfigElement(std::string configElement, KeyMap &keyMap, std::vector<RotaryAction> &rotaryActions)
{
	// get name, row, col
	char type = configElement[0];	 // first character holds type
	int row = configElement[2] - 48; // 3rd character holds row number
	int col = configElement[4] - 48; // 5th character holds col number

	// get element
	std::string config = configElement.substr(6, configElement.length() - 6);

	// config rotary or key
	if (type == 'r')
	{
		// rotary
		RotaryType rotaryType = GetRotaryType(config);
		// RotaryAction &rotary = rotaryActions[col];
		// rotary.SetType(rotaryType);
		rotaryActions[col].SetType(rotaryType);
	}
	else if (type == 'k')
	{
		// key
		KeyAction &key = keyMap.GetAction(row, col);

		// split arrays
		const char delim = ',';
		std::vector<std::string> out;
		Tokenize(config, delim, out);

		// get configs
		int count;
		if (out[0] != "-")
		{
			uint8_t *press = GetKeyConfig(out[0], count);
			key.SetPressConfig(press, count);
		}

		if (out[1] != "-")
		{
			uint8_t *hold = GetKeyConfig(out[1], count);
			key.SetHoldConfig(hold, count);
		}
		if (out[2] != "-")
		{
			uint8_t *release = GetKeyConfig(out[2], count);
			key.SetReleaseConfig(release, count);
		}
	}
}

uint8_t *ConfigWriter::GetKeyConfig(std::string configElement, int &count)
{
	// split keys
	const char delim = '+';
	std::vector<std::string> keys;
	Tokenize(configElement, delim, keys);

	// Get key codes
	count = keys.size();
	uint8_t *arr = (uint8_t *)malloc(sizeof(uint8_t) * count);
	for (size_t i = 0; i < count; i++)
	{
		arr[i] = GetKeyCode(keys[i]);
	}

	return arr;
}

RotaryType ConfigWriter::GetRotaryType(std::string config)
{
	if (config == "mouse")
		return MOUSE;
	if (config == "volume")
		return VOLUME;
	return NOTYPE;
}

uint8_t ConfigWriter::GetKeyCode(std::string key)
{
	// special keys
	if (key == "ctrl")
		return KEY_LEFT_CTRL;
	if (key == "shift")
		return KEY_LEFT_SHIFT;
	if (key == "alt")
		return KEY_LEFT_ALT;
	if (key == "altgr")
		return KEY_RIGHT_ALT;
	if (key == "up")
		return KEY_UP_ARROW;
	if (key == "down")
		return KEY_DOWN_ARROW;
	if (key == "left")
		return KEY_LEFT_ARROW;
	if (key == "right")
		return KEY_RIGHT_ARROW;
	if (key == "back")
		return KEY_BACKSPACE;
	if (key == "tab")
		return KEY_TAB;
	if (key == "cr")
		return KEY_RETURN;
	if (key == "esc")
		return KEY_ESC;
	if (key == "ins")
		return KEY_INSERT;
	if (key == "del")
		return KEY_DELETE;
	if (key == "pageup")
		return KEY_PAGE_UP;
	if (key == "pagedown")
		return KEY_PAGE_DOWN;
	if (key == "home")
		return KEY_HOME;
	if (key == "end")
		return KEY_END;
	if (key == "caps")
		return KEY_CAPS_LOCK;
	if (key == "win")
		return KEY_LEFT_GUI;
	if (key == "f1")
		return KEY_F1;
	if (key == "f2")
		return KEY_F2;
	if (key == "f3")
		return KEY_F3;
	if (key == "f4")
		return KEY_F4;
	if (key == "f5")
		return KEY_F5;
	if (key == "f6")
		return KEY_F6;
	if (key == "f7")
		return KEY_F7;
	if (key == "f8")
		return KEY_F8;
	if (key == "f9")
		return KEY_F9;
	if (key == "f10")
		return KEY_F10;
	if (key == "f11")
		return KEY_F11;
	if (key == "f12")
		return KEY_F12;
	if (key == "f13")
		return KEY_F13;
	if (key == "f14")
		return KEY_F14;
	if (key == "f15")
		return KEY_F15;
	if (key == "f16")
		return KEY_F16;
	if (key == "f17")
		return KEY_F17;
	if (key == "f18")
		return KEY_F18;
	if (key == "f19")
		return KEY_F19;
	if (key == "f20")
		return KEY_F20;
	if (key == "f21")
		return KEY_F21;
	if (key == "f22")
		return KEY_F22;
	if (key == "f23")
		return KEY_F23;
	if (key == "f24")
		return KEY_F24;

	// delimiter characters
	if (key == "plus")
		return '+';
	if (key == "minus")
		return '-';
	if (key == "dot")
		return ',';
	if (key == "semicolon")
		return ';';
	if (key == "colon")
		return ':';

	// regular keys: 1-digit
	return key[0];
}
