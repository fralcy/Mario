#pragma once

#include <Windows.h>

/*
	Abstract class to define keyboard event handlers
*/
class CKeyEventHandler
{
public:
	bool isEnabled = true;
	int type;
	virtual void KeyState(BYTE* state) = 0;
	virtual void OnKeyDown(int KeyCode) = 0;
	virtual void OnKeyUp(int KeyCode) = 0;
	bool IsEnabled() { return isEnabled; }
	void ToggleEnabled() { isEnabled = !isEnabled; }
	int GetType() { return type; }
};

typedef CKeyEventHandler* LPKEYEVENTHANDLER;
