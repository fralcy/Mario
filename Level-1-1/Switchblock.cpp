#include "Switchblock.h"
#include "AssetIDs.h"
#include "PlayScene.h"
void CSwitchBlock::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - 16 / 2;
	t = y - 16 / 2;
	r = l + 16;
	b = t + 16;
}
void CSwitchBlock::Render()
{
	int spriteId = 0;
	if (state == SWITCH_BLOCK_STATE_UNPRESSED)
		spriteId = ID_SPRITE_SWITCH_BLOCK;
	else
		spriteId = ID_SPRITE_SWITCH_BLOCK_PRESSED;
	CSprites* s = CSprites::GetInstance();
	s->Get(spriteId)->Draw(x, y);
}
void CSwitchBlock::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}
void CSwitchBlock::SwitchItem()
{
	return;
}