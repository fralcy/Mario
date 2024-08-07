#include "MysteryBlock.h"
#include "PlayScene.h"
#include "Shroom.h"
#include "Leaf.h"
#include "Coin.h"
#include "Switchblock.h"
#include "Brick.h"

CMysteryBlock::CMysteryBlock(float x, float y, int type, int state) : CGameObject(x, y)
{	
	this->type = type;
	this->state = state;
}
void CMysteryBlock::Render()
{
	int aniId = 0;
	if (state == MYSTERY_BLOCK_STATE_ACTIVE)
	{
        switch (type)
        {    
        case 0:
        case 1:
            aniId = ID_ANI_MYSTERY_BLOCK;
            break;
        case 2:
        case 3:
            aniId = ID_ANI_BRICK;
            break;
        }
	}
    else
    {
        aniId = ID_ANI_MYSTERY_BLOCK_DIE;
    }
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CMysteryBlock::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - MYSTERY_BLOCK_BBOX_WIDTH / 2;
	t = y - MYSTERY_BLOCK_BBOX_HEIGHT / 2;
	r = l + MYSTERY_BLOCK_BBOX_WIDTH;
	b = t + MYSTERY_BLOCK_BBOX_HEIGHT;
}
void CMysteryBlock::SpawnItem(int dir)
{
	CPlayScene* scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
	CMario* player = (CMario*)scene->GetPlayer();
    CGameObject* obj = NULL;
    SetState(MYSTERY_BLOCK_STATE_DIE);
    float x, y;
    GetPosition(x, y);
    if (type == 1)
    {
        if (player->GetLevel() == MARIO_LEVEL_SMALL)
        {
            obj = new CShroom(x, y, dir, SHROOM_TYPE_RED);
        }
        else
        {
            obj = new CLeaf(x, y);
        }
    }
    else if (type == 2)
    {
        obj = new CShroom(x, y, dir, SHROOM_TYPE_GREEN);
    }
    else if (type == 3)
    {
        obj = new CSwitchBlock(x, y - 16);
    }
    else
    {
        obj = new CCoin(x, y, 0);
        CGame* g = CGame::GetInstance();
        int coin = g->GetCoin();
        coin++;
        if (coin >= 100)
        {
            coin = 0;
            g->SetLife(g->GetLife() + 1);
        }
        g->SetCoin(coin);
        if (scene->GetType() == SCENE_TYPE_PLAY)
        {
            g->SetScore(g->GetScore() + 100);
        }
    }
    scene->AddObj(obj);
}