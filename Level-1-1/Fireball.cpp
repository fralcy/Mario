#include "Fireball.h"
CFireball::CFireball(float x, float y, int dir):CGameObject(x,y)
{
	switch (dir)
	{
	case DIR_HEAVY_LOWER_LEFT:
		vy = FIREBALL_SPEED;
		vx = -FIREBALL_SPEED;
		break;
	case DIR_LIGHT_LOWER_LEFT:
		vy = FIREBALL_SPEED / 3;
		vx = -FIREBALL_SPEED;
		break;
	case DIR_LIGHT_UPPER_LEFT:
		vy = -FIREBALL_SPEED / 3;
		vx = -FIREBALL_SPEED;
		break;
	case DIR_HEAVY_UPPER_LEFT:
		vy = -FIREBALL_SPEED;
		vx = -FIREBALL_SPEED;
		break;
	case DIR_HEAVY_UPPER_RIGHT:
		vy = -FIREBALL_SPEED;
		vx = FIREBALL_SPEED;
		break;
	case DIR_LIGHT_UPPER_RIGHT:
		vy = -FIREBALL_SPEED / 3;
		vx = FIREBALL_SPEED;
		break;
	case DIR_LIGHT_LOWER_RIGHT:
		vy = FIREBALL_SPEED / 3;
		vx = FIREBALL_SPEED;
		break;
	case DIR_HEAVY_LOWER_RIGHT:
		vy = FIREBALL_SPEED;
		vx = FIREBALL_SPEED;
		break;
	}
	start = GetTickCount64();
}
void CFireball::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_FIREBALL)->Render(x, y);
	//RenderBoundingBox();
}
void CFireball::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	x += vx * dt;
	y += vy * dt;
	if (GetTickCount64()-start > FIREBALL_TIMEOUT)
	{
		Delete();
	}
}
void CFireball::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - FIREBALL_SIZE / 2;
	top = y - FIREBALL_SIZE / 2;
	right = left + FIREBALL_SIZE;
	bottom = top + FIREBALL_SIZE;
}