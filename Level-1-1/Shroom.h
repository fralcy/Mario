#pragma once
#include "GameObject.h"

#define SHROOM_GRAVITY 0.002f
#define SHROOM_WALKING_SPEED 0.05f

#define SHROOM_BBOX_WIDTH 16
#define SHROOM_BBOX_HEIGHT 14

#define ID_ANI_SHROOM_RED 6000
#define ID_ANI_SHROOM_GREEN 6001

#define SHROOM_TYPE_RED	1
#define SHROOM_TYPE_GREEN 2

class CShroom : public CGameObject
{
protected:
	float ax;
	float ay;
	bool isspawning;
	float maxheight = y - 16;
	int type;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CShroom(float x, float y, int dir, int type);
	int GetType() { return type; }
};