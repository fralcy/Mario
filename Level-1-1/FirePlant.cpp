#include "FirePlant.h"
#include "AssetIDs.h"
#include "PlayScene.h"
CFirePlant::CFirePlant(float x, float y, float vineLength):CGameObject::CGameObject(x,y)
{
	this->pathLength = CELL_HEIGHT + ((vineLength) * CELL_HEIGHT / 2);
	this->maxHeight = y - pathLength;
	vy = PLANT_SPEED;
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
	float mx = 0, my = 0;
	CPlayScene* pc = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
	pc->GetPlayer()->GetPosition(mx, my);
	//Appear if Mario is far away
	if (mx < x - CELL_WIDTH * 1.5f || mx > x + CELL_WIDTH * 1.5f)
	{
		if (isHidden)
		{
			if (y > maxHeight)
			{
				y -= vy * dt;
			}
			else
			{
				isHidden = false;
			}
		}
	}
	//Hide after appear
	if (!isHidden)
	{
		if (y < maxHeight + pathLength)
		{
			y += vy * dt;
		}
		else
		{
			isHidden = true;
		}
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
	RenderBoundingBox();
}
void CFirePlant::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - CELL_WIDTH / 2;
	top = y - CELL_HEIGHT / 2;
	right = left + CELL_WIDTH;
	bottom = top + CELL_HEIGHT * 2;
}