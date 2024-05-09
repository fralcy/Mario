#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_MYSTERY_BLOCK 7000
#define ID_ANI_MYSTERY_BLOCK_DIE 7001

#define MYSTERY_BLOCK_WIDTH 16
#define MYSTERY_BLOCK_BBOX_WIDTH 16
#define MYSTERY_BLOCK_BBOX_HEIGHT 16

#define MYSTERY_BLOCK_STATE_ACTIVE 700
#define MYSTERY_BLOCK_STATE_DIE 701

class CMysteryBlock : public CGameObject {
protected:
	int type;
public:
	CMysteryBlock(float x, float y, int type) : CGameObject(x, y) { this->type = type; this->state = MYSTERY_BLOCK_STATE_ACTIVE; }
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 1; }
	int GetType() { return type; }
	float GetX() const { return x; }
	float GetY() const { return y; }
};