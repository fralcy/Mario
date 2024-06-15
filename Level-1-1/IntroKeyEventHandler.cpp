#include "IntroKeyEventHandler.h"
#include "debug.h"
#include "Game.h"
#include "IntroScene.h"

void CIntroKeyHandler::KeyState(BYTE* states)
{

}

void CIntroKeyHandler::OnKeyDown(int KeyCode)
{
	LPINTROSCENE scene = (LPINTROSCENE)CGame::GetInstance()->GetCurrentScene();
	switch (KeyCode)
	{
	case DIK_Q:
		scene->ToggleIs2Player();
		break;
	case DIK_W:
		if (scene->GetIs2Player()) break;
		CGame::GetInstance()->InitiateSwitchScene(1);
		break;
	}
}

void CIntroKeyHandler::OnKeyUp(int KeyCode)
{

}
