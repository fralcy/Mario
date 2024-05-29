#pragma once

#include "GameObject.h"

class CSpawner : public CGameObject
{
	float width;
	float height;
	vector<LPGAMEOBJECT> objects;
public:
	CSpawner(float l, float t, float r, float b, vector<LPGAMEOBJECT> objects);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);

	void RenderBoundingBox();
	int IsCollidable() { return (objects.size() > 0) ? 1 : 0; }
	int IsBlocking() { return 0; }

	void SpawnEnemies();
};