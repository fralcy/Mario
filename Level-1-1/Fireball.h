#pragma once
#include "GameObject.h"

#define FIREBALL_SIZE 8

#define FIREBALL_SPEED 0.05f

#define ID_ANI_FIREBALL 32000

class CFireball : public CGameObject
{
protected:
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; }
	virtual int IsBlocking() { return 0; }
public:
	CFireball(float x, float y, int dir);
};