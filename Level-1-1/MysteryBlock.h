#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_MYSTERY_BLOCK 7000
#define ID_ANI_MYSTERY_BLOCK_DIE 7001

#define MYSTERY_BLOCK_WIDTH 16
#define MYSTERY_BLOCK_BBOX_WIDTH 16
#define MYSTERY_BLOCK_BBOX_HEIGHT 16

#define MYSTERY_BLOCK_STATE_ACTIVE 1
#define MYSTERY_BLOCK_STATE_DIE 0

class CMysteryBlock : public CGameObject {
protected:
	int type;
public:
	CMysteryBlock(float x, float y, int type, int state);
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 1; }
	int GetType() const { return type; }
	float GetX() const { return x; }
	float GetY() const { return y; }
};