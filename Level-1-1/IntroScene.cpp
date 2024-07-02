#include <iostream>
#include <fstream>
#include "Utils.h"
#include "debug.h"
#include "IntroScene.h"
#include "AssetIDs.h"


void CIntroScene::_ParseSection_SPRITES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 6) return; // skip invalid lines

	int ID = atoi(tokens[0].c_str());
	int l = atoi(tokens[1].c_str());
	int t = atoi(tokens[2].c_str());
	int r = atoi(tokens[3].c_str());
	int b = atoi(tokens[4].c_str());
	int texID = atoi(tokens[5].c_str());

	LPTEXTURE tex = CTextures::GetInstance()->Get(texID);
	if (tex == NULL)
	{
		DebugOut(L"[ERROR] Texture ID %d not found!\n", texID);
		return;
	}

	CSprites::GetInstance()->Add(ID, l, t, r, b, tex);
}

void CIntroScene::_ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	LPANIMATION ani = new CAnimation();

	int ani_id = atoi(tokens[0].c_str());
	for (int i = 1; i < tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time  
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[i + 1].c_str());
		ani->Add(sprite_id, frame_time);
	}

	CAnimations::GetInstance()->Add(ani_id, ani);
}

void CIntroScene::_ParseSection_ASSETS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 1) return;

	wstring path = ToWSTR(tokens[0]);

	LoadAssets(path.c_str());
}

void CIntroScene::_ParseSection_PLATFORM(string line)
{
	vector<string> tokens = split(line);

	// skip invalid lines - an object set must have at least id, x, y
	if (tokens.size() < 2) return;

	int object_type = atoi(tokens[0].c_str());
	float x = (float)atof(tokens[1].c_str());
	float y = (float)atof(tokens[2].c_str());
	CGameObject* obj = NULL;

	switch (object_type)
	{
	case OBJECT_TYPE_TILE: {
		int spriteid = (int)atof(tokens[3].c_str());
		obj = new CTile(x, y, spriteid);
		break;
	}
	case OBJECT_TYPE_BLOCK: {
		int spriteid = (int)atof(tokens[3].c_str());
		obj = new CBlock(x, y, spriteid);
		break;
	}

	case OBJECT_TYPE_LINE: {
		int length = (int)atof(tokens[3].c_str());
		int spriteId = (int)atof(tokens[4].c_str());
		obj = new CLine(x, y, length, spriteId); break;
		break;
	}
	case OBJECT_TYPE_PLATFORM:
	{

		float cell_width = (float)atof(tokens[3].c_str());
		float cell_height = (float)atof(tokens[4].c_str());
		int length = atoi(tokens[5].c_str());
		int sprite_begin = atoi(tokens[6].c_str());
		int sprite_middle = atoi(tokens[7].c_str());
		int sprite_end = atoi(tokens[8].c_str());

		obj = new CPlatform(
			x, y,
			cell_width, cell_height, length,
			sprite_begin, sprite_middle, sprite_end
		);

		break;
	}
	default:
		DebugOut(L"[ERROR] Invalid object type: %d\n", object_type);
		return;
	}
	platform.push_back(obj);
}
void CIntroScene::_ParseSection_CURTAIN(string line)
{
	vector<string> tokens = split(line);

	// skip invalid lines - an object set must have at least id, x, y
	if (tokens.size() < 2) return;

	int object_type = atoi(tokens[0].c_str());
	float x = (float)atof(tokens[1].c_str());
	float y = (float)atof(tokens[2].c_str());
	CGameObject* obj = NULL;

	switch (object_type)
	{
	case OBJECT_TYPE_LINE: {
		int length = (int)atof(tokens[3].c_str());
		int spriteId = (int)atof(tokens[4].c_str());
		obj = new CLine(x, y, length, spriteId); break;
		break;
	}
	default:
		DebugOut(L"[ERROR] Invalid object type: %d\n", object_type);
		return;
	}
	curtain.push_back(obj);
}
void CIntroScene::_ParseSection_PLAYER(string line)
{
	vector<string> tokens = split(line);

	// skip invalid lines - an object set must have at least id, x, y
	if (tokens.size() < 2) return;

	int object_type = atoi(tokens[0].c_str());
	float x = (float)atof(tokens[1].c_str());
	float y = (float)atof(tokens[2].c_str());
	int level = atoi(tokens[3].c_str());
	int nx = atoi(tokens[4].c_str());
	int isMario = atoi(tokens[5].c_str());
	CMario* obj = NULL;

	switch (object_type)
	{
	case OBJECT_TYPE_MARIO:
	{
		obj = new CMario(x, y, level, nx, isMario);
		break;
	}
	default:
		DebugOut(L"[ERROR] Invalid object type: %d\n", object_type);
		return;
	}
	if (player1 == NULL)
		player1 = obj;
	else
		player2 = obj;
}
void CIntroScene::_ParseSection_TITLE(string line)
{
	vector<string> tokens = split(line);

	// skip invalid lines - an object set must have at least id, x, y
	if (tokens.size() < 2) return;

	int object_type = atoi(tokens[0].c_str());
	float x = (float)atof(tokens[1].c_str());
	float y = (float)atof(tokens[2].c_str());
	CGameObject* obj = NULL;

	switch (object_type)
	{
	case OBJECT_TYPE_TILE: {
		int spriteId = (int)atof(tokens[3].c_str());
		obj = new CTile(x, y, spriteId);
		break;
	}
	default:
		DebugOut(L"[ERROR] Invalid object type: %d\n", object_type);
		return;
	}
	title.push_back(obj);
}
void CIntroScene::LoadAssets(LPCWSTR assetFile)
{
	DebugOut(L"[INFO] Start loading assets from : %s \n", assetFile);

	ifstream f;
	f.open(assetFile);

	int section = ASSETS_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[SPRITES]") { section = ASSETS_SECTION_SPRITES; continue; };
		if (line == "[ANIMATIONS]") { section = ASSETS_SECTION_ANIMATIONS; continue; };
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case ASSETS_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
		case ASSETS_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
		}
	}

	f.close();

	DebugOut(L"[INFO] Done loading assets from %s\n", assetFile);
}

CIntroScene::CIntroScene(int id, int world, LPCWSTR filePath) : CScene(id, world, filePath)
{
	key_handler = new CIntroKeyHandler(this);
}

void CIntroScene::Load()
{
	DebugOut(L"[INFO] Start loading scene from : %s \n", sceneFilePath);

	ifstream f;
	f.open(sceneFilePath);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	
		if (line == "[ASSETS]") { section = SCENE_SECTION_ASSETS; continue; };
		if (line == "[PLATFORM]") { section = SCENE_SECTION_PLATFORM; continue; };
		if (line == "[CURTAIN]") { section = SCENE_SECTION_CURTAIN; continue; };
		if (line == "[PLAYER]") { section = SCENE_SECTION_PLAYER; continue; };
		if (line == "[TITLE]") { section = SCENE_SECTION_TITLE; continue; };
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case SCENE_SECTION_ASSETS: _ParseSection_ASSETS(line); break;
		case SCENE_SECTION_PLATFORM: _ParseSection_PLATFORM(line); break;
		case SCENE_SECTION_CURTAIN: _ParseSection_CURTAIN(line); break;
		case SCENE_SECTION_PLAYER: _ParseSection_PLAYER(line); break;
		case SCENE_SECTION_TITLE: _ParseSection_TITLE(line); break;
		}
	}

	f.close();

	DebugOut(L"[INFO] Done loading scene  %s\n", sceneFilePath);
}

void CIntroScene::Update(DWORD dt)
{
	vector<LPGAMEOBJECT> coObjects;
	for (size_t i = 0; i < platform.size(); i++)
	{
		coObjects.push_back(platform[i]);
	}
	if (player1) player1->Update(dt, &coObjects);
	if (player2) player2->Update(dt, &coObjects);
	CGame::GetInstance()->SetCamPos(0, 0);
	if (GetTickCount64() - timer_tick > 50)
	{
		time += 0.05f;
		timer_tick = GetTickCount64();
	}
	for (int i = 0; i < curtain.size(); i++)
	{
		float x, y;
		curtain[i]->GetPosition(x, y);
		curtain[i]->SetPosition(x, y - 1.6f);
		if (y < -8) curtain[i]->Delete();
	}
	if (time >= 2.0f && time <=2.1f)
	{
		player1->SetState(MARIO_STATE_WALKING_RIGHT);
		player2->SetState(MARIO_STATE_WALKING_LEFT);
	}
	if (time >= 2.8f && time <=2.9f)
	{
		player1->SetState(MARIO_STATE_JUMP);
	}
	if (time >= 3.1f && time <= 3.15f)
	{
		player2->SetPosition(player2->GetX(), player2->GetY() - 2);
		player2->SetState(MARIO_STATE_SIT);
	}
	if (time >= 3.15f && time <= 3.2f)
	{
		player1->SetState(MARIO_STATE_HIGH_JUMP);
	}
	if (time >= 3.45f && time <= 3.5f)
	{
		player2->SetState(MARIO_STATE_SIT_RELEASE);
	}
	if (time >= 3.5f && title[0]->GetY()<=32)
	{
		for (int i = 0; i < title.size(); i++)
		{
			title[i]->SetPosition(title[i]->GetX(), title[i]->GetY() + 1.6f);
		}
	}
	DebugOutTitle(L"%f", time);
	PurgeDeletedObjects();
}

void CIntroScene::Render()
{
	for (int i = 0; i < platform.size(); i++)
	{
		platform[i]->Render();
	}
	for (int i = 0; i < curtain.size(); i++)
	{
		curtain[i]->Render();
	}
	if (time >= 1 && player1) player1->Render();
	if (time >= 1 && player2) player2->Render();
	if (time >= 3.5f)
	{
		for (int i = 0; i < title.size(); i++)
		{
			title[i]->Render();
		}
	}
	//float x = 72, y;
	//if (!is2player)
	//{
	//	y = 150;
	//}
	//else
	//{
	//	y = 166;
	//}
	//CSprites::GetInstance()->Get(ID_SPRITE_INTRO_POINTER)->Draw(x ,y);
}

void CIntroScene::Unload()
{
	for (int i = 0; i < platform.size(); i++)
		delete platform[i];
	platform.clear();

	for (int i = 0; i < curtain.size(); i++)
		delete curtain[i];
	curtain.clear();
	player1 = NULL;
	player2 = NULL;
	CSprites::GetInstance()->Clear();
	CAnimations::GetInstance()->Clear();
	DebugOut(L"[INFO] Scene %d unloaded! \n", id);
}
void CIntroScene::PurgeDeletedObjects()
{
	vector<LPGAMEOBJECT>::iterator it;
	for (it = curtain.begin(); it != curtain.end(); it++)
	{
		LPGAMEOBJECT o = *it;
		if (o->IsDeleted())
		{
			delete o;
			*it = NULL;
		}
	}

	// NOTE: remove_if will swap all deleted items to the end of the vector
	// then simply trim the vector, this is much more efficient than deleting individual items
	curtain.erase(
		std::remove_if(curtain.begin(), curtain.end(), CIntroScene::IsGameObjectDeleted),
		curtain.end());
}