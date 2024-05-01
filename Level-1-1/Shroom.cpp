#include "Shroom.h"

CShroom::CShroom(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = SHROOM_GRAVITY;
	die_start = -1;
	SetState(SHROOM_STATE_WALKING);
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
	vy += ay * dt;
	vx += ax * dt;

	if ((state == SHROOM_STATE_DIE) && (GetTickCount64() - die_start > SHROOM_DIE_TIMEOUT))
	{
		isDeleted = true;
		return;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CShroom::Render()
{
	int aniId = ID_ANI_SHROOM_WALKING;
	if (state == SHROOM_STATE_DIE)
	{
		aniId = ID_ANI_SHROOM_DIE;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CShroom::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case SHROOM_STATE_DIE:
		die_start = GetTickCount64();
		y += (SHROOM_BBOX_HEIGHT - SHROOM_BBOX_HEIGHT_DIE) / 2;
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case SHROOM_STATE_WALKING:
		vx = -SHROOM_WALKING_SPEED;
		break;
	}
}
