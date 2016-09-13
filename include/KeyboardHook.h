#pragma once

#include <Windows.h>
#include <vector>
#include "KlavierUtils.h"

class KeyboardHook
{
private:
	static KeyboardHook instance;
	static bool active;
	static HHOOK hook;
	static KBDLLHOOKSTRUCT eventInfo;
	static HWND winId;
	
	static const std::vector<DWORD> lowerAChain;
	static const std::vector<DWORD> lowerCChain;
	static const std::vector<DWORD> lowerEChain;
	static const std::vector<DWORD> lowerIChain;
	static const std::vector<DWORD> lowerOChain;
	static const std::vector<DWORD> lowerUChain;
	static const std::vector<DWORD> lowerYChain;
	static const std::vector<DWORD> upperAChain;
	static const std::vector<DWORD> upperCChain;
	static const std::vector<DWORD> upperEChain;
	static const std::vector<DWORD> upperIChain;
	static const std::vector<DWORD> upperOChain;
	static const std::vector<DWORD> upperUChain;
	static const std::vector<DWORD> upperYChain;

	static DWORD prevCode;
	static DWORD hotkey;
	static UINT activeSwitchHotkeyModifiers;
	static UINT activeSwitchHotkey;
	static bool ignoreBackspace;
	static bool upper;
	static const std::vector<DWORD>* currentChain;
	static unsigned currentChainIndex;

	KeyboardHook();
	~KeyboardHook();
	static LRESULT __stdcall hookCallback(int nCode, WPARAM wParam, LPARAM lParam);
	static bool registerActiveSwitchHotkey();
	static bool unregisterActiveSwitchHotkey();
	static void set();
	static void release();

public:
	static void setHotkey(DWORD new_hotkey);
	static void setActiveSwitchHotkey(const KlavierUtils::Settings& settings, HWND window);
	static const char * switchActive();
	//void run();
};
