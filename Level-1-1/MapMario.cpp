#include "MapMario.h"

void CMapMario::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}
void CMapMario::OnCollisionWith(LPCOLLISIONEVENT e)
{
	
}
void CMapMario::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CCollision::GetInstance()->Process(this, dt, coObjects);
}
void CMapMario::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - 8;
	top = y - 8;
	right = left + 16;
	bottom = top + 16;
}

void CMapMario::OnCollisionWithLevel(LPCOLLISIONEVENT e)
{

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
}
