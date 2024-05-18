#include "Koopa.h"
#include "PlayScene.h"
void CKoopa::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
    left = x - WIDTH / 2;
    top = y - HEIGHT / 2;
    right = left + WIDTH;
    bottom = top + HEIGHT;
}
CKoopa::CKoopa(float x, float y, int color) : CGameObject(x, y)
{
    this->color = color;
    this->ax = 0;
    this->ay = GRAVITY;
    die_start = -1;
    // Create a pathfinder object ahead of the Koopa
    pathfinder = new CPathfinder(x - WIDTH, y);
    LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
    scene->AddObj(pathfinder);

    SetState(STATE_WALKING_LEFT);
}

void CKoopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
    // Check if the pathfinder is falling off the platform
    if (pathfinder->GetVY() > 0) // Pathfinder is falling
    {
        vx = -vx; // Turn Koopa back
        pathfinder->SetPosition(x + (vx > 0 ? 16 : -16), y);
        pathfinder->SetSpeed(vx, 0);
    }

    vy += ay * dt;
    vx += ax * dt;

    CGameObject::Update(dt, coObjects);
    CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CKoopa::Render()
{
    int aniId = ID_ANI_KOOPA_WALKING_LEFT;
    if (vx > 0) aniId = ID_ANI_KOOPA_WALKING_RIGHT;
    CAnimations::GetInstance()->Get(aniId)->Render(x, y);
    RenderBoundingBox();
}

void CKoopa::OnNoCollision(DWORD dt)
{
    x += vx * dt;
    y += vy * dt;
}

void CKoopa::OnCollisionWith(LPCOLLISIONEVENT e)
{
    if (!e->obj->IsBlocking()) return;
    if (dynamic_cast<CKoopa*>(e->obj)) return;

    if (e->ny != 0)
    {
        vy = 0;
    }
    else if (e->nx != 0)
    {
		vx = -vx;
	}
}

void CKoopa::SetState(int state)
{
    CGameObject::SetState(state);
    switch (state)
    {
    case STATE_WALKING_LEFT:
        vx = -WALKING_SPEED;
        pathfinder->SetSpeed(vx, 0);
        pathfinder->SetPosition(x - 16, y);
        break;
    case STATE_WALKING_RIGHT:
        vx = WALKING_SPEED;
        pathfinder->SetSpeed(vx, 0);
        pathfinder->SetPosition(x + 16, y);
        break;
    }
}
