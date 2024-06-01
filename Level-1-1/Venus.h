#pragma once
#include "GameObject.h"

#define CELL_WIDTH 16
#define	CELL_HEIGHT 16

#define PLANT_SPEED	0.02f

#define STATE_AIM_LOWER_LEFT 1
#define STATE_AIM_UPPER_LEFT 2
#define STATE_AIM_UPPER_RIGHT 3
#define STATE_AIM_LOWER_RIGHT 4

#define STATE_NORMAL 0

#define ID_ANI_AIM_LOWER_LEFT_RED 31110
#define ID_ANI_AIM_UPPER_LEFT_RED 31120
#define ID_ANI_AIM_UPPER_RIGHT_RED 31130
#define ID_ANI_AIM_LOWER_RIGHT_RED 31140

#define ID_ANI_NORMAL 31200
#define ID_ANI_AIM_LOWER_LEFT_GREEN 31210
#define ID_ANI_AIM_UPPER_LEFT_GREEN 31220
#define ID_ANI_AIM_UPPER_RIGHT_GREEN 31230
#define ID_ANI_AIM_LOWER_RIGHT_GREEN 31240

#define WAITING_TIME 2000

#define SAFE_DISTANCE 24
#define DANGEROUS_DISTANCE (SAFE_DISTANCE*4)

#define VENUS_HEAD_RED 1
#define VENUS_HEAD_GREEN 2
class CVenus : public CGameObject
{
protected:
	float minHeight;
	float maxHeight;
	bool isWaiting = true;
	float mx, my;
	bool canFire;
	int headColor;
	ULONGLONG startWaiting;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);
public:
	CVenus(float x, float y, float vineLength, bool canFire, int headColor);// vine length in leaf number or half cells
};