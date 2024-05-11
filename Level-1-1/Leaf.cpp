#include "Leaf.h"
#include <cmath>
#define M_PI 3.14159265358979323846
CLeaf::CLeaf(float x, float y):CGameObject(x, y)
{
	starttime = 0;
	time = 0;
}

void CLeaf::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_LEAF)->Render(x, y);
	//RenderBoundingBox();
}

void CLeaf::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - LEAF_BBOX_WIDTH / 2;
	t = y - LEAF_BBOX_HEIGHT / 2;
	r = l + LEAF_BBOX_WIDTH;
	b = t + LEAF_BBOX_HEIGHT;
}

void CLeaf::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isspawning)
	{
		if (y > maxheight)
		{
			y -= 0.05f * dt;
		}
		else
		{
			isspawning = false;
			vy = LEAF_FALL_SPEED;
			starttime = GetTickCount64();
		}
}
	else
	{
		time = GetTickCount64() - starttime;
		y += vy * dt;
		x = float(LEAF_AMPLITUDE * cos((2 * M_PI * LEAF_FREQUENCY) * time + M_PI) + (x0 + LEAF_AMPLITUDE));
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}
