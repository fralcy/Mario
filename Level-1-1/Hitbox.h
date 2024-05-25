#pragma once

#include "GameObject.h"

#define HITBOX_WIDTH 20
#define HITBOX_HEIGHT 10
#define	HITBOX_TIMEOUT 100

class CHitbox: public CGameObject {
protected:
	ULONGLONG time_start;
public:
	CHitbox(float x, float y) : CGameObject(x, y) { time_start = GetTickCount64(); };
	void Render() {
		RenderBoundingBox();
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
		if (GetTickCount64() - time_start > HITBOX_TIMEOUT) Delete();
		CGameObject::Update(dt, coObjects);
		CCollision::GetInstance()->Process(this, dt, coObjects);
	}
	void GetBoundingBox(float& l, float& t, float& r, float& b) {
		l = x - HITBOX_WIDTH / 2;
		t = y - HITBOX_HEIGHT / 2;
		r = l + HITBOX_WIDTH;
		b = t + HITBOX_HEIGHT;
	}
	int IsBlocking() { return 0; }
};