#include "Goal.h"
#include "AssetIDs.h"
#include <ctime>
void CGoal::Render()
{
	int aniId = ID_ANI_SHROOM;
	switch (item)
	{
	case GOAL_ITEM_SHROOM:
		aniId = ID_ANI_SHROOM;
		break;
	case GOAL_ITEM_FLOWER:
		aniId = ID_ANI_FLOWER;
		break;
	case GOAL_ITEM_STAR:
		aniId = ID_ANI_STAR;
		break;
	}
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CGoal::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (wait_start == 0)
	{
		wait_start = GetTickCount64();
	}
	else
	{
		if (GetTickCount64()-wait_start>GOAL_CHANGE_DELAY)
		{
			srand((unsigned int)time(0));
			item += rand() % 2 + 1;
			if (item > 3) item -= 3;
			wait_start = 0;
		}
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CGoal::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - 16 / 2;
	t = y - 16 / 2;
	r = l + 16;
	b = t + 16;
}
