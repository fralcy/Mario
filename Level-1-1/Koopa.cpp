#include "Koopa.h"
#include "PlayScene.h"
void CKoopa::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
    left = x - WIDTH / 2;
    right = left + WIDTH;
    if (state == STATE_SHELL || state == STATE_RECOVER)
    {
        top = y - SHELL_HEIGHT / 2;
        bottom = top + SHELL_HEIGHT;
    }
    else
    {
        top = y - HEIGHT / 2;
        bottom = top + HEIGHT;
    }
}
CKoopa::CKoopa(float x, float y, int color) : CGameObject(x, y)
{
    this->nx = (- 1);
    this->color = color;
    this->ax = 0;
    this->ay = GRAVITY;
    die_start = -1;

    pathfinder = new CPathfinder(x, y);
    LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
    scene->AddObj(pathfinder);

    SetState(STATE_WALKING);
}

void CKoopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
    // Check if the pathfinder is falling off the platform
    if (state == STATE_WALKING) if(pathfinder->GetVY() > 0 && vy == 0) // Pathfinder is falling
    {
        vx = -vx; // Turn Koopa back
        nx = -nx;
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
    int aniId = 0;
    switch (state)
    {
    case STATE_WALKING:
        if (nx < 0) aniId = ID_ANI_KOOPA_WALKING_LEFT;
        else aniId = ID_ANI_KOOPA_WALKING_RIGHT;
        break;
    case STATE_SHELL:
        if (vx == 0) aniId = ID_ANI_KOOPA_SHELL;
        else if (nx < 0) aniId = ID_ANI_KOOPA_SPINNING_LEFT;
        else aniId = ID_ANI_KOOPA_SPINNING_RIGHT;
        break;
    case STATE_RECOVER:
        aniId = ID_ANI_KOOPA_RECOVER;
        break;
    }
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
        nx = -nx;
		vx = -vx;
	}
}

void CKoopa::SetState(int state)
{
    CGameObject::SetState(state);
    switch (state)
    {
    case STATE_WALKING:
        vx = WALKING_SPEED * nx;
        pathfinder->SetSpeed(vx, 0);
        pathfinder->SetPosition(x + 16 * nx, y);
        break;
    case STATE_SHELL:
        vx = 0;
        break;
    }
}
