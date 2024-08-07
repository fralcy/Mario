#pragma once
#include "GameObject.h"

#include "Animation.h"
#include "Animations.h"

#include "debug.h"

#include "Koopa.h"

#define MARIO_WALKING_SPEED		0.09f
#define MARIO_RUNNING_SPEED		0.18f

#define MARIO_ACCEL_WALK_X	0.0005f
#define MARIO_ACCEL_RUN_X	0.0007f

#define MARIO_JUMP_SPEED_Y		0.5f
#define MARIO_JUMP_RUN_SPEED_Y	0.6f
#define MARIO_FLY_SPEED_Y		0.5f
#define MARIO_FLOAT_SPEED		0.05f

#define MARIO_GRAVITY			0.002f

#define MARIO_USING_PIPE_SPEED	0.0090f

#define MARIO_JUMP_DEFLECT_SPEED  0.4f

#define MARIO_STATE_DIE				-10
#define MARIO_STATE_IDLE			0
#define MARIO_STATE_WALKING_RIGHT	100
#define MARIO_STATE_WALKING_LEFT	200

#define MARIO_STATE_JUMP			300
#define MARIO_STATE_RELEASE_JUMP    301

#define MARIO_STATE_RUNNING_RIGHT	400
#define MARIO_STATE_RUNNING_LEFT	500

#define MARIO_STATE_SIT				600
#define MARIO_STATE_SIT_RELEASE		601

#define MARIO_STATE_KICKING_RIGHT	700
#define MARIO_STATE_KICKING_LEFT	800

#define MARIO_STATE_ATTACK_RIGHT	900
#define MARIO_STATE_ATTACK_LEFT		1000

#define MARIO_STATE_FLY				1100
#define MARIO_STATE_FLOAT			1200

#define MARIO_STATE_USING_PIPE		1300

#define MARIO_STATE_LEVEL_UP		1400

#define MARIO_STATE_HIGH_JUMP		1500
#pragma region ANIMATION_ID

#define ID_ANI_MARIO_IDLE_RIGHT 400
#define ID_ANI_MARIO_IDLE_LEFT 401

#define ID_ANI_MARIO_HOLD_RIGHT 450
#define ID_ANI_MARIO_HOLD_LEFT 451

#define ID_ANI_MARIO_WALKING_RIGHT 500
#define ID_ANI_MARIO_WALKING_LEFT 501

#define ID_ANI_MARIO_KICK_RIGHT 550
#define ID_ANI_MARIO_KICK_LEFT 551

#define ID_ANI_MARIO_HOLD_WALK_RIGHT 575
#define ID_ANI_MARIO_HOLD_WALK_LEFT 576

#define ID_ANI_MARIO_RUNNING_RIGHT 600
#define ID_ANI_MARIO_RUNNING_LEFT 601

#define ID_ANI_MARIO_HOLD_RUN_RIGHT 650
#define ID_ANI_MARIO_HOLD_RUN_LEFT 651

#define ID_ANI_MARIO_JUMP_WALK_RIGHT 700
#define ID_ANI_MARIO_JUMP_WALK_LEFT 701

#define ID_ANI_MARIO_JUMP_WALK_RIGHT_DOWN 725
#define ID_ANI_MARIO_JUMP_WALK_LEFT_DOWN 726

#define ID_ANI_MARIO_JUMP_HOLD_RIGHT 750
#define ID_ANI_MARIO_JUMP_HOLD_LEFT 751

#define ID_ANI_MARIO_JUMP_RUN_RIGHT 800
#define ID_ANI_MARIO_JUMP_RUN_LEFT 801

#define ID_ANI_MARIO_SIT_RIGHT 900
#define ID_ANI_MARIO_SIT_LEFT 901

#define ID_ANI_MARIO_BRACE_RIGHT 1000
#define ID_ANI_MARIO_BRACE_LEFT 1001

#define ID_ANI_MARIO_DIE 999

// SMALL MARIO
#define ID_ANI_MARIO_SMALL_IDLE_RIGHT 1100
#define ID_ANI_MARIO_SMALL_IDLE_LEFT 1101

#define ID_ANI_MARIO_SMALL_HOLD_RIGHT 1150
#define ID_ANI_MARIO_SMALL_HOLD_LEFT 1151

#define ID_ANI_MARIO_SMALL_WALKING_RIGHT 1200
#define ID_ANI_MARIO_SMALL_WALKING_LEFT 1201

#define ID_ANI_MARIO_SMALL_KICK_RIGHT 1250
#define ID_ANI_MARIO_SMALL_KICK_LEFT 1251

#define ID_ANI_MARIO_SMALL_RUNNING_RIGHT 1300
#define ID_ANI_MARIO_SMALL_RUNNING_LEFT 1301

#define ID_ANI_MARIO_SMALL_HOLD_MOVE_RIGHT 1350
#define ID_ANI_MARIO_SMALL_HOLD_MOVE_LEFT 1351

#define ID_ANI_MARIO_SMALL_BRACE_RIGHT 1400
#define ID_ANI_MARIO_SMALL_BRACE_LEFT 1401

#define ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT 1500
#define ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT 1501

#define ID_ANI_MARIO_SMALL_JUMP_HOLD_RIGHT 1550
#define ID_ANI_MARIO_SMALL_JUMP_HOLD_LEFT 1551

#define ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT 1600
#define ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT 1601

// RACCOON MARIO
#define ID_ANI_MARIO_RACCOON_IDLE_RIGHT 1700
#define ID_ANI_MARIO_RACCOON_IDLE_LEFT 1701

#define ID_ANI_MARIO_RACCOON_HOLD_RIGHT 1750
#define ID_ANI_MARIO_RACCOON_HOLD_LEFT 1751

#define ID_ANI_MARIO_RACCOON_WALKING_RIGHT 1800
#define ID_ANI_MARIO_RACCOON_WALKING_LEFT 1801

#define ID_ANI_MARIO_RACCOON_KICK_RIGHT 1850
#define ID_ANI_MARIO_RACCOON_KICK_LEFT 1851

#define ID_ANI_MARIO_RACCOON_RUNNING_RIGHT 1900
#define ID_ANI_MARIO_RACCOON_RUNNING_LEFT 1901

#define ID_ANI_MARIO_RACCOON_HOLD_MOVE_RIGHT 1950
#define ID_ANI_MARIO_RACCOON_HOLD_MOVE_LEFT 1951

#define ID_ANI_MARIO_RACCOON_BRACE_RIGHT 2000
#define ID_ANI_MARIO_RACCOON_BRACE_LEFT 2001

#define ID_ANI_MARIO_RACCOON_JUMP_WALK_RIGHT 2100
#define ID_ANI_MARIO_RACCOON_JUMP_WALK_LEFT 2101

#define ID_ANI_MARIO_RACCOON_JUMP_WALK_RIGHT_DOWN 2125
#define ID_ANI_MARIO_RACCOON_JUMP_WALK_LEFT_DOWN 2126

#define ID_ANI_MARIO_RACCOON_JUMP_HOLD_RIGHT 2150
#define ID_ANI_MARIO_RACCOON_JUMP_HOLD_LEFT 2151

#define ID_ANI_MARIO_RACCOON_JUMP_RUN_RIGHT 2200
#define ID_ANI_MARIO_RACCOON_JUMP_RUN_LEFT 2201

#define ID_ANI_MARIO_RACCOON_JUMP_RUN_RIGHT_DOWN 2250
#define ID_ANI_MARIO_RACCOON_JUMP_RUN_LEFT_DOWN 2251

#define ID_ANI_MARIO_RACCOON_SIT_RIGHT 2300
#define ID_ANI_MARIO_RACCOON_SIT_LEFT 2301

#define ID_ANI_MARIO_RACCOON_ATTACK_RIGHT 2400
#define ID_ANI_MARIO_RACCOON_ATTACK_LEFT 2401

#define ID_ANI_MARIO_RACCOON_FLOAT_RIGHT 2500
#define ID_ANI_MARIO_RACCOON_FLOAT_LEFT 2501

#define ID_ANI_MARIO_LEVEL_UP_RIGHT 2600
#define ID_ANI_MARIO_LEVEL_UP_LEFT 2601

//LUIGI
#define ID_ANI_LUIGI_IDLE_RIGHT 3400
#define ID_ANI_LUIGI_IDLE_LEFT 3401

#define ID_ANI_LUIGI_HOLD_RIGHT 3450
#define ID_ANI_LUIGI_HOLD_LEFT 3451

#define ID_ANI_LUIGI_WALKING_RIGHT 3500
#define ID_ANI_LUIGI_WALKING_LEFT 3501

#define ID_ANI_LUIGI_KICK_RIGHT 3550
#define ID_ANI_LUIGI_KICK_LEFT 3551

#define ID_ANI_LUIGI_HOLD_WALK_RIGHT 3575
#define ID_ANI_LUIGI_HOLD_WALK_LEFT 3576

#define ID_ANI_LUIGI_RUNNING_RIGHT 3600
#define ID_ANI_LUIGI_RUNNING_LEFT 3601

#define ID_ANI_LUIGI_HOLD_RUN_RIGHT 3650
#define ID_ANI_LUIGI_HOLD_RUN_LEFT 3651

#define ID_ANI_LUIGI_JUMP_WALK_RIGHT 3700
#define ID_ANI_LUIGI_JUMP_WALK_LEFT 3701

#define ID_ANI_LUIGI_JUMP_WALK_RIGHT_DOWN 3725
#define ID_ANI_LUIGI_JUMP_WALK_LEFT_DOWN 3726

#define ID_ANI_LUIGI_JUMP_HOLD_RIGHT 3750
#define ID_ANI_LUIGI_JUMP_HOLD_LEFT 3751

#define ID_ANI_LUIGI_JUMP_RUN_RIGHT 3800
#define ID_ANI_LUIGI_JUMP_RUN_LEFT 3801

#define ID_ANI_LUIGI_SIT_RIGHT 3900
#define ID_ANI_LUIGI_SIT_LEFT 3901

#define ID_ANI_LUIGI_BRACE_RIGHT 4000
#define ID_ANI_LUIGI_BRACE_LEFT 4001
#pragma endregion

#define GROUND_Y 160.0f




#define	MARIO_LEVEL_SMALL	1
#define	MARIO_LEVEL_BIG		2
#define MARIO_LEVEL_RACCOON 3

#define MARIO_BIG_BBOX_WIDTH  14
#define MARIO_BIG_BBOX_HEIGHT 24
#define MARIO_BIG_SITTING_BBOX_WIDTH  14
#define MARIO_BIG_SITTING_BBOX_HEIGHT 16

#define MARIO_SIT_HEIGHT_ADJUST ((MARIO_BIG_BBOX_HEIGHT-MARIO_BIG_SITTING_BBOX_HEIGHT)/2)

#define MARIO_SMALL_BBOX_WIDTH  13
#define MARIO_SMALL_BBOX_HEIGHT 12


#define MARIO_UNTOUCHABLE_TIME 2500
#define MARIO_KICKING_TIME	200
#define MARIO_ATTACKING_TIME	300
#define MARIO_ATTACK_DELAY_TIME	600
#define MARIO_FLOATING_TIME	150
#define MARIO_FLY_PREPARE_TIME 2000
#define MARIO_CAN_FLY_TIME 7500
#define MARIO_DIE_TIMEOUT 2500
#define MARIO_USING_PIPE_TIME 2000
#define MARIO_LEVEL_UP_TIME 1000

class CMario : public CGameObject
{
	BOOLEAN isSitting;
	float maxVx;
	float ax;				// acceleration on x 
	float ay;				// acceleration on y 

	CKoopa* hold_obj;

	int level; 
	int untouchable; 
	ULONGLONG untouchable_start, isKicking_start, isAttacking_start, isFloating_start, p_meter_start, canFly_start, die_start, usingPipe_start, isLevelUp_start;
	BOOLEAN isOnPlatform, isKicking, isAttacking, canAttack, isFloating, needTracking, isRunning, canFly, isUsingPipe, isLevelUp;
	int p_meter;
	float desX, desY;
	bool isMario;
	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithCoin(LPCOLLISIONEVENT e);
	void OnCollisionWithPortal(LPCOLLISIONEVENT e);
	void OnCollisionWithShroom(LPCOLLISIONEVENT e);
	void OnCollisionWithMysteryBlock(LPCOLLISIONEVENT e);
	void OnCollisionWithSwitchBlock(LPCOLLISIONEVENT e);
	void OnCollisionWithLeaf(LPCOLLISIONEVENT e);
	void OnCollisionWithFirePlant(LPCOLLISIONEVENT e);
	void OnCollisionWithFireBall(LPCOLLISIONEVENT e);
	void OnCollisionWithKoopa(LPCOLLISIONEVENT e);
	void OnCollisionWithBrick(LPCOLLISIONEVENT e);
	void Pick(CKoopa* koopa);
	void OnCollisionWithPipe(LPCOLLISIONEVENT e);
	void OnCollisionWithGoal(LPCOLLISIONEVENT e);
	void OnCollisionWithSpawner(LPCOLLISIONEVENT e);
	void OnCollisionWithMapBound(LPCOLLISIONEVENT e);
	int GetAniIdBig();
	int GetAniIdSmall();
	int GetAniIdRaccoon();

public:
	CMario(float x, float y, int level, int nx, bool isMario) : CGameObject(x, y)
	{
		isSitting = false;
		maxVx = 0.0f;
		ax = 0.0f;
		ay = MARIO_GRAVITY; 
		hold_obj = NULL;
		this->level = level;
		untouchable = isKicking = 0;
		untouchable_start = isKicking_start = -1;
		canAttack = true;
		isAttacking = 0;
		isAttacking_start = -1;
		isOnPlatform = false;
		isFloating = 0;
		isFloating_start = -1;
		needTracking = true;
		isRunning = 0;
		p_meter = 0;
		p_meter_start = 0;
		canFly = false;
		canFly_start = 0;
		isUsingPipe = 0;
		usingPipe_start = 0;
		isLevelUp = 0;
		isLevelUp_start = 0;
		this->nx = nx;
		this->isMario = isMario;
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);

	int IsCollidable()
	{ 
		return (state != MARIO_STATE_DIE && state != MARIO_STATE_USING_PIPE); 
	}

	int IsBlocking() { return 0/*(state != MARIO_STATE_DIE && untouchable==0)*/; }

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);

	void SetLevel(int l);
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }
	void StartKicking() { isKicking = 1; isKicking_start = GetTickCount64(); }
	void Attack() { isAttacking = 1; canAttack = 0; isAttacking_start = GetTickCount64(); }

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void GetDamage();
	int GetLevel() { return level; }
	bool IsHolding() { return (hold_obj) ? 1 : 0; }
	void Throw();
	void Drop() { hold_obj = NULL; }
	CKoopa* GetHoldObj() { return hold_obj; }
	int GetNX() { return nx; }
	bool CanAttack() { return level == MARIO_LEVEL_RACCOON && canAttack && !isSitting; }
	bool CanFly() { return level == MARIO_LEVEL_RACCOON && canFly && !isOnPlatform; }
	bool CanFloat() { return level == MARIO_LEVEL_RACCOON && !isFloating && !isOnPlatform; }
	bool NeedTracking() { return needTracking; }
	int GetPMeter() { return p_meter; }
};