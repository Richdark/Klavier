#pragma once

#include "windows.h"
#include <string>
#include <unordered_map>

namespace KlavierUtils
{
	const DWORD LowerAGrave = 0xE0;
	const DWORD LowerACircumflex = 0xE2;
	const DWORD LowerAsh = 0xE6;
	const DWORD LowerCedilla = 0xE7;
	const DWORD LowerEAcute = 0xE9;
	const DWORD LowerEGrave = 0xE8;
	const DWORD LowerECircumflex = 0xEA;
	const DWORD LowerEUmlaut = 0xEB;
	const DWORD LowerICircumflex = 0xEE;
	const DWORD LowerIUmlaut = 0xEF;
	const DWORD LowerOCircumflex = 0xF4;
	const DWORD LowerEthel = 0x153;
	const DWORD LowerUGrave = 0xF9;
	const DWORD LowerUCircumflex = 0xFB;
	const DWORD LowerUUmlaut = 0xFC;
	const DWORD LowerYUmlaut = 0xFF;
	const DWORD UpperAGrave = 0xC0;
	const DWORD UpperACircumflex = 0xC2;
	const DWORD UpperAsh = 0xC6;
	const DWORD UpperCedilla = 0xC7;
	const DWORD UpperEAcute = 0xC9;
	const DWORD UpperEGrave = 0xC8;
	const DWORD UpperECircumflex = 0xCA;
	const DWORD UpperEUmlaut = 0xCB;
	const DWORD UpperICircumflex = 0xCE;
	const DWORD UpperIUmlaut = 0xCF;
	const DWORD UpperOCircumflex = 0xD4;
	const DWORD UpperEthel = 0x152;
	const DWORD UpperUGrave = 0xD9;
	const DWORD UpperUCircumflex = 0xDB;
	const DWORD UpperUUmlaut = 0xDC;
	const DWORD UpperYUmlaut = 0x178;

	enum class AccentInput { KKey, InsKey };

	struct Settings
	{
		AccentInput input;
		UINT hotkey_modifiers;
		UINT hotkey;
	};

	const std::unordered_map<std::string, UINT> HotkeyCodes
	{
		{ "A", 0x41 },
		{ "B", 0x42 },
		{ "C", 0x43 },
		{ "D", 0x44 },
		{ "E", 0x45 },
		{ "F", 0x46 },
		{ "G", 0x47 },
		{ "H", 0x48 },
		{ "I", 0x49 },
		{ "J", 0x4A },
		{ "K", 0x4B },
		{ "L", 0x4C },
		{ "M", 0x4D },
		{ "N", 0x4E },
		{ "O", 0x4F },
		{ "P", 0x50 },
		{ "Q", 0x51 },
		{ "R", 0x52 },
		{ "S", 0x53 },
		{ "T", 0x54 },
		{ "U", 0x55 },
		{ "V", 0x56 },
		{ "W", 0x57 },
		{ "X", 0x58 },
		{ "Y", 0x59 },
		{ "Z", 0x5A },
		{ "Tab", VK_TAB },
		{ "Space", VK_SPACE },
		{ "Insert", VK_INSERT },
		{ "Delete", VK_DELETE },
		{ "Home", VK_HOME },
		{ "End", VK_END },
		{ "Page up", VK_PRIOR },
		{ "Page down", VK_NEXT }
	};

	const std::unordered_map<UINT, std::string> HotkeyLabels
	{
		{ 0x41, "A" },
		{ 0x42, "B" },
		{ 0x43, "C" },
		{ 0x44, "D" },
		{ 0x45, "E" },
		{ 0x46, "F" },
		{ 0x47, "G" },
		{ 0x48, "H" },
		{ 0x49, "I" },
		{ 0x4A, "J" },
		{ 0x4B, "K" },
		{ 0x4C, "L" },
		{ 0x4D, "M" },
		{ 0x4E, "N" },
		{ 0x4F, "O" },
		{ 0x50, "P" },
		{ 0x51, "Q" },
		{ 0x52, "R" },
		{ 0x53, "S" },
		{ 0x54, "T" },
		{ 0x55, "U" },
		{ 0x56, "V" },
		{ 0x57, "W" },
		{ 0x58, "X" },
		{ 0x59, "Y" },
		{ 0x5A, "Z" },
		{ VK_TAB, "Tab" },
		{ VK_SPACE, "Space" },
		{ VK_INSERT, "Insert" },
		{ VK_DELETE, "Delete" },
		{ VK_HOME, "Home" },
		{ VK_END, "End" },
		{ VK_PRIOR, "Page up" },
		{ VK_NEXT, "Page down" }
	};
}