#pragma once
#include "GameObject.h"

#define FIREBALL_SIZE 8

#define FIREBALL_SPEED 0.075f

#define DIR_HEAVY_LOWER_LEFT 1
#define DIR_LIGHT_LOWER_LEFT 2
#define DIR_LIGHT_UPPER_LEFT 3
#define DIR_HEAVY_UPPER_LEFT 4
#define DIR_HEAVY_UPPER_RIGHT 5
#define DIR_LIGHT_UPPER_RIGHT 6
#define DIR_LIGHT_LOWER_RIGHT 7
#define DIR_HEAVY_LOWER_RIGHT 8

#define ID_ANI_FIREBALL 32000

#define FIREBALL_TIMEOUT 5000
class CFireball : public CGameObject
{
protected:
	ULONGLONG start;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsBlocking() { return 0; }
public:
	CFireball(float x, float y, int dir);
};