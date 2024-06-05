#pragma once

#include "GameObject.h"

class CMapBound : public CGameObject
{
	float width;
	float height;
public:
	CMapBound(float x, float y, float w, float h);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);

	void RenderBoundingBox();

	int IsBlocking() { return 0; }
};