#include "Pipe.h"
#include "PlayScene.h"
#include "Mario.h"

CPipe::CPipe(float x, float y, float w, float h, float desX, float desY): CGameObject(x,y)
{
	width = w;
	height = h;
	this->desX = desX;
	this->desY = desY;
}

void CPipe::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - width / 2;
	t = y - height / 2;
	r = x + width / 2;
	b = y + height / 2;
}
