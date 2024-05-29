#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "AssetIDs.h"

#define EFFECT_EXISTING_TIME	100

class CEffect : public CGameObject {
protected:
	int spriteId;
	ULONGLONG timer_start = 0;
public:
	CEffect(float x, float y, int spriteId) : CGameObject(x, y) { 
		this->spriteId = spriteId;
		timer_start = GetTickCount64();
	}
	void Render() {
		CSprites* s = CSprites::GetInstance();
		s->Get(this->spriteId)->Draw(x, y);
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
		if (GetTickCount64() - timer_start > EFFECT_EXISTING_TIME)
			Delete();
		CGameObject::Update(dt, coObjects);
		CCollision::GetInstance()->Process(this, dt, coObjects);
	}
	void GetBoundingBox(float& l, float& t, float& r, float& b) {}
	int IsBlocking() { return 0; }
};