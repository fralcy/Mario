#pragma once

#include "GameObject.h"

/*
	Object that triggers scene switching
*/
class CSpawner : public CGameObject
{
	float width;
	float height;
	vector<LPGAMEOBJECT> objects;
public:
	CSpawner(float l, float t, float r, float b, vector<LPGAMEOBJECT> objects);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);

	void RenderBoundingBox(void);

	int IsBlocking() { return 0; }
};