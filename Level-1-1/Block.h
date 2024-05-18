#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"


class CBlock : public CGameObject {
protected:
	int spriteId;
public:
	CBlock(float x, float y, int spriteId) : CGameObject(x, y) { this->spriteId = spriteId; }
	void Render() {
		CSprites* s = CSprites::GetInstance();
		s->Get(this->spriteId)->Draw(x, y);
	}
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b) {
		l = x - static_cast<float>(16) / 2;
		t = y - static_cast<float>(16) / 2;
		r = l + 16;
		b = t + 16;
	}
};