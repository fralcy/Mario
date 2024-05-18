#include "Koopa.h"

void CKoopa::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - WIDTH / 2;
	top = y - HEIGHT / 2;
	right = left + WIDTH;
	bottom = top + HEIGHT;
}

void CKoopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CKoopa::Render()
{
	int aniId = ID_ANI_KOOPA_WALKING_LEFT;
	if (vx > 0) aniId = ID_ANI_KOOPA_WALKING_RIGHT;
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CKoopa::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CKoopa::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CKoopa*>(e->obj)) return;

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

CKoopa::CKoopa(float x, float y, int color) :CGameObject(x, y)
{
	this->color = color;
	this->ax = 0;
	this->ay = GRAVITY;
	die_start = -1;
	SetState(STATE_WALKING_LEFT);
}

void CKoopa::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case STATE_WALKING_LEFT:
		vx = -WALKING_SPEED;
		break;
	}
}
