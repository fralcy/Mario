#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"


class CLine : public CGameObject {
protected:
	int spriteId;
	int length;
public:
	CLine(float x, float y, int length, int spriteId) : CGameObject(x, y) { this->length = length; this->spriteId = spriteId; }
	void Render() {
		CSprites* s = CSprites::GetInstance();
		for (int i = 0; i < length; i++) {
			s->Get(this->spriteId)->Draw(x + 16 * i, y);
		}
	}
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b) {}
	int IsBlocking() { return 0; }
};