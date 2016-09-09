#pragma once

#include "windows.h"

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
	};
}