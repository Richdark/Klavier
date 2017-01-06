#include "include/KeyboardHook.h"

KeyboardHook KeyboardHook::instance;
HHOOK KeyboardHook::hook;
KBDLLHOOKSTRUCT KeyboardHook::eventInfo;

using std::vector;
namespace KU = KlavierUtils;

const vector<DWORD> KeyboardHook::lowerAChain{ 0x61, KU::LowerAGrave, KU::LowerACircumflex, KU::LowerAsh };
const vector<DWORD> KeyboardHook::lowerCChain{ 0x63, KU::LowerCedilla };
const vector<DWORD> KeyboardHook::lowerEChain{ 0x65, KU::LowerEAcute, KU::LowerEGrave, KU::LowerECircumflex, KU::LowerEUmlaut };
const vector<DWORD> KeyboardHook::lowerIChain{ 0x69, KU::LowerICircumflex, KU::LowerIUmlaut };
const vector<DWORD> KeyboardHook::lowerOChain{ 0x6F, KU::LowerOCircumflex, KU::LowerEthel };
const vector<DWORD> KeyboardHook::lowerUChain{ 0x75, KU::LowerUGrave, KU::LowerUCircumflex, KU::LowerUUmlaut };
const vector<DWORD> KeyboardHook::lowerYChain{ 0x79, KU::LowerYUmlaut };
const vector<DWORD> KeyboardHook::upperAChain{ 0x41, KU::UpperAGrave, KU::UpperACircumflex, KU::UpperAsh };
const vector<DWORD> KeyboardHook::upperCChain{ 0x43, KU::UpperCedilla };
const vector<DWORD> KeyboardHook::upperEChain{ 0x45, KU::UpperEAcute, KU::UpperEGrave, KU::UpperECircumflex, KU::UpperEUmlaut };
const vector<DWORD> KeyboardHook::upperIChain{ 0x49, KU::UpperICircumflex, KU::UpperIUmlaut };
const vector<DWORD> KeyboardHook::upperOChain{ 0x4F, KU::UpperOCircumflex, KU::UpperEthel };
const vector<DWORD> KeyboardHook::upperUChain{ 0x55, KU::UpperUGrave, KU::UpperUCircumflex, KU::UpperUUmlaut };
const vector<DWORD> KeyboardHook::upperYChain{ 0x59, KU::UpperYUmlaut };

// true when hook is set
bool KeyboardHook::active = false;

// ID of window that will receive hotkey messages
HWND KeyboardHook::winId = NULL;

// code of a previously pressed key
DWORD KeyboardHook::prevCode = 0x00;

// hotkey code for switching accents
DWORD KeyboardHook::hotkey = VK_INSERT;

// hotkey modifiers for switching Klavier active/inactive state
UINT KeyboardHook::activeSwitchHotkeyModifiers = 0;

// hotkey for switching Klavier active/inactive state
UINT KeyboardHook::activeSwitchHotkey = 0;

// true when backspace was sent by an application to replace a character's accent with a next one
bool KeyboardHook::ignoreBackspace = false;

// true when shift was pressed (left or right)
bool KeyboardHook::upper = false;

// character currently being modified
const vector<DWORD>* KeyboardHook::currentChain = NULL;

// current accent index
unsigned KeyboardHook::currentChainIndex = 0;

KeyboardHook::KeyboardHook()
{
	//KeyboardHook::set();
}

KeyboardHook::~KeyboardHook()
{
	KeyboardHook::release();
	KeyboardHook::unregisterActiveSwitchHotkey();
}

LRESULT KeyboardHook::hookCallback(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode >= 0)
	{
		if (wParam == WM_KEYDOWN)
		{
			KeyboardHook::eventInfo = *((KBDLLHOOKSTRUCT*)lParam);

			// "k" key pressed
			if (KeyboardHook::eventInfo.vkCode == KeyboardHook::hotkey)
			{
				KeyboardHook::currentChainIndex++;

				// change accent
				if (KeyboardHook::prevCode == 0x41 ||
					KeyboardHook::prevCode == 0x43 ||
					KeyboardHook::prevCode == 0x45 ||
					KeyboardHook::prevCode == 0x49 ||
					KeyboardHook::prevCode == 0x4F ||
					KeyboardHook::prevCode == 0x55 ||
					KeyboardHook::prevCode == 0x59 ||
					KeyboardHook::prevCode == KeyboardHook::hotkey)
				{
					// remove previous character
					INPUT delInputArray;
					KEYBDINPUT delKeyInput;

					delKeyInput.wVk = VK_BACK;
					delKeyInput.dwFlags = 0;
					delInputArray.type = INPUT_KEYBOARD;
					delInputArray.ki = delKeyInput;

					// send new character
					INPUT inputArray;
					KEYBDINPUT keyInput;

					keyInput.wVk = 0;
					keyInput.wScan = (*KeyboardHook::currentChain)[KeyboardHook::currentChainIndex % (*KeyboardHook::currentChain).size()];
					keyInput.dwFlags = KEYEVENTF_UNICODE;
					inputArray.type = INPUT_KEYBOARD;
					inputArray.ki = keyInput;

					KeyboardHook::ignoreBackspace = true;
					SendInput(1, &delInputArray, sizeof(delInputArray));

					KeyboardHook::ignoreBackspace = false;
					SendInput(1, &inputArray, sizeof(inputArray));

					return 1;
				}
			}

			// "shift" key was pressed
			else if (KeyboardHook::eventInfo.vkCode == VK_SHIFT ||
				KeyboardHook::eventInfo.vkCode == VK_LSHIFT ||
				KeyboardHook::eventInfo.vkCode == VK_RSHIFT)
			{
				KeyboardHook::upper = true;
			}

			// some key that can have an accent was pressed
			else if (KeyboardHook::eventInfo.vkCode == 0x41 ||
				KeyboardHook::eventInfo.vkCode == 0x43 ||
				KeyboardHook::eventInfo.vkCode == 0x45 ||
				KeyboardHook::eventInfo.vkCode == 0x49 ||
				KeyboardHook::eventInfo.vkCode == 0x4F ||
				KeyboardHook::eventInfo.vkCode == 0x55 ||
				KeyboardHook::eventInfo.vkCode == 0x59 ||
				KeyboardHook::eventInfo.vkCode == KeyboardHook::hotkey)
			{
				KeyboardHook::currentChainIndex = 0;
				KeyboardHook::prevCode = KeyboardHook::eventInfo.vkCode;

				// "A" key was pressed
				if (KeyboardHook::eventInfo.vkCode == 0x41)
				{
					if (KeyboardHook::upper)
					{
						KeyboardHook::currentChain = &KeyboardHook::upperAChain;
					}
					else
					{
						KeyboardHook::currentChain = &KeyboardHook::lowerAChain;
					}
				}

				// "C" key was pressed
				else if (KeyboardHook::eventInfo.vkCode == 0x43)
				{
					if (KeyboardHook::upper)
					{
						KeyboardHook::currentChain = &KeyboardHook::upperCChain;
					}
					else
					{
						KeyboardHook::currentChain = &KeyboardHook::lowerCChain;
					}
				}

				// "E" key was pressed
				else if (KeyboardHook::eventInfo.vkCode == 0x45)
				{
					if (KeyboardHook::upper)
					{
						KeyboardHook::currentChain = &KeyboardHook::upperEChain;
					}
					else
					{
						KeyboardHook::currentChain = &KeyboardHook::lowerEChain;
					}
				}

				// "I" key was pressed
				else if (KeyboardHook::eventInfo.vkCode == 0x49)
				{
					if (KeyboardHook::upper)
					{
						KeyboardHook::currentChain = &KeyboardHook::upperIChain;
					}
					else
					{
						KeyboardHook::currentChain = &KeyboardHook::lowerIChain;
					}
				}

				// "O" key was pressed
				else if (KeyboardHook::eventInfo.vkCode == 0x4F)
				{
					if (KeyboardHook::upper)
					{
						KeyboardHook::currentChain = &KeyboardHook::upperOChain;
					}
					else
					{
						KeyboardHook::currentChain = &KeyboardHook::lowerOChain;
					}
				}

				// "U" key was pressed
				else if (KeyboardHook::eventInfo.vkCode == 0x55)
				{
					if (KeyboardHook::upper)
					{
						KeyboardHook::currentChain = &KeyboardHook::upperUChain;
					}
					else
					{
						KeyboardHook::currentChain = &KeyboardHook::lowerUChain;
					}
				}

				// "Y" key was pressed
				else if (KeyboardHook::eventInfo.vkCode == 0x59)
				{
					if (KeyboardHook::upper)
					{
						KeyboardHook::currentChain = &KeyboardHook::upperYChain;
					}
					else
					{
						KeyboardHook::currentChain = &KeyboardHook::lowerYChain;
					}
				}

				KeyboardHook::upper = false;
			}

			// any other user-pressed key
			else if ((KeyboardHook::eventInfo.vkCode != VK_BACK || !(KeyboardHook::ignoreBackspace)) && KeyboardHook::eventInfo.vkCode != VK_PACKET)
			{
				KeyboardHook::currentChain = NULL;
				KeyboardHook::currentChainIndex = 0;
				KeyboardHook::prevCode = KeyboardHook::eventInfo.vkCode;

				KeyboardHook::upper = false;
			}
		}
	}

	return CallNextHookEx(KeyboardHook::hook, nCode, wParam, lParam);
}

// set Klavier active (listen for hotkey)
void KeyboardHook::set()
{
	KeyboardHook::hook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardHook::hookCallback, NULL, 0);
	KeyboardHook::active = true;
}

// set Klavier inactive
void KeyboardHook::release()
{
	UnhookWindowsHookEx(KeyboardHook::hook);
	KeyboardHook::active = false;
}

// set hotkey for accent modification
void KeyboardHook::setHotkey(DWORD new_hotkey)
{
	KeyboardHook::hotkey = new_hotkey;
}

// get Klavier active status
bool KeyboardHook::isActive()
{
	return KeyboardHook::active;
}

// set hotkey for switching Klavier on/off and register it
void KeyboardHook::setActiveSwitchHotkey(const KlavierUtils::Settings& settings, HWND window_id)
{
	KeyboardHook::activeSwitchHotkeyModifiers = settings.hotkey_modifiers;
	KeyboardHook::activeSwitchHotkey = settings.hotkey;
	KeyboardHook::winId = window_id;

	KeyboardHook::registerActiveSwitchHotkey();
}

// register hotkey for switching Klavier on/off
bool KeyboardHook::registerActiveSwitchHotkey()
{
	KeyboardHook::unregisterActiveSwitchHotkey();

	return RegisterHotKey(KeyboardHook::winId, 1, KeyboardHook::activeSwitchHotkeyModifiers, KeyboardHook::activeSwitchHotkey);
}

// unregister hotkey for switching Klavier on/off
bool KeyboardHook::unregisterActiveSwitchHotkey()
{
	return UnregisterHotKey(KeyboardHook::winId, 1);
}

// switch Klavier active status
bool KeyboardHook::switchActive()
{
	if (KeyboardHook::active)
	{
		KeyboardHook::release();

		return false;
	}
	else
	{
		KeyboardHook::set();

		return true;
	}
}

//void KeyboardHook::run()
//{
//	MSG hookMessage;
//
//	while (GetMessage(&hookMessage, NULL, 0, 0))
//	{
//		//
//	}
//}
