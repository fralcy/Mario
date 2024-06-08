#include "Spawner.h"
#include "Game.h"
#include "PlayScene.h"
CSpawner::CSpawner(float x, float y, float w, float h, vector<LPGAMEOBJECT> objects)
{
	this->objects = objects;
	this->x = x;
	this->y = y;
	width = w;
	height = h;
}

void CSpawner::RenderBoundingBox()
{
	D3DXVECTOR3 p(x, y, 0);
	RECT rect;

	LPTEXTURE bbox = CTextures::GetInstance()->Get(ID_TEX_BBOX);

	float l, t, r, b;

	GetBoundingBox(l, t, r, b);
	rect.left = 0;
	rect.top = 0;
	rect.right = (int)r - (int)l;
	rect.bottom = (int)b - (int)t;

	float cx, cy;
	CGame::GetInstance()->GetCamPos(cx, cy);

	CGame::GetInstance()->Draw(x - cx, y - cy, bbox, nullptr, BBOX_ALPHA, rect.right - 1, rect.bottom - 1);
}

void CSpawner::Render()
{
	//RenderBoundingBox();
}

void CSpawner::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - width / 2;
	t = y - height / 2;
	r = x + width / 2;
	b = y + height / 2;
}

void CSpawner::SpawnEnemies()
{
	LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
	for (int i = 0; i < objects.size(); i++)
	{
		scene->AddObj(objects[i]);
	}
	objects.clear();
}