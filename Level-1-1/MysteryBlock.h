#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_MYSTERY_BLOCK 10000
#define MYSTERY_BLOCK_WIDTH 16
#define MYSTERY_BLOCK_BBOX_WIDTH 16
#define MYSTERY_BLOCK_BBOX_HEIGHT 16

class CMysteryBlock : public CGameObject {
public:
	CMysteryBlock(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};