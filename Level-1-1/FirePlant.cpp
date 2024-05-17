#include "FirePlant.h"
#include "AssetIDs.h"
#include "PlayScene.h"
CFirePlant::CFirePlant(float x, float y, float vineLength):CGameObject::CGameObject(x,y)
{
	this->minHeight = y;
    this->maxHeight = y - CELL_HEIGHT - vineLength * CELL_HEIGHT / 2;
	vy = PLANT_SPEED;
    startWaiting = 0;
}
void CFirePlant::Render()
{
	//Render head animations
	int headAniId = ID_ANI_PLANT_HEAD;
	CAnimations::GetInstance()->Get(headAniId)->Render(x, y);
	//Render vine
	CSprites* s = CSprites::GetInstance();
	int vineSprite = ID_SPRITE_PLANT_VINE;
	s->Get(vineSprite)->Draw(x, y + CELL_HEIGHT);
}
void CFirePlant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	//Get Mario's Position
	//CMario* player = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
    //float mx = player->GetX();
    //Wait after appearing or hiding
    if (isWaiting)
    {
        if (GetTickCount64() - startWaiting < WAITING_TIME) return;
        else isWaiting = false;
        (y < minHeight) ? isHiding = true : isSpawning = true;
    }

    //Calculate distance to Mario
    //float distance = abs(x - mx);
    //DebugOut(L"[INFO] waiting %d, hiding %d, spawning %d\n",isWaiting, isHiding,isSpawning);

    //Appear if Mario is far away or it's appearing
    if (/*distance < SAFE_DISTANCE ||*/ isSpawning)
    {
        y -= vy * dt;
        if (y <= maxHeight)
        {
            y = maxHeight; // Ensure y doesn't go above maxHeight
            isSpawning = false;
            isWaiting = true;
            startWaiting = GetTickCount64();
        }
    }

    // Hide after appearing
    if (isHiding)
    {
        y += vy * dt;
        if (y >= minHeight)
        {
            y = minHeight; // Ensure y doesn't go below minHeight
            isHiding = false;
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