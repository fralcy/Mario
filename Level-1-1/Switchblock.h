#pragma once
#include "GameObject.h"

#define SWITCH_BLOCK_STATE_UNPRESSED 1
#define SWITCH_BLOCK_STATE_PRESSED 0

#define SWITCH_TIME 5000
class CSwitchBlock : public CGameObject {
	vector<LPGAMEOBJECT> objects;
	vector<LPGAMEOBJECT> objects_2;
	bool isSwitching = false;
	ULONGLONG switch_start = 0;
public:
	CSwitchBlock(float x, float y);
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsCollidable() { return 1; }
	int IsBlocking() { return 0; }
	void SwitchObjects();
};