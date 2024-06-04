#pragma once
#include "GameObject.h"

#define SWITCH_BLOCK_STATE_UNPRESSED 1
#define SWITCH_BLOCK_STATE_PRESSED 0
class CSwitchBlock : public CGameObject {
public:
	CSwitchBlock(float x, float y) :CGameObject(x, y) { state = SWITCH_BLOCK_STATE_UNPRESSED;}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsCollidable() { return 1; }
	int IsBlocking() { return 0; }
	void SwitchItem();
};