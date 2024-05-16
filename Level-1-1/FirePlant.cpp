#include "FirePlant.h"
#include "AssetIDs.h"
CFirePlant::CFirePlant(float x, float y):CGameObject::CGameObject(x,y)
{
}
void CFirePlant::Render()
{
	//Render head animations
	int headAniId = ID_ANI_PLANT_HEAD;
	CAnimations::GetInstance()->Get(headAniId)->Render(x, y);
	//Render vine
	CSprites* s = CSprites::GetInstance();
	int vineSprite = ID_SPRITE_PLANT_VINE;
	s->Get(vineSprite)->Draw(x, y + CELL_HEIGHT);
}
void CFirePlant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

}
void CFirePlant::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{

}