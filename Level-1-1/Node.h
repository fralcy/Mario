#pragma once
#include "GameObject.h"

class CNode: public CGameObject{
	int l, r, u, d;//1: can move, -1: blocked until level is completed, 0: doesn't exist
	int type; //-1: start, 0: normal, 1: level, special level
	bool isCompleted = false;
	int sceneId; //input trash value if node is not level
public:
	CNode(float x, float y, int l, int r, int u, int d, int type, int sceneId): CGameObject(x,y)
	{
		this->l = l;
		this->r = r;
		this->u = u;
		this->d = d;
		this->type = type;
		this->sceneId = sceneId;
	}
	void GetBoundingBox(float& l, float& t, float& r, float& b) {
		l = x - 16 / 2;
		t = y -	16 / 2;
		r = l + 16;
		b = t + 16;
	}
	void Render() { /*RenderBoundingBox();*/ }
	void GetMovableDirs(int& l, int& r, int& u, int& d)
	{
		l = this->l;
		r = this->r;
		u = this->u;
		d = this->d;
		if (type == 1 && isCompleted)
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
	void Complete() { isCompleted = true; }
	int GetType() { return type; }
	int GetSceneId() { if (type == 1) return sceneId; else return -1; }
};