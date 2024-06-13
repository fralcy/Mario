#pragma once
#include "GameObject.h"
#include "Node.h"
#define	MARIO_LEVEL_SMALL	1
#define	MARIO_LEVEL_BIG		2
#define MARIO_LEVEL_RACCOON 3

#define MAP_MARIO_SPEED 0.1f

#define ID_ANI_MAP_MAIRO_SMALL	3001
#define ID_ANI_MAP_MAIRO_BIG	3002
#define ID_ANI_MAP_MAIRO_RACCOON	3003
class CMapMario : public CGameObject
{
	int level;
	CNode* curNode, *nextNode;
public:
	CMapMario(float x, float y, int level, CNode* curNode) : CGameObject(x, y) {
		this->level = level;
		this->curNode = curNode;
		this->nextNode = NULL;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	int IsCollidable() { return 1; }
	int IsBlocking() { return 0; }
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	void OnCollisionWithNode(LPCOLLISIONEVENT e);
	CNode* GetCurrentNode() { return curNode; }
};