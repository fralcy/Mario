#pragma once
#include "GameObject.h"

#define CELL_WIDTH 16
#define	CELL_HEIGHT 16

#define PLANT_SPEED	0.025f

#define STATE_AIM_LOWER_LEFT 1
#define STATE_AIM_UPPER_LEFT 2
#define STATE_AIM_UPPER_RIGHT 3
#define STATE_AIM_LOWER_RIGHT 4

#define ID_ANI_AIM_LOWER_LEFT 31000
#define ID_ANI_AIM_UPPER_LEFT 31100
#define ID_ANI_AIM_UPPER_RIGHT 31200
#define ID_ANI_AIM_LOWER_RIGHT 31300

#define WAITING_TIME 1000

#define SAFE_DISTANCE 24
class CFirePlant : public CGameObject
{
protected:
	float minHeight;
	float maxHeight;
	bool isWaiting = false;
	float mx, my;
	ULONGLONG startWaiting;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; }
	virtual int IsBlocking() { return 0; }
	void Aim();

public:
	CFirePlant(float x, float y, float vineLength);// vine length in leaf number or half cells
};