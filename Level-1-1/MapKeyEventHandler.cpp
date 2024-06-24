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
		int selectedSceneId = mario->GetCurrentNode()->GetSceneId();
		if (selectedSceneId != -1)
		{
			game->SetPrevMapNode(game->GetCurMapNode());
			game->SetCurMapNode(mario->GetCurrentNode()->GetId());
			game->InitiateSwitchScene(selectedSceneId);
		}
		break;
	}
}

void CMapKeyHandler::OnKeyUp(int KeyCode)
{

}