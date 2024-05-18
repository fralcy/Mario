#include "FirePlant.h"
#include "AssetIDs.h"
#include "PlayScene.h"
#include <cmath>
CFirePlant::CFirePlant(float x, float y, float vineLength):CGameObject::CGameObject(x,y)
{
	this->minHeight = y;
    this->maxHeight = y - CELL_HEIGHT - vineLength * CELL_HEIGHT / 2;
	vy = PLANT_SPEED;
    startWaiting = 0;
}
void CFirePlant::Render()
{
	//Get head animations
	int headAniId = ID_ANI_PLANT_HEAD;
	//Get vine sprite
	CSprites* s = CSprites::GetInstance();
    //Render
    CAnimations::GetInstance()->Get(headAniId)->Render(x, y);
	s->Get(ID_SPRITE_PLANT_VINE)->Draw(x, y + CELL_HEIGHT);
}
void CFirePlant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	//Get Mario's Position
    float mx, my;
    CPlayScene* scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
	CMario* player = (CMario*)scene->GetPlayer();
    player->GetPosition(mx,my);
    //Calculate distance to Mario
    float dx = abs(x - mx);
    //DebugOut(L"[INFO] x %d, mx %d, dx %d\n", x, mx, dx);
    //Wait after appearing or hiding
    if (isWaiting)
    {
        if (GetTickCount64() - startWaiting < WAITING_TIME)
            return;
        else
            isWaiting = false;
    }
    //Start appear or hide
    if (!isWaiting)
    {
        if (y == minHeight && dx > SAFE_DISTANCE)
        {
            isSpawning = true;
            isHiding = false;
        }
        else if (y == maxHeight)
        {
            isHiding = true;
            isSpawning = false;
        }
    }
    //Appear
    if (isSpawning)
    {
        y -= vy * dt;
        if (y < maxHeight)
        {
            y = maxHeight; // Ensure y doesn't go above maxHeight
            isSpawning = false;
            isWaiting = true;
            startWaiting = GetTickCount64();
        }
    }
    //Hide
    if(isHiding)
    {
        y += vy * dt;
        if (y > minHeight)
        {
            y = minHeight; // Ensure y doesn't go below minHeight
            isHiding = false;
            isWaiting = true;
            startWaiting = GetTickCount64();
        }
    }
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
	//RenderBoundingBox();
}
void CFirePlant::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - (CELL_WIDTH / 2);
	top = y - (CELL_HEIGHT / 2);
	right = left + CELL_WIDTH;
	bottom = top + (CELL_HEIGHT * 2);
}