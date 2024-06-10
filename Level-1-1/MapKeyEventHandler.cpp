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
	LPMAPSCENE scene = (LPMAPSCENE)CGame::GetInstance()->GetCurrentScene();
	CMapMario* mario = (CMapMario*)scene->GetPlayer();
	switch (KeyCode)
	{
	case DIK_LEFT:
		mario->SetSpeed(-MAP_MARIO_SPEED, 0);
		break;
	case DIK_RIGHT:
		mario->SetSpeed(MAP_MARIO_SPEED, 0);
		break;
	case DIK_UP:
		mario->SetSpeed(0, -MAP_MARIO_SPEED);
		break;
	case DIK_DOWN:
		mario->SetSpeed(0, MAP_MARIO_SPEED);
		break;
	case DIK_R:
		scene->Unload();
		scene->Load();
		break;
	case DIK_S:
		int selectedLevelId = mario->GetSelectedLevelId();
		if (selectedLevelId != 0)
			CGame::GetInstance()->InitiateSwitchScene(selectedLevelId);
		break;
	}
}

void CMapKeyHandler::OnKeyUp(int KeyCode)
{

}