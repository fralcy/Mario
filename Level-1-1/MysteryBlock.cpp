#include "MysteryBlock.h"

CMysteryBlock::CMysteryBlock(float x, float y, int type, int state) : CGameObject(x, y)
{	
	this->type = type;
	this->state = state;
}
void CMysteryBlock::Render()
{
	int aniId = ID_ANI_MYSTERY_BLOCK;
	if (state == MYSTERY_BLOCK_STATE_DIE)
	{
		aniId = ID_ANI_MYSTERY_BLOCK_DIE;
	}
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CMysteryBlock::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - MYSTERY_BLOCK_BBOX_WIDTH / 2;
	t = y - MYSTERY_BLOCK_BBOX_HEIGHT / 2;
	r = l + MYSTERY_BLOCK_BBOX_WIDTH;
	b = t + MYSTERY_BLOCK_BBOX_HEIGHT;
}