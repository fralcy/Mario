#pragma once
#include "GameObject.h"
#include "Pathfinder.h"

#define GRAVITY 0.002f
#define WALKING_SPEED 0.025f

#define WIDTH 16
#define HEIGHT 24
#define SHELL_HEIGHT 14

#define KOOPA_HIDE_TIME 4000
#define KOOPA_RECOVER_TIME 2000

#define STATE_WALKING 100
#define STATE_SHELL 200
#define STATE_RECOVER 300

#define ID_ANI_KOOPA_WALKING_LEFT 33100
#define ID_ANI_KOOPA_WALKING_RIGHT 33200
#define ID_ANI_KOOPA_SHELL 33300
#define ID_ANI_KOOPA_SPINNING_LEFT 33400
#define ID_ANI_KOOPA_SPINNING_RIGHT 33500
#define ID_ANI_KOOPA_RECOVER 33600

class CKoopa : public CGameObject
{
protected:
    int color;
    float ax;
    float ay;
    CPathfinder* pathfinder;
    ULONGLONG hide_start, recover_start;

    virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
    virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
    virtual void Render();

    virtual int IsCollidable() { return 1; };
    virtual int IsBlocking() { return 0; }
    virtual void OnNoCollision(DWORD dt);

    virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
    CKoopa(float x, float y, int color);
    virtual void SetState(int state);
};
