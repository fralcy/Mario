#pragma once
#include "GameObject.h"
#define GRAVITY 0.002f
#define PATHFINDER_SPEED 0.025f

#define KOOPA_WIDTH 16
#define KOOPA_HEIGHT 24

class CPathfinder : public CGameObject
{
protected:
    float ax;
    float ay;

    virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
    virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
    virtual void Render() { /*RenderBoundingBox();*/ }

    virtual int IsCollidable() { return 1; };
    virtual int IsBlocking() { return 0; }
    virtual void OnNoCollision(DWORD dt);

    virtual void OnCollisionWith(LPCOLLISIONEVENT e);
public:
    CPathfinder(float x, float y);
};
