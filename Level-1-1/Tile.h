#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"


class CTile : public CGameObject {
protected:
	int spriteId;
public:
	CTile(float x, float y, int spriteId) : CGameObject(x, y) { this->spriteId = spriteId; }
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b) {}
	int IsBlocking() { return 0; }
};