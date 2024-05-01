#pragma once
#include "GameObject.h"

#define SHROOM_GRAVITY 0.002f
#define SHROOM_WALKING_SPEED 0.05f


#define SHROOM_BBOX_WIDTH 16
#define SHROOM_BBOX_HEIGHT 14
#define SHROOM_BBOX_HEIGHT_DIE 7

#define SHROOM_DIE_TIMEOUT 500

#define SHROOM_STATE_WALKING 100
#define SHROOM_STATE_DIE 200

#define ID_ANI_SHROOM_WALKING 6000
#define ID_ANI_SHROOM_DIE 6001

class CShroom : public CGameObject
{
protected:
	float ax;
	float ay;

	ULONGLONG die_start;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CShroom(float x, float y);
	virtual void SetState(int state);
};