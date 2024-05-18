#pragma once
#include "GameObject.h"

#define FIREBALL_SIZE 8

#define FIREBALL_SPEED 0.075f

#define DIR_LOWER_LEFT 1
#define DIR_LEFT 2
#define DIR_UPPER_LEFT 3
#define DIR_UPPER_RIGHT 4
#define DIR__RIGHT 5
#define DIR_LOWER_RIGHT 6

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