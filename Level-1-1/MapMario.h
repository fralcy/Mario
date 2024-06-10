#pragma once
#include "GameObject.h"
#define	MARIO_LEVEL_SMALL	1
#define	MARIO_LEVEL_BIG		2
#define MARIO_LEVEL_RACCOON 3

#define MAP_MARIO_SPEED 0.2f

#define ID_ANI_MAP_MAIRO_SMALL	3001
#define ID_ANI_MAP_MAIRO_BIG	3002
#define ID_ANI_MAP_MAIRO_RACCOON	3003
class CMapMario : public CGameObject
{
	int level;
	int selectedLevelId;
public:
	CMapMario(float x, float y, int level) : CGameObject(x, y) {
		this->level = level;
		selectedLevelId = 0;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	int IsBlocking() { return 0; }
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	void OnCollisionWithLevel(LPCOLLISIONEVENT e);
	int GetSelectedLevelId() { return selectedLevelId; }
};