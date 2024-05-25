#include "Hitbox.h"
#include "debug.h"

void CHitbox::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	if (GetTickCount64() - time_start > HITBOX_TIMEOUT)
		Delete();
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
	if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
	else if (dynamic_cast<CKoopa*>(e->obj))
		OnCollisionWithKoopa(e);
	else if (dynamic_cast<CFirePlant*>(e->obj))
		OnCollisionWithFirePlant(e);
	else if (dynamic_cast<CMysteryBlock*>(e->obj))
		OnCollisionWithMysteryBlock(e);
}
void CHitbox::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	e->obj->Delete();
}
void CHitbox::OnCollisionWithKoopa(LPCOLLISIONEVENT e)
{
	e->obj->Delete();
}
void CHitbox::OnCollisionWithFirePlant(LPCOLLISIONEVENT e)
{
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