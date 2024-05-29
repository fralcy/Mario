#include "Goomba.h"
#include "PlayScene.h"
#include "Mario.h"
#include "Hitbox.h"

CGoomba::CGoomba(float x, float y, int type):CGameObject(x, y)
{
	this->type = type;
	this->ax = 0;
	this->ay = GOOMBA_GRAVITY;
	die_start = fly_start = -1;
	vx = -GOOMBA_WALKING_SPEED;
	(type == 0) ? SetState(GOOMBA_STATE_WALKING) : SetState(GOOMBA_STATE_WINGED);
}

void CGoomba::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x - GOOMBA_BBOX_WIDTH / 2;
	right = left + GOOMBA_BBOX_WIDTH;
	if (state == GOOMBA_STATE_STOMPED)
	{
		top = y - GOOMBA_BBOX_HEIGHT_DIE/2;
		bottom = top + GOOMBA_BBOX_HEIGHT_DIE;
	}
	else
	{
		top = y - GOOMBA_BBOX_HEIGHT / 2;
		bottom = top + GOOMBA_BBOX_HEIGHT - 1;
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

	if (e->ny != 0)
	{
		vy = 0;
		if (e->ny < 0 && hop_count == 0)  // Goomba lands on the ground
		{
			ChangeDirection();
		}
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

	if (state == GOOMBA_STATE_WINGED)
	{
		if (hop_count <3)
		{
			if (GetTickCount64() - fly_start > PARAGOOMBA_HOP_DELAY)
			{
				canFly = true;
				fly_start = -1;
			}
		}
		else
		{
			if (GetTickCount64() - fly_start > PARAGOOMBA_FLY_DELAY)
			{
				canFly = true;
				fly_start = -1;
			}
		}
		if (canFly)
		{
			Fly();
		}
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
			if (vy == 0)
				aniId = ID_ANI_PARAGOOMBA_WALING_2;
			else
				aniId = ID_ANI_PARAGOOMBA_FLYING;
			break;
		case GOOMBA_STATE_STOMPED:
			aniId = ID_ANI_PARAGOOMBA_STOMPED;
		}
	}


	CAnimations::GetInstance()->Get(aniId)->Render(x,AdjustY());
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
			break;
		case GOOMBA_STATE_WINGED:
			hop_count = 0;
			canFly = true;
			break;
	}
}
float CGoomba::AdjustY()
{
	if (state == GOOMBA_STATE_WINGED) return y - 1.5f;
	//else if (state == GOOMBA_STATE_FLYING) return y - 4.0f;
	else return y;
}
void CGoomba::Fly()
{
	canFly = false;          // Reset canfly flag
	fly_start = GetTickCount64();  // Reset fly start time

	// Hopping logic
	if (hop_count < 3)
	{
		vy = -PARAGOOMBA_HOPPING_SPEED;  // Hop
		hop_count++;
	}
	else
	{
		vy = -PARAGOOMBA_FLYING_SPEED;  // Fly after three hops
		hop_count = 0;
	}
}
void CGoomba::ChangeDirection()
{
	CPlayScene* scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
	CMario* player = (CMario*)scene->GetPlayer();
	if (x > player->GetX())
	{
		vx = -GOOMBA_WALKING_SPEED;
	}
	else
	{
		vx = GOOMBA_WALKING_SPEED;
	}
}