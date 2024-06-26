#pragma once
#include "Scene.h"
class CIntroKeyHandler : public CSceneKeyHandler
{
public:
	virtual void KeyState(BYTE* states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	CIntroKeyHandler(LPSCENE s) :CSceneKeyHandler(s) { type = 0; }
};