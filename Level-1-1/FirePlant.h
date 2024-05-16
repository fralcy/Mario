#pragma once
#include "GameObject.h"

#define CELL_WIDTH 16
#define	CELL_HEIGHT 16

#define PLANT_SPEED	0.025f

#define ID_ANI_PLANT_HEAD 31000

class CFirePlant : public CGameObject
{
protected:
	float pathLength;
	float maxHeight;
	bool isHidden = true;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; }
	virtual int IsBlocking() { return 0; }

public:
	CFirePlant(float x, float y, float vineLength);// vine length in leaf number or half cells
};