#include "Hitbox.h"
#include "PlayScene.h"
#include "Mario.h"
#include "Effect.h"

void CHitbox::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	if (GetTickCount64() - time_start > HITBOX_TIMEOUT)
		Delete();
	LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
	CMario* mario = (CMario*)scene->GetPlayer();
	if (vx > 0)
	{
		vx = HITBOX_SPEED + mario->GetVX();
	}
	else
	{
		vx = -HITBOX_SPEED + mario->GetVX();
	}
	vy = mario->GetVY();
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}
void CHitbox::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}
void CHitbox::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CFirePlant*>(e->obj))
		OnCollisionWithFirePlant(e);
	else if (dynamic_cast<CMysteryBlock*>(e->obj))
		OnCollisionWithMysteryBlock(e);
	else if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
	else if (dynamic_cast<CKoopa*>(e->obj))
		OnCollisionWithKoopa(e);
}
void CHitbox::OnCollisionWithFirePlant(LPCOLLISIONEVENT e)
{
	LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
	float x, y;
	e->obj->GetPosition(x, y);
	CEffect* hit = new CEffect(x, y, ID_SPRITE_HIT);
	scene->AddObj(hit);
	e->obj->Delete();
}
void CHitbox::OnCollisionWithMysteryBlock(LPCOLLISIONEVENT e)
{
	CMysteryBlock* mysteryblock = dynamic_cast<CMysteryBlock*>(e->obj);
	if (e->nx != 0 && mysteryblock->GetState() == MYSTERY_BLOCK_STATE_ACTIVE)
	{
		mysteryblock->SpawnItem((int)-e->nx);
	}
}
void CHitbox::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
	float x, y;
	e->obj->GetPosition(x, y);
	CEffect* hit = new CEffect (x, y, ID_SPRITE_HIT);
	scene->AddObj(hit);
	e->obj->Delete();
}
void CHitbox::OnCollisionWithKoopa(LPCOLLISIONEVENT e)
{
	LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
	CKoopa* koopa = (CKoopa*)e->obj;
	float x, y;
	koopa->GetPosition(x, y);
	CEffect* hit = new CEffect(x, y, ID_SPRITE_HIT);
	scene->AddObj(hit);
	koopa->SetState(KOOPA_STATE_KNOCKED);
	koopa->SetSpeed(KOOPA_KNOCKED_SPEED_X * -e->nx, -KOOPA_KNOCKED_SPEED_Y);
}