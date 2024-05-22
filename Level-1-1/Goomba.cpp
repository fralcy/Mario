#include "Goomba.h"

CGoomba::CGoomba(float x, float y, int type):CGameObject(x, y)
{
	this->type = type;
	this->ax = 0;
	this->ay = GOOMBA_GRAVITY;
	die_start = fly_start = -1;
	(type == 0) ? SetState(GOOMBA_STATE_WALKING) : SetState(GOOMBA_STATE_WINGED);
}

void CGoomba::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (state == GOOMBA_STATE_STOMPED)
	{
		left = x - GOOMBA_BBOX_WIDTH/2;
		top = y - GOOMBA_BBOX_HEIGHT_DIE/2;
		right = left + GOOMBA_BBOX_WIDTH;
		bottom = top + GOOMBA_BBOX_HEIGHT_DIE;
	}
	else
	{ 
		left = x - GOOMBA_BBOX_WIDTH/2;
		top = y - GOOMBA_BBOX_HEIGHT/2;
		right = left + GOOMBA_BBOX_WIDTH;
		bottom = top + GOOMBA_BBOX_HEIGHT;
	}
}

void CGoomba::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CGoomba::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return; 
	if (dynamic_cast<CGoomba*>(e->obj)) return; 

	if (e->ny != 0 )
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CGoomba::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if ( (state==GOOMBA_STATE_STOMPED) && (GetTickCount64() - die_start > GOOMBA_DIE_TIMEOUT) )
	{
		isDeleted = true;
		return;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CGoomba::Render()
{
	int aniId = 0;
	if (type == GOOMBA_TYPE_NORMAL)
	{
		aniId = ID_ANI_GOOMBA_WALKING;
		if (state == GOOMBA_STATE_STOMPED)
		{
			aniId = ID_ANI_GOOMBA_STOMPED;
		}
	}
	else
	{
		switch (state)
		{
		case GOOMBA_STATE_WALKING:
			aniId = ID_ANI_PARAGOOMBA_WALKING;
			break;
		case GOOMBA_STATE_WINGED:
			aniId = ID_ANI_PARAGOOMBA_WALING_2;
			break;
		case GOOMBA_STATE_STOMPED:
			aniId = ID_ANI_PARAGOOMBA_STOMPED;
			break;
		case GOOMBA_STATE_FLYING:
			aniId = ID_ANI_PARAGOOMBA_FLYING;
		}
	}


	CAnimations::GetInstance()->Get(aniId)->Render(x,y);
	//RenderBoundingBox();
}

void CGoomba::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
		case GOOMBA_STATE_STOMPED:
			die_start = GetTickCount64();
			y += (GOOMBA_BBOX_HEIGHT - GOOMBA_BBOX_HEIGHT_DIE)/2;
			vx = 0;
			vy = 0;
			ay = 0; 
			break;
		case GOOMBA_STATE_WALKING:
		case GOOMBA_STATE_WINGED:
			vx = -GOOMBA_WALKING_SPEED;
			break;
	}
}
