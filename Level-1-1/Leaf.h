#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_LEAF 9000
#define LEAF_WIDTH 16
#define LEAF_BBOX_WIDTH 16
#define LEAF_BBOX_HEIGHT 16
#define LEAF_AMPLITUDE 20
#define LEAF_FREQUENCY 0.0005f
#define LEAF_FALL_SPEED 0.03f

class CLeaf : public CGameObject {
protected:
	float x0 = x;
	bool isspawning;
	float maxheight = y - 48;
	ULONGLONG time;
	ULONGLONG starttime;
public:
	CLeaf(float x, float y);
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual int IsBlocking() { return 0; }
};