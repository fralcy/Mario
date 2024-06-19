#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "AssetIDs.h"

class CHub: public CGameObject {
protected:
public:
	CHub(float x, float y) : CGameObject(x,y) {}
	void Render() {
		CSprites* s = CSprites::GetInstance();
		//get pos
		float cx, cy;
		CGame::GetInstance()->GetCamPos(cx, cy);
		cx += 16;
		cy += 202;
		if (x != cx) x = cx;
		if (y != cy) y = cy;
		//render HUB's background
		for (int i = 0; i < 16; i++)
		{
			s->Get(ID_SPRITE_BLACK_BACKGROUND_MIDDLE)->Draw((x - 8) + 16 * i, y-2);
			s->Get(ID_SPRITE_BLACK_BACKGROUND_MIDDLE)->Draw((x - 8) + 16 * i, y+14);
		}
		for (int i = 0; i < 15; i++)
			s->Get(ID_SPRITE_HUB + i )->Draw(x+ 16 * i , y);
		for (int i = 0; i < 15; i++)
			s->Get(ID_SPRITE_HUB + i + 15)->Draw(x + 16 * i, y + 16);
		//render world map level
		s->Get(ID_SPRITE_NUMBER + CGame::GetInstance()->GetWorld())->Draw(x + 36, y + 1);
		//render life
		s->Get(ID_SPRITE_NUMBER + CGame::GetInstance()->GetLife())->Draw(x + 36, y + 9);
		//render speed meter
		//render score
		//render coin
		//render time
	}
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b) {}
	int IsBlocking() { return 0; }
};