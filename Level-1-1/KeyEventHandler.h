#pragma once

#include <Windows.h>

/*
	Abstract class to define keyboard event handlers
*/
class CKeyEventHandler
{
public:
	bool isEnabled = true;
	virtual void KeyState(BYTE* state) = 0;
	virtual void OnKeyDown(int KeyCode) = 0;
	virtual void OnKeyUp(int KeyCode) = 0;
	void ToggleEnabled() { isEnabled = !isEnabled; }
};

typedef CKeyEventHandler* LPKEYEVENTHANDLER;
