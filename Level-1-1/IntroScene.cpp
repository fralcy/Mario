#include "Utils.h"
#include "debug.h"
#include "IntroScene.h"

void CIntroScene::_ParseSection_SPRITES(string line)
{
}

void CIntroScene::_ParseSection_ANIMATIONS(string line)
{
}

void CIntroScene::_ParseSection_ASSETS(string line)
{
}

void CIntroScene::_ParseSection_OBJECTS(string line)
{
}

void CIntroScene::LoadAssets(LPCWSTR assetFile)
{
}

CIntroScene::CIntroScene(int id, LPCWSTR filePath) : CScene(id, filePath)
{
	key_handler = new CIntroKeyHandler(this);
}

void CIntroScene::Load()
{
}

void CIntroScene::Update(DWORD dt)
{
}

void CIntroScene::Render()
{
}

void CIntroScene::Unload()
{
}
