#include "MapKeyEventHandler.h"

#include "debug.h"
#include "Game.h"

#include "MapMario.h"
#include "MapScene.h"

void CMapKeyHandler::KeyState(BYTE* states)
{

}

void CMapKeyHandler::OnKeyDown(int KeyCode)
{
	CGame* game = CGame::GetInstance();
	LPMAPSCENE scene = (LPMAPSCENE)game->GetCurrentScene();
	CMapMario* mario = (CMapMario*)scene->GetPlayer();
	int l, r, u, d;
	mario->GetCurrentNode()->GetMovableDirs(l, r, u, d);
	float x, y;
	mario->GetSpeed(x, y);
	if (x != 0 || y != 0)return;
	switch (KeyCode)
	{
	case DIK_LEFT:
		if (l == 1)
			mario->SetSpeed(-MAP_MARIO_SPEED, 0);
		break;
	case DIK_RIGHT:
		if (r == 1)
			mario->SetSpeed(MAP_MARIO_SPEED, 0);
		break;
	case DIK_UP:
		if (u == 1)
			mario->SetSpeed(0, -MAP_MARIO_SPEED);
		break;
	case DIK_DOWN:
		if (d == 1)
			mario->SetSpeed(0, MAP_MARIO_SPEED);
		break;
	case DIK_R:
		scene->Unload();
		scene->Load();
		break;
	case DIK_S:
		CNode* node = mario->GetCurrentNode();
		int selectedSceneId = node->GetSceneId();
		if (selectedSceneId != -1 && !game->isCompleted(node->GetId()))
		{
			game->SetPrevMapNode(game->GetCurMapNode());
			game->SetCurMapNode(node->GetId());
			game->InitiateSwitchScene(selectedSceneId);
		}
		break;
	}
}

void CMapKeyHandler::OnKeyUp(int KeyCode)
{

}