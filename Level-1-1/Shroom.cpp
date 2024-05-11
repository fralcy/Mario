#include "Shroom.h"

CShroom::CShroom(float x, float y, int nx) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = SHROOM_GRAVITY;
	this->nx = nx;
}

void CShroom::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - SHROOM_BBOX_WIDTH / 2;
	top = y - SHROOM_BBOX_HEIGHT / 2;
	right = left + SHROOM_BBOX_WIDTH;
	bottom = top + SHROOM_BBOX_HEIGHT;
}

void CShroom::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CShroom::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CShroom*>(e->obj)) return;

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CShroom::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isspawning)
	{
		if (y > maxheight)
		{
			y -= 0.05f * dt;
		}
		else
		{
			isspawning = false;
			vx = SHROOM_WALKING_SPEED * nx;
		}
	}
	else
	{
		vy += ay * dt;
		vx += ax * dt;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CShroom::Render()
{
	int ani = ID_ANI_SHROOM_WALKING;
	if (isspawning)
	{
		ani = ID_ANI_SHROOM_GROWING;
	}
	CAnimations::GetInstance()->Get(ani)->Render(x, y);
	//RenderBoundingBox();
}