#pragma once
#include "Scene.h"
class CMapKeyHandler: public CSceneKeyHandler
{
public:
	virtual void KeyState(BYTE* states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	CMapKeyHandler(LPSCENE s) :CSceneKeyHandler(s) { type = 1; }
};