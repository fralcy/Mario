#include "MapMario.h"
#include "debug.h"
void CMapMario::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}
void CMapMario::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CNode*>(e->obj))
		OnCollisionWithNode(e);
}
void CMapMario::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (nextNode)
	{
		float desX, desY;
		nextNode->GetPosition(desX, desY);
		//DebugOut(L"%f, %f, %f, %f\n", x, y, desX, desY);
		SetPosition(desX, desY);
		if (x == desX && y ==desY)
		{
			SetSpeed(0, 0);
			curNode = nextNode;
			nextNode = NULL;
		}
	}
	CCollision::GetInstance()->Process(this, dt, coObjects);
}
void CMapMario::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - 8;
	top = y - 8;
	right = left + 16;
	bottom = top + 16;
}

void CMapMario::OnCollisionWithNode(LPCOLLISIONEVENT e)
{
	nextNode = (CNode*)(e->obj);
}
void CMapMario::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = ID_ANI_MAP_MAIRO_SMALL;

	if (level == MARIO_LEVEL_BIG)
		aniId = ID_ANI_MAP_MAIRO_RACCOON;
	else if (level == MARIO_LEVEL_SMALL)
		aniId = ID_ANI_MAP_MAIRO_SMALL;
	else if (level == MARIO_LEVEL_RACCOON)
		aniId = ID_ANI_MAP_MAIRO_RACCOON;

	animations->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}
