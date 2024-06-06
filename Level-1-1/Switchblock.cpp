#include "Switchblock.h"
#include "AssetIDs.h"
#include "PlayScene.h"
#include "Coin.h"
#include "Brick.h"
void CSwitchBlock::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - 16 / 2;
	t = y - 16 / 2;
	r = l + 16;
	b = t + 16;
}
void CSwitchBlock::SwitchObjects()
{
	LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
	float x, y;
	DebugOut(L"switch!\n");
	if (!isSwitching)
	{
		objects = scene->GetSwitchableObjects();
		for (int i = 0; i < objects.size(); i++)
		{
			if (!objects[i]->IsDeleted())
			{
				objects[i]->GetPosition(x, y);
				objects[i]->Delete();
				LPGAMEOBJECT obj = new CCoin(x, y, 1);
				objects_2.push_back(obj);
				scene->AddObj(obj);
			}
		}
		objects.clear();
		isSwitching = true;
		switch_start = GetTickCount64();
	}
	else
	{
		for (int i = 0; i < objects_2.size(); i++)
		{
			if (!objects_2[i]->IsDeleted())
			{
				objects_2[i]->GetPosition(x, y);
				objects_2[i]->Delete();
				LPGAMEOBJECT obj = new CBrick(x, y);
				objects.push_back(obj);
				scene->AddObj(obj);
			}
		}
		objects_2.clear();
		isSwitching = false;
	}
}
CSwitchBlock::CSwitchBlock(float x, float y) : CGameObject(x, y)
{
	this->state = SWITCH_BLOCK_STATE_UNPRESSED;
	LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
}
void CSwitchBlock::Render()
{
	int spriteId = 0;
	if (state == SWITCH_BLOCK_STATE_UNPRESSED)
		spriteId = ID_SPRITE_SWITCH_BLOCK;
	else
		spriteId = ID_SPRITE_SWITCH_BLOCK_PRESSED;
	CSprites* s = CSprites::GetInstance();
	s->Get(spriteId)->Draw(x, y);
}
void CSwitchBlock::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isSwitching)
	{
		if (GetTickCount64() - switch_start > SWITCH_TIME)
		{
			SwitchObjects();
		}
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}