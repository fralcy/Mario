#include "Koopa.h"
#include "PlayScene.h"
void CKoopa::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
    left = x - KOOPA_WIDTH / 2;
    right = left + KOOPA_WIDTH;
    if (state == KOOPA_STATE_SHELL || state == KOOPA_STATE_RECOVER)
    {
        top = y - KOOPA_SHELL_HEIGHT / 2;
        bottom = top + KOOPA_SHELL_HEIGHT;
    }
    else
    {
        top = y - KOOPA_HEIGHT / 2;
        bottom = top + KOOPA_HEIGHT;
    }
}
CKoopa::CKoopa(float x, float y, int color) : CGameObject(x, y)
{
    this->nx = -1;
    this->color = color;
    this->ax = 0;
    this->ay = GRAVITY;
    hide_start = recover_start = -1;

    pathfinder = new CPathfinder(x, y);
    LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
    scene->AddObj(pathfinder);

    SetState(KOOPA_STATE_WALKING);
}

void CKoopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
    // Check if the pathfinder is falling off the platform
    if (state == KOOPA_STATE_WALKING) if(pathfinder->GetVY() > 0 && vy == 0) // Pathfinder is falling
    {
        vx = -vx; // Turn Koopa back
        nx = -nx;
        pathfinder->SetPosition(x + (vx > 0 ? 16 : -16), y);
        pathfinder->SetSpeed(vx, 0);
    }
    // Start recovering after hide for a while
    if (vx == 0)
    {
        if (state == KOOPA_STATE_SHELL)
        {
            if (hide_start == -1)
                hide_start = GetTickCount64();
            else if (GetTickCount64() - hide_start > KOOPA_HIDE_TIME)
            {
                recover_start = GetTickCount64();
                SetState(KOOPA_STATE_RECOVER);
            }
        }
        else
        {
            if (GetTickCount64() - recover_start > KOOPA_RECOVER_TIME)
            {
                y = y - KOOPA_HEIGHT + KOOPA_SHELL_HEIGHT + 2;
                SetState(KOOPA_STATE_WALKING);
            }
        }
    }
    else
    {
        hide_start = recover_start = -1;
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
    case KOOPA_STATE_WALKING:
        if (nx < 0) aniId = ID_ANI_KOOPA_WALKING_LEFT;
        else aniId = ID_ANI_KOOPA_WALKING_RIGHT;
        break;
    case KOOPA_STATE_SHELL:
        if (vx == 0) aniId = ID_ANI_KOOPA_SHELL;
        else if (nx < 0) aniId = ID_ANI_KOOPA_SPINNING_LEFT;
        else aniId = ID_ANI_KOOPA_SPINNING_RIGHT;
        break;
    case KOOPA_STATE_RECOVER:
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
    case KOOPA_STATE_WALKING:
        vx = KOOPA_WALKING_SPEED * nx;
        pathfinder->SetSpeed(vx, 0);
        pathfinder->SetPosition(x + 16 * nx, y);
        break;
    case KOOPA_STATE_SHELL:
        vx = 0;
        break;
    case KOOPA_STATE_RECOVER:
        break;
    }
}
