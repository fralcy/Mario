#include "FirePlant.h"
#include "AssetIDs.h"
#include "PlayScene.h"
#include <cmath>
CFirePlant::CFirePlant(float x, float y, float vineLength):CGameObject::CGameObject(x,y)
{
	this->minHeight = y;
    this->maxHeight = y - CELL_HEIGHT - vineLength * CELL_HEIGHT / 2;
    startWaiting = 0;
    mx = my = 1000;
}
void CFirePlant::Render()
{
    //Get head animations
    int headAniId = 0;
    switch (state)
    {
    case STATE_AIM_LOWER_LEFT:
        headAniId = ID_ANI_AIM_LOWER_LEFT;
        break;
    case STATE_AIM_UPPER_LEFT:
        headAniId = ID_ANI_AIM_UPPER_LEFT;
        break;
    case STATE_AIM_UPPER_RIGHT:
        headAniId = ID_ANI_AIM_UPPER_RIGHT;
        break;
    case STATE_AIM_LOWER_RIGHT:
        headAniId = ID_ANI_AIM_LOWER_RIGHT;
        break;
    }
    //Render
    CAnimations::GetInstance()->Get(headAniId)->Render(x, y);
    CSprites::GetInstance()->Get(ID_SPRITE_PLANT_VINE)->Draw(x, y + CELL_HEIGHT);
}
void CFirePlant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	//Get Mario's Position
    float mx, my;
    CPlayScene* scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
	CMario* player = (CMario*)scene->GetPlayer();
    player->GetPosition(mx,my);
    //Aim
    if (mx <= x)
    {
        if (my < y)
            SetState(STATE_AIM_UPPER_LEFT);
        else
            SetState(STATE_AIM_LOWER_LEFT);
    }
    else
    {
        if (my < y)
            SetState(STATE_AIM_UPPER_RIGHT);
        else
            SetState(STATE_AIM_LOWER_RIGHT);
    }
    DebugOut(L"[INFO] %d %d %d\n", (mx < x) , (my > y), state);
    //Wait
    if (isWaiting)
    {
        if (GetTickCount64() - startWaiting > WAITING_TIME)
            isWaiting = false;
        return;
    }
    //Start
    if (vy == 0)
    {
        if (y >= minHeight && abs(x - mx) > SAFE_DISTANCE)
        {
            y = minHeight;
            vy = -PLANT_SPEED;
        }
        else if (y <= maxHeight)
        {
            y = maxHeight;
            vy = PLANT_SPEED;
        }
    }
    //Move
    else
    {
        y += vy * dt;
        //Stop
        if (y <= maxHeight)
        {
            vy = 0;
            isWaiting = true;
            startWaiting = GetTickCount64();
        }
        else if (y >= minHeight)
        {
            vy = 0;
            isWaiting = true;
            startWaiting = GetTickCount64();
        }
    }
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
	RenderBoundingBox();
}
void CFirePlant::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - (CELL_WIDTH / 2);
	top = y - (CELL_HEIGHT / 2);
	right = left + CELL_WIDTH;
	bottom = top + (CELL_HEIGHT * 2);
}