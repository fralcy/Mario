#include "Venus.h"
#include "AssetIDs.h"
#include "PlayScene.h"
#include <cmath>
#include "Fireball.h"
CVenus::CVenus(float x, float y, float vineLength, bool canFire, int headColor):CGameObject::CGameObject(x,y)
{
	this->minHeight = y;
    this->maxHeight = y - 16 - vineLength * 8;
    startWaiting = GetTickCount64();
    mx = my = 0;
    this->canFire = canFire;
    this->headColor = headColor;
}
void CVenus::Render()
{
    //Get head animations
    int headAniId = 0;
    if (canFire)
    {
        if (headColor == VENUS_HEAD_RED)
        {
            switch (state)
            {
            case STATE_AIM_LOWER_LEFT:
                headAniId = ID_ANI_AIM_LOWER_LEFT_RED;
                break;
            case STATE_AIM_UPPER_LEFT:
                headAniId = ID_ANI_AIM_UPPER_LEFT_RED;
                break;
            case STATE_AIM_UPPER_RIGHT:
                headAniId = ID_ANI_AIM_UPPER_RIGHT_RED;
                break;
            case STATE_AIM_LOWER_RIGHT:
                headAniId = ID_ANI_AIM_LOWER_RIGHT_RED;
                break;
            }
        }
        else
        {
            switch (state)
            {
            case STATE_AIM_LOWER_LEFT:
                headAniId = ID_ANI_AIM_LOWER_LEFT_GREEN;
                break;
            case STATE_AIM_UPPER_LEFT:
                headAniId = ID_ANI_AIM_UPPER_LEFT_GREEN;
                break;
            case STATE_AIM_UPPER_RIGHT:
                headAniId = ID_ANI_AIM_UPPER_RIGHT_GREEN;
                break;
            case STATE_AIM_LOWER_RIGHT:
                headAniId = ID_ANI_AIM_LOWER_RIGHT_GREEN;
                break;
            }
        }
    }
    else
    {
        headAniId = ID_ANI_NORMAL;
    }
    //Render
    CSprites::GetInstance()->Get(ID_SPRITE_PLANT_VINE)->Draw(x, y + 8);
    CAnimations::GetInstance()->Get(headAniId)->Render(x, y - 6);
    //RenderBoundingBox();
}
void CVenus::OnNoCollision(DWORD dt)
{
    x += vx * dt;
    y += vy * dt;
};
void CVenus::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	//Get Mario's Position
    CPlayScene* scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
	CMario* player = (CMario*)scene->GetPlayer();
    player->GetPosition(mx,my);
    //Aim
    if (canFire)
    {
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
    }
    //DebugOut(L"[INFO] %d %d %d\n", (mx < x) , (my > y), state);
    //Wait
    if (isWaiting)
    {
        if (GetTickCount64() - startWaiting < WAITING_TIME)
            return;
        isWaiting = false;
        if (canFire)
        {
            if (y <= maxHeight)
            {
                //Fire
                int dir = 0;
                switch (state)
                {
                case STATE_AIM_LOWER_LEFT:
                    dir = (abs(x - mx) < DANGEROUS_DISTANCE) ? DIR_HEAVY_LOWER_LEFT : DIR_LIGHT_LOWER_LEFT;
                    break;
                case STATE_AIM_UPPER_LEFT:
                    dir = (abs(x - mx) < DANGEROUS_DISTANCE) ? DIR_HEAVY_UPPER_LEFT : DIR_LIGHT_UPPER_LEFT;
                    break;
                case STATE_AIM_UPPER_RIGHT:
                    dir = (abs(x - mx) > DANGEROUS_DISTANCE) ? DIR_LIGHT_UPPER_RIGHT : DIR_HEAVY_UPPER_RIGHT;
                    break;
                case STATE_AIM_LOWER_RIGHT:
                    dir = (abs(x - mx) > DANGEROUS_DISTANCE) ? DIR_LIGHT_LOWER_RIGHT : DIR_HEAVY_LOWER_RIGHT;
                    break;
                }
                CFireball* fire = new CFireball(x, y, dir);
                scene->AddObj(fire);
            }
        }
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
    else
    {
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
}
void CVenus::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - 8;
	top = y - 8;
	right = left + 16;
    bottom = top + 30;
}