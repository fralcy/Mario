#pragma once
#include "GameObject.h"

class CPipe : public CGameObject
{
	float width, height;
	float desX, desY;
public:
	CPipe(float x, float y, float w, float h, float desX, float desY);
	virtual void Render() {
		RenderBoundingBox();
	}
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
	void GetDestinationPosition(float& x, float& y) { x = this->desX; y = this->desY; }
};