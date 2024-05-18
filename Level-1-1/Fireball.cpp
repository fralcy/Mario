#include "Fireball.h"
CFireball::CFireball(float x, float y, int dir):CGameObject(x,y)
{
	switch (dir)
	{
	case DIR_LOWER_LEFT:
		vy = FIREBALL_SPEED;
		vx = -FIREBALL_SPEED;
		break;
	case DIR_LEFT:
		vy = FIREBALL_SPEED / 3;
		vx = -FIREBALL_SPEED;
		break;
	case DIR_UPPER_LEFT:
		vy = -FIREBALL_SPEED;
		vx = -FIREBALL_SPEED;
		break;
	case DIR_UPPER_RIGHT:
		vy = -FIREBALL_SPEED;
		vx = FIREBALL_SPEED;
		break;
	case DIR__RIGHT:
		vy = FIREBALL_SPEED / 3;
		vx = FIREBALL_SPEED;
		break;
	case DIR_LOWER_RIGHT:
		vy = FIREBALL_SPEED;
		vx = FIREBALL_SPEED;
		break;
	}
}
void CFireball::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_FIREBALL)->Render(x, y);
}
void CFireball::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	x += vx * dt;
	y += vy * dt;
	if (y > 260 || y < 0)
	{
		Delete();
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}
void CFireball::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - FIREBALL_SIZE / 2;
	top = y - FIREBALL_SIZE / 2;
	right = left + FIREBALL_SIZE;
	bottom = top + FIREBALL_SIZE;
}