#include "MysteryBlock.h"

void CMysteryBlock::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_MYSTERY_BLOCK)->Render(x, y);
	//RenderBoundingBox();
}

void CMysteryBlock::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - MYSTERY_BLOCK_BBOX_WIDTH / 2;
	t = y - MYSTERY_BLOCK_BBOX_HEIGHT / 2;
	r = l + MYSTERY_BLOCK_BBOX_WIDTH;
	b = t + MYSTERY_BLOCK_BBOX_HEIGHT;
}