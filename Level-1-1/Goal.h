#pragma once

#include "GameObject.h"
#define GOAL_ITEM_SHROOM 1
#define GOAL_ITEM_FLOWER 2
#define GOAL_ITEM_STAR 3

#define ID_ANI_SHROOM	6000
#define ID_ANI_FLOWER	6100
#define ID_ANI_STAR		6200

#define GOAL_CHANGE_DELAY 500
class CGoal : public CGameObject {
protected:
	int item = 0;
	ULONGLONG wait_start = 0;
public:
	CGoal(float x, float y) :CGameObject(x, y) {};
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
	int GetItem() const { return item; }
};