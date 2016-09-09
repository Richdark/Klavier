#pragma once

#include <Windows.h>
#include <vector>
#include <QMessageBox>
#include <string>
#include "KlavierUtils.h"

class KeyboardHook
{
private:
	static KeyboardHook instance;
	static HHOOK hook;
	static KBDLLHOOKSTRUCT eventInfo;
		
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
	static bool ignoreBackspace;
	static bool upper;
	static const std::vector<DWORD>* currentChain;
	static unsigned currentChainIndex;

	KeyboardHook();
	~KeyboardHook();
	static LRESULT __stdcall hookCallback(int nCode, WPARAM wParam, LPARAM lParam);
	void set();
	void release();

public:
	static KeyboardHook& getInstance();
	static void setHotkey(DWORD new_hotkey);
	//void run();
};
