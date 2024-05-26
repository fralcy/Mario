#pragma once

#include "GameObject.h"
#include "Goomba.h"
#include "FirePlant.h"
#include "Koopa.h"
#include "Mysteryblock.h"

#define HITBOX_WIDTH 1
#define HITBOX_HEIGHT 10
#define	HITBOX_TIMEOUT 150
#define HITBOX_SPEED 0.1f

class CHitbox: public CGameObject {
protected:
	ULONGLONG time_start;
public:
	CHitbox(float x, float y) : CGameObject(x, y) { time_start = GetTickCount64(); };
	void Render() {
		RenderBoundingBox();
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b) {
		l = x - HITBOX_WIDTH / 2;
		t = y - HITBOX_HEIGHT / 2;
		r = l + HITBOX_WIDTH;
		b = t + HITBOX_HEIGHT;
	}
	int IsCollidable() { return 1; }
	int IsBlocking() { return 0; }

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	void OnCollisionWithMysteryBlock(LPCOLLISIONEVENT e);
	void OnCollisionWithFirePlant(LPCOLLISIONEVENT e);
};