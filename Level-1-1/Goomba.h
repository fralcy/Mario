#pragma once
#include "GameObject.h"

#define GOOMBA_GRAVITY 0.002f
#define GOOMBA_WALKING_SPEED 0.05f
#define PARAGOOMBA_HOPPING_SPEED 0.15f
#define PARAGOOMBA_FLYING_SPEED 0.35f

#define GOOMBA_BBOX_WIDTH 16
#define GOOMBA_BBOX_HEIGHT 14
#define GOOMBA_BBOX_HEIGHT_DIE 7

#define GOOMBA_DIE_TIMEOUT 500
#define PARAGOOMBA_HOP_DELAY 750
#define PARAGOOMBA_FLY_DELAY 1250

#define GOOMBA_TYPE_NORMAL 0
#define GOOMBA_TYPE_WINGED 1

#define GOOMBA_STATE_WALKING 100
#define GOOMBA_STATE_STOMPED 200
#define GOOMBA_STATE_WINGED 300

#define ID_ANI_GOOMBA_WALKING 5000
#define ID_ANI_GOOMBA_STOMPED 5001
#define ID_ANI_PARAGOOMBA_WALKING 5002
#define ID_ANI_PARAGOOMBA_WALING_2 5003
#define ID_ANI_PARAGOOMBA_FLYING 5004
#define ID_ANI_PARAGOOMBA_STOMPED 5005

class CGoomba : public CGameObject
{
protected:
	float ax;				
	float ay; 
	int type;
	int hop_count;
	bool canFly = false;
	ULONGLONG die_start, fly_start;

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	
	float AdjustY();
	void Fly();
	void ChangeDirection();
public: 	
	CGoomba(float x, float y, int type);
	virtual void SetState(int state);
	int GetType() { return type; }
};