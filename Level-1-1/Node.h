#pragma once
#include "GameObject.h"
#include "AssetIDs.h"

class CNode: public CGameObject{
	int l, r, u, d;//1: can move, -1: blocked until level is completed, 0: doesn't exist
	int id; //-1: empty, 0: start, 1,2,3,...: normal level
	int sceneId; //input -1 value if node is not level
public:
	CNode(float x, float y, int l, int r, int u, int d, int id, int sceneId): CGameObject(x,y)
	{
		this->l = l;
		this->r = r;
		this->u = u;
		this->d = d;
		this->id = id;
		this->sceneId = sceneId;
	}
	void GetBoundingBox(float& l, float& t, float& r, float& b) {
		l = x - 16 / 2;
		t = y -	16 / 2;
		r = l + 16;
		b = t + 16;
	}
	void Render() 
	{ 
		if (id >= 1 && id <= 6)
		{
			CSprites* s = CSprites::GetInstance();
			if (!CGame::GetInstance()->isCompleted(id))
			{
				s->Get(ID_SPRITE_MAP_LEVEL + 100 * id)->Draw(x, y);
			}
			else
			{

			}
		}
		/*RenderBoundingBox();*/
	}
	void GetMovableDirs(int& l, int& r, int& u, int& d)
	{
		l = this->l;
		r = this->r;
		u = this->u;
		d = this->d;
		if (id >= 1 && id <= 6 && CGame::GetInstance()->isCompleted(id))
		{
			if (l == -1) l = 1;
			if (r == -1) r = 1;
			if (u == -1) u = 1;
			if (d == -1) d = 1;
		}
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
	{
		CGameObject::Update(dt, coObjects);
		CCollision::GetInstance()->Process(this, dt, coObjects);
	}
	int IsBlocking() { return 0; }
	int GetId() { return id; }
	int GetSceneId() { if (id >= 1) return sceneId; else return -1; }
};