#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "AssetIDs.h"
#include "PlayScene.h"
class CHub: public CGameObject {
protected:
public:
	CHub(float x, float y) : CGameObject(x,y) {}
	void Render() {
		CSprites* s = CSprites::GetInstance();
		CAnimations* a = CAnimations::GetInstance();
		//get pos
		float cx, cy;
		CGame* g = CGame::GetInstance();
		g->GetCamPos(cx, cy);
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
		s->Get(ID_SPRITE_NUMBER + g->GetWorld())->Draw(x + 36, y + 1);
		//render life
		s->Get(ID_SPRITE_NUMBER + g->GetLife())->Draw(x + 36, y + 9);
		//render speed meter
		//render score
		int score = 1234567;
		for (int i = 1; i < 8; i++)
		{
			s->Get(ID_SPRITE_NUMBER + score % 10)->Draw(x + 108 - (8 * i), y + 9);
			score /= 10;
		}
		//render coin
		int coin = 45;
		s->Get(ID_SPRITE_NUMBER + coin / 10)->Draw(x + 132, y + 1);
		s->Get(ID_SPRITE_NUMBER + coin % 10)->Draw(x + 140, y + 1);
		//render time
		if (dynamic_cast<CPlayScene*>(g->GetCurrentScene()))
		{
			CPlayScene* scene = (CPlayScene*)(g->GetCurrentScene());
			int time = 300;
			for (int i = 1; i < 4; i++)
			{
				s->Get(ID_SPRITE_NUMBER + time % 10)->Draw(x + 148 - (8 * i), y + 9);
				time /= 10;
			}
		}
		//render collected cards
		s->Get(ID_SPRITE_SHROOM)->Draw(x + 168, y + 6);
		s->Get(ID_SPRITE_SHROOM)->Draw(x + 192, y + 6);
		s->Get(ID_SPRITE_SHROOM)->Draw(x + 216, y + 6);
	}
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b) {}
	int IsBlocking() { return 0; }
};