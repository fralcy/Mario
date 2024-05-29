#include "Pathfinder.h"

void CPathfinder::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
    left = x - KOOPA_WIDTH / 2;
    top = y - KOOPA_HEIGHT / 2;
    right = left + KOOPA_WIDTH;
    bottom = top + KOOPA_HEIGHT;
}

void CPathfinder::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
    vy += ay * dt;
    vx += ax * dt;
    CGameObject::Update(dt, coObjects);
    CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CPathfinder::OnNoCollision(DWORD dt)
{
	x += vy * dt;
	y += vy * dt;
}

void CPathfinder::OnCollisionWith(LPCOLLISIONEVENT e)
{
    if (!e->obj->IsBlocking()) return;
    if (dynamic_cast<CPathfinder*>(e->obj)) return;

    if (e->ny != 0)
    {
        vy = 0;
    }
}

CPathfinder::CPathfinder(float x, float y): CGameObject(x,y)
{
    this->ax = 0;
    this->ay = KOOPA_GRAVITY;
}
