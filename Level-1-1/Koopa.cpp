#include "Koopa.h"
#include "PlayScene.h"
#include "Mysteryblock.h"
#include "Venus.h"
#include "Effect.h"

void CKoopa::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
    left = x - KOOPA_WIDTH / 2;
    right = left + KOOPA_WIDTH;
    if (state != KOOPA_STATE_WALKING)
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
CKoopa::CKoopa(float x, float y, int color, int type) : CGameObject(x, y)
{
    this->nx = -1;
    this->color = color;
    this->type = type;
    this->ax = 0;
    this->ay = KOOPA_GRAVITY;
    hide_start = recover_start = -1;

    pathfinder = new CPathfinder(x, y);
    LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
    scene->AddObj(pathfinder);

    SetState(KOOPA_STATE_WALKING);
}

void CKoopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
    //Get player
    LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
    CMario* player = (CMario*)scene->GetPlayer();
    //No gravity if player is holding this
    if (player->GetHoldObj() == this)
    {
        this->ay = 0;
    }
    else
    {
        this->ay = KOOPA_GRAVITY;
    }
    // Check if the pathfinder is falling off the platform
    if (state == KOOPA_STATE_WALKING && type == KOOPA_TYPE_NORMAL) if(pathfinder->GetVY() > 0 && vy == 0) // Pathfinder is falling
    {
        vx = -vx; // Turn Koopa back
        nx = -nx;
        pathfinder->SetPosition(x + KOOPA_WIDTH * nx * 0.75f, y);
        pathfinder->SetSpeed(vx, 0);
    }
    // Start recovering after hide for a while
    if (vx == 0)
    {
        if (state == KOOPA_STATE_SHELL || state == KOOPA_STATE_KNOCKED)
        {
            if (hide_start == -1)
                hide_start = GetTickCount64();
            else if (GetTickCount64() - hide_start > KOOPA_HIDE_TIME)
            {
                recover_start = GetTickCount64();
                SetState(KOOPA_STATE_RECOVER);
            }
        }
        else if (state == KOOPA_STATE_RECOVER)
        {
            if (GetTickCount64() - recover_start > KOOPA_RECOVER_TIME)
            {
                y = y - KOOPA_HEIGHT + KOOPA_SHELL_HEIGHT + 2;
                SetState(KOOPA_STATE_WALKING);
                //If player is holding this
                if (player->GetHoldObj() == this)
                {
                    player->GetDamage(); //Damage player
                    player->Drop(); //Leave player's hands
                }
            }
        }
    }
    else
    {
        hide_start = recover_start = -1;
    }
    //if koopa has wings and is on platform
    if (type == KOOPA_TYPE_WINGED && state == KOOPA_STATE_WALKING)
    {
        if (GetTickCount64() - fly_start > KOOPA_FLY_DELAY_TIME)
        {
            Fly();
        }
    }
    vy += ay * dt;
    vx += ax * dt;        

    CGameObject::Update(dt, coObjects);
    CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CKoopa::Render()
{
    int aniId = 0;
    if (color == KOOPA_COLOR_RED)
    {
        switch (state)
        {
        case KOOPA_STATE_WALKING:
            if (nx < 0) aniId = ID_ANI_KOOPA_WALKING_LEFT_RED;
            else aniId = ID_ANI_KOOPA_WALKING_RIGHT_RED;
            break;
        case KOOPA_STATE_SHELL:
            if (vx == 0) aniId = ID_ANI_KOOPA_SHELL_RED;
            else if (nx < 0) aniId = ID_ANI_KOOPA_SPINNING_LEFT_RED;
            else aniId = ID_ANI_KOOPA_SPINNING_RIGHT_RED;
            break;
        case KOOPA_STATE_RECOVER:
            aniId = ID_ANI_KOOPA_RECOVER_RED;
            break;
        case KOOPA_STATE_KNOCKED:
            if (vx == 0) aniId = ID_ANI_KOOPA_SHELL_RED;
            else if (nx < 0) aniId = ID_ANI_KOOPA_SPINNING_LEFT_RED;
            else aniId = ID_ANI_KOOPA_SPINNING_RIGHT_RED;
            break;
        }
    }
    else
    {
        switch (state)
        {
        case KOOPA_STATE_WALKING:
            if (type == KOOPA_TYPE_NORMAL)
            {
                if (nx < 0) aniId = ID_ANI_KOOPA_WALKING_LEFT_GREEN;
                else aniId = ID_ANI_KOOPA_WALKING_RIGHT_GREEN;
            }
            else
            {
                if (nx < 0) aniId = ID_ANI_PARAKOOPA_WALKING_LEFT_GREEN;
                else aniId = ID_ANI_PARAKOOPA_WALKING_RIGHT_GREEN;
            }
            break;
        case KOOPA_STATE_SHELL:
            if (vx == 0) aniId = ID_ANI_KOOPA_SHELL_GREEN;
            else if (nx < 0) aniId = ID_ANI_KOOPA_SPINNING_LEFT_GREEN;
            else aniId = ID_ANI_KOOPA_SPINNING_RIGHT_GREEN;
            break;
        case KOOPA_STATE_RECOVER:
            aniId = ID_ANI_KOOPA_RECOVER_GREEN;
            break;
        case KOOPA_STATE_KNOCKED:
            if (vx == 0) aniId = ID_ANI_KOOPA_SHELL_GREEN;
            else if (nx < 0) aniId = ID_ANI_KOOPA_SPINNING_LEFT_GREEN;
            else aniId = ID_ANI_KOOPA_SPINNING_RIGHT_GREEN;
            break;
        }
    }
    CAnimations::GetInstance()->Get(aniId)->Render(x, y);
    //RenderBoundingBox();
}

void CKoopa::OnNoCollision(DWORD dt)
{
    x += vx * dt;
    y += vy * dt;
}

void CKoopa::OnCollisionWith(LPCOLLISIONEVENT e)
{
    if (dynamic_cast<CMysteryBlock*>(e->obj))
        OnCollisionWithMysteryBlock(e);
    else if (dynamic_cast<CGoomba*>(e->obj))
        OnCollisionWithGoomba(e);
    else if (dynamic_cast<CVenus*>(e->obj))
        OnCollisionWithPlant(e);
    else if (dynamic_cast<CKoopa*>(e->obj))
        OnCollisionWithKoopa(e);
    else if (dynamic_cast<CBrick*>(e->obj))
        OnCollisionWithBrick(e);
    if (!e->obj->IsBlocking()) return;
    

    if (e->ny != 0)
    {
        vy = 0;
        if (isKnocking) 
        {
            vx = 0;
            isKnocking = false;
        }
    }
    else if (e->nx != 0)
    {
        nx = -nx;
		vx = -vx;
        pathfinder->SetSpeed(vx, 0);
        pathfinder->SetPosition(x + 8 * nx, y);
	}
}
void CKoopa::OnCollisionWithMysteryBlock(LPCOLLISIONEVENT e)
{
    if (state == KOOPA_STATE_WALKING || vx == 0) return;
    CMysteryBlock* mysteryblock = dynamic_cast<CMysteryBlock*>(e->obj);
    if (e->nx != 0 && mysteryblock->GetState() == MYSTERY_BLOCK_STATE_ACTIVE)
    {
        mysteryblock->SpawnItem((int) - e->nx);
    }
}
void CKoopa::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
    if (state == KOOPA_STATE_WALKING || vx == 0)  return;
    float x, y;
    e->obj->GetPosition(x, y);
    LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
    CEffect* hit = new CEffect(x, y, ID_SPRITE_HIT);
    scene->AddObj(hit);
    e->obj->Delete();
}
void CKoopa::OnCollisionWithPlant(LPCOLLISIONEVENT e)
{
    if (state == KOOPA_STATE_WALKING || vx == 0)  return;
    float x, y;
    e->obj->GetPosition(x, y);
    LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
    CEffect* hit = new CEffect(x, y, ID_SPRITE_HIT);
    scene->AddObj(hit);
    e->obj->Delete();
}
void CKoopa::OnCollisionWithKoopa(LPCOLLISIONEVENT e)
{
    if (state == KOOPA_STATE_WALKING || vx == 0)  return;
    float x, y;
    e->obj->GetPosition(x, y);
    LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
    CEffect* hit = new CEffect(x, y, ID_SPRITE_HIT);
    scene->AddObj(hit);
    e->obj->Delete();
}
void CKoopa::OnCollisionWithBrick(LPCOLLISIONEVENT e)
{
    if (e->nx != 0 && vx != 0 && state != KOOPA_STATE_WALKING && !isKnocking)
    {
        LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
        CBrick* brick = (CBrick*)e->obj;
        float x, y;
        brick->GetPosition(x, y);
        CEffect* broken = new CEffect(x, y, ID_SPRITE_BRICK_BROKEN);
        scene->AddObj(broken);
        brick->Delete();
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
        pathfinder->SetPosition(x + KOOPA_WIDTH * nx * 0.75f, y);
        break;
    case KOOPA_STATE_SHELL:
        vx = 0;
        break;
    case KOOPA_STATE_RECOVER:
        break;
    case KOOPA_STATE_KNOCKED:
        isKnocking = true;
        break;
    }
}
void CKoopa::Fly()
{
    fly_start = GetTickCount64();
    vx = (nx < 0) ? -KOOPA_FLYING_SPEED_X : KOOPA_FLYING_SPEED_X;
    vy = -KOOPA_FLYING_SPEED_Y;
}