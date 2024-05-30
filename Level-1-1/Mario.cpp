#include <algorithm>
#include "debug.h"
#include "AssetIDs.h"
#include "Mario.h"
#include "Game.h"

#include "Goomba.h"
#include "Coin.h"
#include "Portal.h"
#include "Shroom.h"
#include "Platform.h"
#include "MysteryBlock.h"
#include "Leaf.h"
#include "FirePlant.h"
#include "Fireball.h"
#include "Koopa.h"
#include "Spawner.h"
#include "MapBound.h"
#include "Collision.h"
#include "PlayScene.h"

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	vy += ay * dt;
	vx += ax * dt;
	if (abs(vx) > abs(maxVx)) vx = maxVx;

	// reset untouchable timer if untouchable time has passed
	if ( GetTickCount64() - untouchable_start > MARIO_UNTOUCHABLE_TIME) 
	{
		untouchable_start = 0;
		untouchable = 0;
	}
	if (GetTickCount64() - isKicking_start > MARIO_KICKING_TIME)
	{
		isKicking_start = 0;
		isKicking = 0;
	}
	if (GetTickCount64() - isAttacking_start > MARIO_ATTACKING_TIME)
	{
		isAttacking = 0;
		if (GetTickCount64() - isAttacking_start > MARIO_ATTACK_DELAY_TIME)
		{
			canAttack = true;
			isAttacking_start = 0;
		}
	}
	if (GetTickCount64() - isFloating_start > MARIO_FLOATING_TIME)
	{
		isFloating_start = 0;
		isFloating = false;
	}
	if (hold_obj)
	{
		switch (level)
		{
		case MARIO_LEVEL_SMALL:
			(nx > 0) ? hold_obj->SetPosition(x + 6, y - 4) : hold_obj->SetPosition(x - 6, y - 4);
			break;
		case MARIO_LEVEL_BIG:
		case MARIO_LEVEL_RACCOON:
			(nx > 0) ? hold_obj->SetPosition(x + 8, y - 2) : hold_obj->SetPosition(x - 8, y - 2);
			break;
		}
		//hold_obj->Render();
	}
	if (needTracking && y >= 115) needTracking = false;
	isOnPlatform = false;
	if (!isFloating) ay = MARIO_GRAVITY;
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CMario::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CMario::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->ny != 0 && e->obj->IsBlocking())
	{
		vy = 0;
		if (e->ny < 0) isOnPlatform = true;
	}
	else 
	if (e->nx != 0 && e->obj->IsBlocking())
	{
		vx = 0;
	}

	if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
	else if (dynamic_cast<CCoin*>(e->obj))
		OnCollisionWithCoin(e);
	else if (dynamic_cast<CPortal*>(e->obj))
		OnCollisionWithPortal(e);
	else if (dynamic_cast<CShroom*>(e->obj))
		OnCollisionWithShroom(e);
	else if (dynamic_cast<CMysteryBlock*>(e->obj))
		OnCollisionWithMysteryBlock(e);
	else if (dynamic_cast<CLeaf*>(e->obj))
		OnCollisionWithLeaf(e);
	else if (dynamic_cast<CFirePlant*>(e->obj))
		OnCollisionWithFirePlant(e);
	else if (dynamic_cast<CFireball*>(e->obj))
		OnCollisionWithFireBall(e);
	else if (dynamic_cast<CKoopa*>(e->obj))
		OnCollisionWithKoopa(e);
	else if (dynamic_cast<CSpawner*>(e->obj))
		OnCollisionWithSpawner(e);
	else if (dynamic_cast<CMapBound*>(e->obj))
		OnCollisionWithMapBound(e);
}

void CMario::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

	if (goomba->GetType() == GOOMBA_TYPE_NORMAL)
	{
		// jump on top >> kill Goomba and deflect a bit 
		if (e->ny < 0)
		{
			if (goomba->GetState() != GOOMBA_STATE_STOMPED)
			{
				goomba->SetState(GOOMBA_STATE_STOMPED);
				vy = -MARIO_JUMP_DEFLECT_SPEED;
			}
		}
		else // hit by Goomba
		{
			GetDamage();
		}
	}
	else
	{
		if (e->ny < 0)
		{
			if (goomba->GetState() == GOOMBA_STATE_WINGED)
			{
				goomba->SetState(GOOMBA_STATE_WALKING);
				vy = -MARIO_JUMP_DEFLECT_SPEED;
			}
			else if (goomba->GetState() == GOOMBA_STATE_WALKING)
			{
				goomba->SetState(GOOMBA_STATE_STOMPED);
				vy = -MARIO_JUMP_DEFLECT_SPEED;
			}
		}
		else // hit by Goomba
		{
			GetDamage();
		}
	}
}

void CMario::OnCollisionWithFirePlant(LPCOLLISIONEVENT e)
{
	CFirePlant* plant = dynamic_cast<CFirePlant*>(e->obj);
	{
		GetDamage();
	}
}
void CMario::OnCollisionWithFireBall(LPCOLLISIONEVENT e)
{
	CFireball* fire = dynamic_cast<CFireball*>(e->obj);
	{
		GetDamage();
	}
}
void CMario::OnCollisionWithKoopa(LPCOLLISIONEVENT e)
{
	CKoopa* koopa = dynamic_cast<CKoopa*>(e->obj);
	if (koopa->GetState() == KOOPA_STATE_WALKING)
	{
		if (e->ny < 0)
		{
			koopa->SetState(KOOPA_STATE_SHELL);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
		else
		{
			GetDamage();
		}
	}
	else
	{
		if ((state == MARIO_STATE_RUNNING_LEFT || state == MARIO_STATE_RUNNING_RIGHT) && !hold_obj && e->nx != 0 && e->ny == 0 && koopa->GetVX() == 0)
		{
			Pick(koopa);
		} 
		else if (koopa->GetVX() == 0)
		{
			StartKicking();
			if (e->nx > 0)
			{
				state = MARIO_STATE_KICKING_LEFT;
			}
			else if (e->nx < 0)
			{
				state = MARIO_STATE_KICKING_RIGHT;
			}
			koopa->SetSpeed(KOOPA_SPINNING_SPEED * nx, 0);
		}
		else if (e->ny < 0)
		{
			koopa->SetSpeed(0, 0);
		}
		else
		{
			GetDamage();
		}
	}
}
void CMario::Pick(CKoopa* koopa)
{
	hold_obj = koopa;
	koopa->SetState(KOOPA_STATE_SHELL);
}
void CMario::Throw()
{
	//hold_obj->SetState(KOOPA_STATE_SHELL);
	hold_obj->SetSpeed(KOOPA_SPINNING_SPEED * nx, 0);
	hold_obj = NULL;
	StartKicking();
}
void CMario::OnCollisionWithCoin(LPCOLLISIONEVENT e)
{
	CCoin* coin = dynamic_cast<CCoin*>(e->obj);
	if (coin->GetType() == 1)
	{
		e->obj->Delete();
		AddCoin();
	}
}
void CMario::OnCollisionWithShroom(LPCOLLISIONEVENT e)
{
	CShroom* shroom = (CShroom*) e->obj;
	if (shroom->GetType() == SHROOM_TYPE_RED)
	{
		if (level == MARIO_LEVEL_SMALL)
		{
			SetLevel(MARIO_LEVEL_BIG);
		}
		else
		{
			StartUntouchable();
		}
	}
	else
	{
		life++;
	}
	shroom->Delete();
}

void CMario::OnCollisionWithMysteryBlock(LPCOLLISIONEVENT e)
{
	float x = this->x;
	CMysteryBlock* mysteryblock  = dynamic_cast<CMysteryBlock*>(e->obj);
	if (e->ny > 0 && mysteryblock->GetState() == MYSTERY_BLOCK_STATE_ACTIVE)
	{
		mysteryblock->SpawnItem((x < mysteryblock->GetX()) ? 1 : -1);
	}
}
void CMario::OnCollisionWithLeaf(LPCOLLISIONEVENT e)
{
	e->obj->Delete();
	if (level == MARIO_LEVEL_BIG)
	{
		SetLevel(MARIO_LEVEL_RACCOON);
	}
	else
	{
		StartUntouchable();
	}
}

void CMario::OnCollisionWithSpawner(LPCOLLISIONEVENT e)
{
	CSpawner* s = (CSpawner*)e->obj;
	s->SpawnEnemies();
}
void CMario::OnCollisionWithMapBound(LPCOLLISIONEVENT e)
{
	if (e->ny != 0)
	{
		if (e->ny < 0)
			SetState(MARIO_STATE_DIE);
		else if (e->ny > 0)
			vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = 0;
		if (e->nx > 0)
			x += 8;
		else
			x -= 8;
	}

	DebugOut(L"%f, %f\n", e->nx, e->ny);
}

void CMario::OnCollisionWithPortal(LPCOLLISIONEVENT e)
{
	CPortal* p = (CPortal*)e->obj;
	CGame::GetInstance()->InitiateSwitchScene(p->GetSceneId());
}

//
// Get animation ID for small Mario
//
int CMario::GetAniIdSmall()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (hold_obj)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_SMALL_JUMP_HOLD_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_JUMP_HOLD_LEFT;
		}
		else if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT;
		}
	}
	else
		if (hold_obj)
		{
			if (vx == 0)
			{
				if (nx >= 0)
					aniId = ID_ANI_MARIO_SMALL_HOLD_RIGHT;
				else
					aniId = ID_ANI_MARIO_SMALL_HOLD_LEFT;
			}
			else
			{
				if (vx > 0)
					aniId = ID_ANI_MARIO_SMALL_HOLD_MOVE_RIGHT;
				else
					aniId = ID_ANI_MARIO_SMALL_HOLD_MOVE_LEFT;
			}
		}
		else if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_SIT_LEFT;
		}
		else if (isKicking)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_SMALL_KICK_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_KICK_LEFT;
		}
		else
		{
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_SMALL_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_MARIO_SMALL_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_SMALL_RUNNING_RIGHT;
				else if (ax == MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_SMALL_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_SMALL_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_SMALL_RUNNING_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_SMALL_WALKING_LEFT;
			}
		}

	if (aniId == -1) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;

	return aniId;
}

//
// Get animdation ID for big Mario
//
int CMario::GetAniIdBig()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (hold_obj)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_JUMP_HOLD_RIGHT;
			else
				aniId = ID_ANI_MARIO_JUMP_HOLD_LEFT;
		}
		else if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_JUMP_RUN_LEFT;
		}
		else
		{
			if (vy < 0)
			{
				if (nx >= 0)
					aniId = ID_ANI_MARIO_JUMP_WALK_RIGHT;
				else
					aniId = ID_ANI_MARIO_JUMP_WALK_LEFT;
			}
			else
			{
				if (nx >= 0)
					aniId = ID_ANI_MARIO_JUMP_WALK_RIGHT_DOWN;
				else
					aniId = ID_ANI_MARIO_JUMP_WALK_LEFT_DOWN;
			}
		}
	}
	else
		if (hold_obj)
		{
			if (vx == 0)
			{
				if (nx >= 0)
					aniId = ID_ANI_MARIO_HOLD_RIGHT;
				else
					aniId = ID_ANI_MARIO_HOLD_LEFT;
			}
			else
			{
				if (vx > 0)
					aniId = ID_ANI_MARIO_HOLD_RUN_RIGHT;
				else
					aniId = ID_ANI_MARIO_HOLD_RUN_LEFT;
			}
		}
		else if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_SIT_LEFT;
		}
		else if (isKicking)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_KICK_RIGHT;
			else
				aniId = ID_ANI_MARIO_KICK_LEFT;
		}
		else
		{
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_MARIO_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_RUNNING_RIGHT;
				else if (ax == MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_WALKING_RIGHT;

			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_RUNNING_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_WALKING_LEFT;
			}
		}

	if (aniId == -1) aniId = ID_ANI_MARIO_IDLE_RIGHT;

	return aniId;
}
int CMario::GetAniIdRaccoon()
{
	int aniId = -1;
	if (isAttacking)
	{
		if (nx >= 0)
			aniId = ID_ANI_MARIO_RACCOON_ATTACK_RIGHT;
		else
			aniId = ID_ANI_MARIO_RACCOON_ATTACK_LEFT;
	}
	else if (isFloating)
	{
		if (nx >= 0)
			aniId = ID_ANI_MARIO_RACCOON_FLOAT_RIGHT;
		else
			aniId = ID_ANI_MARIO_RACCOON_FLOAT_LEFT;
	}
	else if (!isOnPlatform)
	{
		if (hold_obj)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_RACCOON_JUMP_HOLD_RIGHT;
			else
				aniId = ID_ANI_MARIO_RACCOON_JUMP_HOLD_LEFT;
		}
		else if (vy < 0)
		{
			if (abs(ax) == MARIO_ACCEL_RUN_X)
			{
				if (nx >= 0)
					aniId = ID_ANI_MARIO_RACCOON_JUMP_RUN_RIGHT;
				else
					aniId = ID_ANI_MARIO_RACCOON_JUMP_RUN_LEFT;
			}
			else
			{
				if (nx >= 0)
					aniId = ID_ANI_MARIO_RACCOON_JUMP_WALK_RIGHT;
				else
					aniId = ID_ANI_MARIO_RACCOON_JUMP_WALK_LEFT;
			}
		}
		else if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_RACCOON_JUMP_RUN_RIGHT_DOWN;
			else
				aniId = ID_ANI_MARIO_RACCOON_JUMP_RUN_LEFT_DOWN;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_RACCOON_JUMP_WALK_RIGHT_DOWN;
			else
				aniId = ID_ANI_MARIO_RACCOON_JUMP_WALK_LEFT_DOWN;
		}
	}
	else
		if (hold_obj)
		{
			if (vx == 0)
			{
				if (nx >= 0)
					aniId = ID_ANI_MARIO_RACCOON_HOLD_RIGHT;
				else
					aniId = ID_ANI_MARIO_RACCOON_HOLD_LEFT;
			}
			else
			{
				if (vx > 0)
					aniId = ID_ANI_MARIO_RACCOON_HOLD_MOVE_RIGHT;
				else
					aniId = ID_ANI_MARIO_RACCOON_HOLD_MOVE_LEFT;
			}
		}
		else if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_RACCOON_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_RACCOON_SIT_LEFT;
		}
		else if (isKicking)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_RACCOON_KICK_RIGHT;
			else
				aniId = ID_ANI_MARIO_RACCOON_KICK_LEFT;
		}
		else
		{
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_RACCOON_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_RACCOON_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_MARIO_RACCOON_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_RACCOON_RUNNING_RIGHT;
				else if (ax == MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_RACCOON_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_RACCOON_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_RACCOON_RUNNING_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_RACCOON_WALKING_LEFT;
			}
		}

	if (aniId == -1) aniId = ID_ANI_MARIO_RACCOON_IDLE_RIGHT;

	return aniId;
}
void CMario::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;

	if (state == MARIO_STATE_DIE)
		aniId = ID_ANI_MARIO_DIE;
	else if (level == MARIO_LEVEL_BIG)
		aniId = GetAniIdBig();
	else if (level == MARIO_LEVEL_SMALL)
		aniId = GetAniIdSmall();
	else if (level == MARIO_LEVEL_RACCOON)
		aniId = GetAniIdRaccoon();

	animations->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
	
	DebugOutTitle(L"Coins: %d - Life: %d", coin, life);
}

void CMario::SetState(int state)
{
	// DIE is the end state, cannot be changed! 
	if (this->state == MARIO_STATE_DIE) return; 

	switch (state)
	{
	case MARIO_STATE_RUNNING_RIGHT:
		if (isSitting) break;
		maxVx = MARIO_RUNNING_SPEED;
		ax = MARIO_ACCEL_RUN_X;
		nx = 1;
		break;
	case MARIO_STATE_RUNNING_LEFT:
		if (isSitting) break;
		maxVx = -MARIO_RUNNING_SPEED;
		ax = -MARIO_ACCEL_RUN_X;
		nx = -1;
		break;
	case MARIO_STATE_WALKING_RIGHT:
		if (isSitting) break;
		maxVx = MARIO_WALKING_SPEED;
		ax = MARIO_ACCEL_WALK_X;
		nx = 1;
		break;
	case MARIO_STATE_WALKING_LEFT:
		if (isSitting) break;
		maxVx = -MARIO_WALKING_SPEED;
		ax = -MARIO_ACCEL_WALK_X;
		nx = -1;
		break;
	case MARIO_STATE_JUMP:
		if (isSitting) break;
		if (isOnPlatform)
		{
			if (abs(this->vx) == MARIO_RUNNING_SPEED)
				vy = -MARIO_JUMP_RUN_SPEED_Y;
			else
				vy = -MARIO_JUMP_SPEED_Y;
		}
		break;

	case MARIO_STATE_RELEASE_JUMP:
		if (isFloating) break;
		if (vy < 0) vy += MARIO_JUMP_SPEED_Y / 2;
		break;

	case MARIO_STATE_SIT:
		if (isOnPlatform && level != MARIO_LEVEL_SMALL && !hold_obj)
		{
			state = MARIO_STATE_IDLE;
			isSitting = true;
			vx = 0; vy = 0.0f;
			ax = 0;
			y +=MARIO_SIT_HEIGHT_ADJUST;
		}
		break;

	case MARIO_STATE_SIT_RELEASE:
		if (isSitting)
		{
			isSitting = false;
			state = MARIO_STATE_IDLE;
			y -= MARIO_SIT_HEIGHT_ADJUST;
		}
		break;

	case MARIO_STATE_IDLE:
		ax = 0.0f;
		vx = 0.0f;
		break;

	case MARIO_STATE_DIE:
		vy = -MARIO_JUMP_DEFLECT_SPEED;
		vx = 0;
		ax = 0;
		break;
	case MARIO_STATE_ATTACK_RIGHT:
	case MARIO_STATE_ATTACK_LEFT:
		if (!canAttack) return;
		Attack();
		break;
	case MARIO_STATE_FLY:
		if (!isOnPlatform)
		{
			vy = -MARIO_FLY_SPEED_Y;
			needTracking = true;
		}
		break;
	case MARIO_STATE_FLOAT:
		if (!isOnPlatform)
		{
			isFloating = true;
			isFloating_start = GetTickCount64();
			ay = 0;
			vy = MARIO_FLOAT_SPEED;
			vx = 0;
			if (nx >= 0)
			{
				maxVx = MARIO_WALKING_SPEED;
				ax = MARIO_ACCEL_WALK_X;
			}
			else
			{
				maxVx = -MARIO_WALKING_SPEED;
				ax = -MARIO_ACCEL_WALK_X;
			}
		}
		break;
	}

	CGameObject::SetState(state);
}

void CMario::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (level != MARIO_LEVEL_SMALL)
	{
		if (isSitting)
		{
			left = x - MARIO_BIG_SITTING_BBOX_WIDTH / 2;
			top = y - MARIO_BIG_SITTING_BBOX_HEIGHT / 2;
			right = left + MARIO_BIG_SITTING_BBOX_WIDTH;
			bottom = top + MARIO_BIG_SITTING_BBOX_HEIGHT;
		}
		else 
		{
			left = x - MARIO_BIG_BBOX_WIDTH/2;
			top = y - MARIO_BIG_BBOX_HEIGHT/2;
			right = left + MARIO_BIG_BBOX_WIDTH;
			bottom = top + MARIO_BIG_BBOX_HEIGHT;
		}
	}
	else
	{
		left = x - MARIO_SMALL_BBOX_WIDTH/2;
		top = y - MARIO_SMALL_BBOX_HEIGHT/2;
		right = left + MARIO_SMALL_BBOX_WIDTH;
		bottom = top + MARIO_SMALL_BBOX_HEIGHT;
	}
}

void CMario::SetLevel(int l)
{
	// Adjust position to avoid falling off platform
	if (this->level == MARIO_LEVEL_SMALL)
	{
		y -= (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT) / 2;
	}
	level = l;
}

void CMario::GetDamage()
{
	if (untouchable == 0)
	{
		if (level == MARIO_LEVEL_BIG)
		{
			SetLevel(MARIO_LEVEL_SMALL);
			StartUntouchable();
		}
		else if (level == MARIO_LEVEL_RACCOON)
		{
			SetLevel(MARIO_LEVEL_BIG);
			StartUntouchable();
		}
		else
		{
			DebugOut(L">>> Mario DIE >>> \n");
			SetState(MARIO_STATE_DIE);
		}
	}
}