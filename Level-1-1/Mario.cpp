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
#include "Switchblock.h"
#include "Leaf.h"
#include "Venus.h"
#include "Fireball.h"
#include "Koopa.h"
#include "Effect.h"
#include "Pipe.h"
#include "Goal.h"
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
	//check if mario is running on platform
	if ((state != MARIO_STATE_RUNNING_LEFT && state != MARIO_STATE_RUNNING_RIGHT) || !isOnPlatform)
	{
		isRunning = false;
	}
	//prepare speed to fly when running
	if (isRunning)
	{
		if (p_meter < 7)
		{
			if (p_meter_start == 0)
			{
				p_meter_start = GetTickCount64();
			}
			if (GetTickCount64() - p_meter_start > MARIO_FLY_PREPARE_TIME / 7)
			{
				p_meter++;
				p_meter_start = 0;
			}
		}
	}
	else
	{
		if (p_meter > 0)
		{
			if (p_meter_start == 0)
			{
				p_meter_start = GetTickCount64();
			}
			if (p_meter == 7)
			{
				if (GetTickCount64() - p_meter_start > MARIO_FLY_PREPARE_TIME / 3)
				{
					p_meter--;
					p_meter_start = 0;
				}
			}
			else
			{
				if (GetTickCount64() - p_meter_start > MARIO_FLY_PREPARE_TIME / 7)
				{
					p_meter--;
					p_meter_start = 0;
				}
			}
		}
	}
	//can fly after run for a while
	if (p_meter == 7)
	{
		canFly = true;
		canFly_start = GetTickCount64();
	}
	//disable fly after a while
	if (canFly)
	{
		if (GetTickCount64() - canFly_start > MARIO_CAN_FLY_TIME)
		{
			canFly = false;
			canFly_start = 0;
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
	//switch to previous after mario die
	if (state == MARIO_STATE_DIE)
	{
		if (GetTickCount64()-die_start>MARIO_DIE_TIMEOUT)
		{
			CGame* g = CGame::GetInstance();
			if (g->GetLife()!=-1)//return previous scene if there are lifes remain
			{
				g->SetMarioLevel(1);
				g->InitiateSwitchScene(CGame::GetInstance()->GetPreviousScene());
				g->SetLife(CGame::GetInstance()->GetLife() - 1);
				g->SetCurMapNode(g->GetPrevMapNode());
			}
			else//return intro if there is no life lefts
			{
				g->InitiateSwitchScene(1);
				g->SetLife(4);
				g->SetCoin(0);
				g->SetScore(0);
				g->ClearCards();
				g->SetCurMapNode(0);
				g->SetMarioLevel(1);
				g->ClearCompletedNodes();
			}
		}
	}
	//stop using pipe
	if (isUsingPipe)
	{
		if (desY > y)
		{
			vy = MARIO_USING_PIPE_SPEED;
		}
		else
		{
			vy = -MARIO_USING_PIPE_SPEED;
		}
		if (GetTickCount64() - usingPipe_start > MARIO_USING_PIPE_TIME)
		{
			isUsingPipe = 0;
			usingPipe_start = 0;
			SetPosition(desX, desY);
			SetState(MARIO_STATE_IDLE);
		}
	}
	//level up
	if (isLevelUp)
	{
		vx = 0;
		vy = 0;
		if (GetTickCount64() - isLevelUp_start > MARIO_LEVEL_UP_TIME)
		{
			isLevelUp = false;
			isLevelUp_start = 0;
			SetState(MARIO_STATE_IDLE);
		}
	}
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
		if (e->ny < 0) 
		{
			isOnPlatform = true;
			canFly = false;
		}
	}
	else 
	if (e->nx != 0 && e->obj->IsBlocking())
	{
		vx = 0;
		isRunning = false;
		if (p_meter > 0) p_meter--;
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
	else if (dynamic_cast<CSwitchBlock*>(e->obj))
		OnCollisionWithSwitchBlock(e);
	else if (dynamic_cast<CLeaf*>(e->obj))
		OnCollisionWithLeaf(e);
	else if (dynamic_cast<CVenus*>(e->obj))
		OnCollisionWithFirePlant(e);
	else if (dynamic_cast<CFireball*>(e->obj))
		OnCollisionWithFireBall(e);
	else if (dynamic_cast<CKoopa*>(e->obj))
		OnCollisionWithKoopa(e);
	else if (dynamic_cast<CBrick*>(e->obj))
		OnCollisionWithBrick(e);
	else if (dynamic_cast<CSpawner*>(e->obj))
		OnCollisionWithSpawner(e);
	else if (dynamic_cast<CMapBound*>(e->obj))
		OnCollisionWithMapBound(e);
	else if (dynamic_cast<CPipe*>(e->obj))
		OnCollisionWithPipe(e);
	else if (dynamic_cast<CGoal*>(e->obj))
		OnCollisionWithGoal(e);
}

void CMario::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
	CScene* scene = CGame::GetInstance()->GetCurrentScene();
	if (goomba->GetState() == GOOMBA_STATE_STOMPED) return;
	if (goomba->GetType() == GOOMBA_TYPE_NORMAL)
	{
		// jump on top >> kill Goomba and deflect a bit 
		if (e->ny < 0)
		{
			if (goomba->GetState() != GOOMBA_STATE_STOMPED)
			{
				goomba->SetState(GOOMBA_STATE_STOMPED);
				vy = -MARIO_JUMP_DEFLECT_SPEED;
				if (scene->GetType() == SCENE_TYPE_PLAY)
				{
					CGame::GetInstance()->SetScore(CGame::GetInstance()->GetScore() + 100);
				}
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
			if (scene->GetType() == SCENE_TYPE_PLAY)
			{
				CGame::GetInstance()->SetScore(CGame::GetInstance()->GetScore() + 100);
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
	CVenus* plant = dynamic_cast<CVenus*>(e->obj);
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
	CScene* scene = CGame::GetInstance()->GetCurrentScene();
	if (koopa->GetType() == KOOPA_TYPE_WINGED)
	{
		if (e->ny < 0)
		{
			koopa->SetType(KOOPA_TYPE_NORMAL);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
			if (scene->GetType() == SCENE_TYPE_PLAY)
			{
				CGame::GetInstance()->SetScore(CGame::GetInstance()->GetScore() + 100);
			}
		}
		else
		{
			GetDamage();
		}
		return;
	}
	if (koopa->GetState() == KOOPA_STATE_WALKING)
	{
		if (e->ny < 0)
		{
			koopa->SetState(KOOPA_STATE_SHELL);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
			if (scene->GetType() == SCENE_TYPE_PLAY)
			{
				CGame::GetInstance()->SetScore(CGame::GetInstance()->GetScore() + 100);
			}
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
			if (scene->GetType() == SCENE_TYPE_PLAY)
			{
				CGame::GetInstance()->SetScore(CGame::GetInstance()->GetScore() + 100);
			}
		}
		else if (abs(koopa->GetVX()) == KOOPA_SPINNING_SPEED)
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
void CMario::OnCollisionWithPipe(LPCOLLISIONEVENT e)
{
	CPipe* pipe = dynamic_cast<CPipe*>(e->obj);
	pipe->GetDestinationPosition(desX, desY);
	x = pipe->GetX();
	SetState(MARIO_STATE_USING_PIPE);
}
void CMario::OnCollisionWithGoal(LPCOLLISIONEVENT e)
{
	CGoal* goal = (CGoal*)e->obj;
	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
	scene->GetKeyEventHandler()->ToggleEnabled();
	SetSpeed(0, MARIO_JUMP_SPEED_Y / 2);
	SetState(MARIO_STATE_WALKING_RIGHT);
	goal->Collect();
	int item = goal->GetItem();
	CGame* g = CGame::GetInstance();
	g->CollectCard(item);
	switch (item)
	{
	case GOAL_ITEM_SHROOM:
		if (scene->GetType() == SCENE_TYPE_PLAY)
		{
			g->SetScore(CGame::GetInstance()->GetScore() + 2000);
		}
		break;
	case GOAL_ITEM_FLOWER:
		if (scene->GetType() == SCENE_TYPE_PLAY)
		{
			g->SetScore(CGame::GetInstance()->GetScore() + 3000);
		}
		break;
	case GOAL_ITEM_STAR:
		if (scene->GetType() == SCENE_TYPE_PLAY)
		{
			g->SetScore(CGame::GetInstance()->GetScore() + 5000);
		}
		break;
	default:
		break;
	}
	scene->DeletMapBound();
}
void CMario::Throw()
{
	if (!hold_obj) return;
	//hold_obj->SetState(KOOPA_STATE_SHELL);
	hold_obj->SetSpeed(KOOPA_SPINNING_SPEED * nx, 0.0f);
	hold_obj = NULL;
	StartKicking();
}
void CMario::OnCollisionWithCoin(LPCOLLISIONEVENT e)
{
	CCoin* coin = dynamic_cast<CCoin*>(e->obj);
	CScene* scene = CGame::GetInstance()->GetCurrentScene();
	if (coin->GetType() == 1)
	{
		e->obj->Delete();
		CGame* g = CGame::GetInstance();
		int coin = g->GetCoin();
		coin++;
		if (coin >=100)
		{
			coin = 0;
			g->SetLife(g->GetLife() + 1);
		}
		g->SetCoin(coin);
		if (scene->GetType() == SCENE_TYPE_PLAY)
		{
			g->SetScore(g->GetScore() + 100);
		}
	}
}
void CMario::OnCollisionWithShroom(LPCOLLISIONEVENT e)
{
	CShroom* shroom = (CShroom*) e->obj;
	CScene* scene = CGame::GetInstance()->GetCurrentScene();
	if (shroom->GetType() == SHROOM_TYPE_RED)
	{
		if (level == MARIO_LEVEL_SMALL)
		{
			SetLevel(MARIO_LEVEL_BIG);
			SetState(MARIO_STATE_LEVEL_UP);
		}
		else
		{
			StartUntouchable();
		}
		if (scene->GetType() == SCENE_TYPE_PLAY)
		{
			CGame::GetInstance()->SetScore(CGame::GetInstance()->GetScore() + 1000);
		}
	}
	else
	{
		if (scene->GetType() == SCENE_TYPE_PLAY)
		{
			CGame::GetInstance()->SetLife(CGame::GetInstance()->GetLife() + 1);
		}
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
void CMario::OnCollisionWithSwitchBlock(LPCOLLISIONEVENT e)
{
	CSwitchBlock* switchblock = dynamic_cast<CSwitchBlock*>(e->obj);
	if (e->ny < 0 && switchblock->GetState()==SWITCH_BLOCK_STATE_UNPRESSED)
	{
		switchblock->SetState(SWITCH_BLOCK_STATE_PRESSED);
		switchblock->SwitchObjects();
	}
}
void CMario::OnCollisionWithLeaf(LPCOLLISIONEVENT e)
{
	e->obj->Delete();
	CScene* scene = CGame::GetInstance()->GetCurrentScene();
	if (scene->GetType() == SCENE_TYPE_PLAY)
	{
		CGame::GetInstance()->SetScore(CGame::GetInstance()->GetScore() + 1000);
	}
	if (level == MARIO_LEVEL_BIG)
	{
		SetLevel(MARIO_LEVEL_RACCOON);
	}
	else
	{
		StartUntouchable();
	}
}
void CMario::OnCollisionWithBrick(LPCOLLISIONEVENT e)
{
	if (e->ny > 0 && level != MARIO_LEVEL_SMALL)
	{
		LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
		CBrick* brick = (CBrick*)e->obj;
		float x, y;
		brick->GetPosition(x, y);
		CEffect* broken = new CEffect(x, y, ID_SPRITE_BRICK_BROKEN);
		scene->AddObj(broken);
		brick->Delete();
		if (scene->GetType() == SCENE_TYPE_PLAY)
		{
			CGame::GetInstance()->SetScore(CGame::GetInstance()->GetScore() + 10);
		}
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
		isRunning = false;
	}

	DebugOut(L"%f, %f\n", e->nx, e->ny);
}

void CMario::OnCollisionWithPortal(LPCOLLISIONEVENT e)
{
	CPortal* p = (CPortal*)e->obj;
	CGame* g = CGame::GetInstance();
	LPPLAYSCENE scene = (LPPLAYSCENE)g->GetCurrentScene();
	g->SetPrevMapNode(g->GetCurMapNode());
	g->CompleteCurNode();
	g->SetMarioLevel(level);
	g->InitiateSwitchScene(p->GetSceneId());
	if (scene->GetType() == SCENE_TYPE_PLAY)
	{
		g->SetScore(g->GetScore() + scene->GetTime() * 50);
	}
}

//
// Get animation ID for small Mario
//
int CMario::GetAniIdSmall()
{
	int aniId = -1;
	if (isUsingPipe)
	{
		return ID_ANI_MARIO_SMALL_USING_PIPE;
	}
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
	if (isMario)
	{
		if (isUsingPipe)
		{
			return ID_ANI_MARIO_USING_PIPE;
		}
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
	}
	else
	{
		if (!isOnPlatform)
		{
			if (hold_obj)
			{
				if (nx >= 0)
					aniId = ID_ANI_LUIGI_JUMP_HOLD_RIGHT;
				else
					aniId = ID_ANI_LUIGI_JUMP_HOLD_LEFT;
			}
			else if (abs(ax) == MARIO_ACCEL_RUN_X)
			{
				if (nx >= 0)
					aniId = ID_ANI_LUIGI_JUMP_RUN_RIGHT;
				else
					aniId = ID_ANI_LUIGI_JUMP_RUN_LEFT;
			}
			else
			{
				if (vx == 0)
				{
					if (nx >= 0)
						aniId = ID_ANI_LUIGI_HOLD_RIGHT;
					else
						aniId = ID_ANI_LUIGI_HOLD_LEFT;
				}
				else
				{
					if (vx > 0)
						aniId = ID_ANI_LUIGI_HOLD_RUN_RIGHT;
					else
						aniId = ID_ANI_LUIGI_HOLD_RUN_LEFT;
				}
			}
		}
		else
		{
			if (hold_obj)
			{
				if (vx == 0)
				{
					if (nx >= 0)
						aniId = ID_ANI_LUIGI_HOLD_RIGHT;
					else
						aniId = ID_ANI_LUIGI_HOLD_LEFT;
				}
				else
				{
					if (vx > 0)
						aniId = ID_ANI_LUIGI_HOLD_RUN_RIGHT;
					else
						aniId = ID_ANI_LUIGI_HOLD_RUN_LEFT;
				}
			}
			else if (isSitting)
			{
				if (nx > 0)
					aniId = ID_ANI_LUIGI_SIT_RIGHT;
				else
					aniId = ID_ANI_LUIGI_SIT_LEFT;
			}
			else if (isKicking)
			{
				if (nx > 0)
					aniId = ID_ANI_LUIGI_KICK_RIGHT;
				else
					aniId = ID_ANI_LUIGI_KICK_LEFT;
			}
			else
			{
				if (vx == 0)
				{
					if (nx > 0) aniId = ID_ANI_LUIGI_IDLE_RIGHT;
					else aniId = ID_ANI_LUIGI_IDLE_LEFT;
				}
				else if (vx > 0)
				{
					if (ax < 0)
						aniId = ID_ANI_LUIGI_BRACE_RIGHT;
					else if (ax == MARIO_ACCEL_RUN_X)
						aniId = ID_ANI_LUIGI_RUNNING_RIGHT;
					else if (ax == MARIO_ACCEL_WALK_X)
						aniId = ID_ANI_LUIGI_WALKING_RIGHT;

				}
				else // vx < 0
				{
					if (ax > 0)
						aniId = ID_ANI_LUIGI_BRACE_LEFT;
					else if (ax == -MARIO_ACCEL_RUN_X)
						aniId = ID_ANI_LUIGI_RUNNING_LEFT;
					else if (ax == -MARIO_ACCEL_WALK_X)
						aniId = ID_ANI_LUIGI_WALKING_LEFT;
				}
			}
		}
		if (aniId == -1) aniId = ID_ANI_LUIGI_IDLE_RIGHT;
	}

	return aniId;
}
int CMario::GetAniIdRaccoon()
{
	int aniId = -1;
	if (isUsingPipe)
	{
		return ID_ANI_MARIO_RACCOON_USING_PIPE;
	}
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
	else if(isLevelUp)
	{
		if (nx > 0)
		{
			aniId = ID_ANI_MARIO_LEVEL_UP_RIGHT;
		}
		else
		{
			aniId = ID_ANI_MARIO_LEVEL_UP_LEFT;
		}
	}
	else if (level == MARIO_LEVEL_BIG)
		aniId = GetAniIdBig();
	else if (level == MARIO_LEVEL_SMALL)
		aniId = GetAniIdSmall();
	else if (level == MARIO_LEVEL_RACCOON)
		aniId = GetAniIdRaccoon();

	animations->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
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
		isRunning = true;
		break;
	case MARIO_STATE_RUNNING_LEFT:
		if (isSitting) break;
		maxVx = -MARIO_RUNNING_SPEED;
		ax = -MARIO_ACCEL_RUN_X;
		nx = -1;
		isRunning = true;
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
	case MARIO_STATE_HIGH_JUMP:
		vy = -MARIO_JUMP_SPEED_Y * 1.5f;
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
		if (isUsingPipe) return;
		ax = 0.0f;
		vx = 0.0f;
		ay = MARIO_GRAVITY;
		break;

	case MARIO_STATE_DIE:
		vy = -MARIO_JUMP_DEFLECT_SPEED;
		vx = 0;
		ax = 0;
		die_start = GetTickCount64();
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
	case MARIO_STATE_USING_PIPE:
	{
		isUsingPipe = true;
		usingPipe_start = GetTickCount64();
		vx = 0.0f;
		ax = 0.0f;
		break;
	}
	case MARIO_STATE_LEVEL_UP:
	{
		isLevelUp = true;
		isLevelUp_start = GetTickCount64();
		vx = 0.0f;
		ax = 0.0f;
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