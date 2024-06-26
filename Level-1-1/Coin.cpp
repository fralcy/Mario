#include "Coin.h"

CCoin::CCoin(float x, float y, int type):CGameObject(x, y)
{
	this->type = type;
	if (type == 0)
	{
		vy = -0.25f;
	}
}

void CCoin::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_COIN)->Render(x, y);

	//RenderBoundingBox();
}

void CCoin::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - COIN_BBOX_WIDTH / 2;
	t = y - COIN_BBOX_HEIGHT / 2;
	r = l + COIN_BBOX_WIDTH;
	b = t + COIN_BBOX_HEIGHT;
}

void CCoin::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (type == 0)
	{
		if (isfalling == false)
		{
			if (y > maxheight)
			{
				y += vy * dt;
			}
			else
			{
				isfalling = true;
				vy = -vy;
			}
		}
		else
		{
			if (y < maxheight + 32)
			{
				y += vy * dt;
			}
			else
			{
				Delete();
				return;
			}
		}
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}