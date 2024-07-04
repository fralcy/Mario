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
void CIntroScene::_ParseSection_BACKGROUND(string line)
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
	case OBJECT_TYPE_TILE: {
		int spriteId = (int)atof(tokens[3].c_str());
		obj = new CTile(x, y, spriteId);
		break;
	}
	default:
		DebugOut(L"[ERROR] Invalid object type: %d\n", object_type);
		return;
	}
	background.push_back(obj);
}
void CIntroScene::_ParseSection_BACKGROUND2(string line)
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
	background2.push_back(obj);
}
void CIntroScene::_ParseSection_OBJECT(string line)
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
	case OBJECT_TYPE_GOOMBA: {
		int type = (int)atof(tokens[3].c_str());
		obj = new CGoomba(x, y, type);
		break;
	}
	case OBJECT_TYPE_KOOPA: {
		int color = (int)atof(tokens[3].c_str());
		int type = (int)atof(tokens[4].c_str());
		obj = new CKoopa(x, y, color, type); break;
		break;
	}
	case OBJECT_TYPE_LEAF: obj = new CLeaf(x, y); break;
	case OBJECT_TYPE_SHROOM: obj = new CShroom(x, y, -1, SHROOM_TYPE_RED); break;
	default:
		DebugOut(L"[ERROR] Invalid object type: %d\n", object_type);
		return;
	}
	objects.push_back(obj);
}
void CIntroScene::_ParseSection_OBJECT2(string line)
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
	case OBJECT_TYPE_KOOPA: {
		int color = (int)atof(tokens[3].c_str());
		int type = (int)atof(tokens[4].c_str());
		obj = new CKoopa(x, y, color, type);
		obj->SetSpeed(KOOPA_WALKING_SPEED, 0);
		break;
	}
	default:
		DebugOut(L"[ERROR] Invalid object type: %d\n", object_type);
		return;
	}
	objects2.push_back(obj);
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
	type = 0;
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
		if (line == "[BACKGROUND]") { section = SCENE_SECTION_BACKGROUND; continue; };
		if (line == "[BACKGROUND2]") { section = SCENE_SECTION_BACKGROUND2; continue; };
		if (line == "[OBJECT]") { section = SCENE_SECTION_OBJECT; continue; };
		if (line == "[OBJECT2]") { section = SCENE_SECTION_OBJECT2; continue; };
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
		case SCENE_SECTION_BACKGROUND: _ParseSection_BACKGROUND(line); break;
		case SCENE_SECTION_BACKGROUND2: _ParseSection_BACKGROUND2(line); break;
		case SCENE_SECTION_OBJECT: _ParseSection_OBJECT(line); break;
		case SCENE_SECTION_OBJECT2: _ParseSection_OBJECT2(line); break;
		}
	}

	f.close();
	time = 0;
	DebugOut(L"[INFO] Done loading scene  %s\n", sceneFilePath);
}

void CIntroScene::Update(DWORD dt)
{
	vector<LPGAMEOBJECT> coObjects;
	for (size_t i = 0; i < platform.size(); i++)
	{
		coObjects.push_back(platform[i]);
	}
	if (time >= 4.6f)
	{
		for (size_t i = 0; i < objects.size(); i++)
		{
			coObjects.push_back(objects[i]);
		}
		for (size_t i = 0; i < objects.size(); i++)
		{
			objects[i]->Update(dt, &coObjects);
		}
	}
	if (time >= 14.0f)
	{
		for (size_t i = 0; i < objects2.size(); i++)
		{
			coObjects.push_back(objects2[i]);
		}
		for (size_t i = 0; i < objects2.size(); i++)
		{
			objects2[i]->Update(dt, &coObjects);
		}
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
	if (time >= 4.6f && time <= 4.7f)
	{
		for (int i = 0; i < objects.size(); i++)
		{
			if (dynamic_cast<CKoopa*>(objects[i]))
				objects[i]->SetState(KOOPA_STATE_KNOCKED);
			if (dynamic_cast<CGoomba*>(objects[i]))
				objects[i]->SetSpeed(0, 0);
		}
	}
	if (time >= 7.35f && time <= 7.4f)
	{
		for (int i = 0; i < objects.size(); i++)
		{
			if (dynamic_cast<CKoopa*>(objects[i]))
				objects[i]->SetState(KOOPA_STATE_SHELL);
		}
		player2->SetState(MARIO_STATE_JUMP);
	}
	if (time >= 7.4f && time <= 7.45f)
	{
		player2->SetState(MARIO_STATE_RUNNING_LEFT);
	}
	if (time >= 7.5f && time <= 7.6f)
	{
		player2->SetState(MARIO_STATE_JUMP);
	}
	if (time >= 7.9f && time <= 7.95f)
	{
		player2->SetState(MARIO_STATE_WALKING_RIGHT);
	}
	if (time >= 9.1f && time <= 9.15f)
	{
		player2->SetState(MARIO_STATE_IDLE);
		player1->SetState(MARIO_STATE_WALKING_LEFT);
		player1->SetState(MARIO_STATE_IDLE);
		player1->SetPosition(player2->GetX() + 112, player2->GetY());
		for (int i = 0; i < objects.size(); i++)
		{
			if (dynamic_cast<CKoopa*>(objects[i]))
			{
				objects[i]->SetState(KOOPA_STATE_SHELL);
				objects[i]->SetPosition(player2->GetX() + 96, player2->GetY());
				break;
			}
		}
		player1->SetState(MARIO_STATE_RUNNING_LEFT);
	}
	if (time >= 9.5f && time <= 9.55f)
	{
		player1->SetState(MARIO_STATE_IDLE);
	}
	if (time >= 9.55f && time <= 9.6f)
	{
		player2->SetState(MARIO_STATE_WALKING_LEFT);
	}
	if (time >= 10.0f && time <= 10.05f)
	{
		player1->Throw();
	}
	if (time >= 10.15f && time <= 10.2f)
	{
		player2->SetState(MARIO_STATE_JUMP);
	}
	if (time >= 10.45f && time <= 10.5f)
	{
		player2->SetState(MARIO_STATE_WALKING_RIGHT);
	}
	if (time >= 10.55f && time <= 10.65f)
	{
		player1->SetState(MARIO_STATE_WALKING_RIGHT);
	}
	if (time >= 11.f && time <= 11.05f)
	{
		player2->SetState(MARIO_STATE_IDLE);
	}
	if (time >= 11.5f && time <= 11.55f)
	{
		for (int i = 0; i < objects.size(); i++)
		{
			if (dynamic_cast<CKoopa*>(objects[i]))
			{
				objects[i]->SetPosition(player2->GetX() - 112, player2->GetY());
				break;
			}
		}
	}
	if (time >= 11.5f && player2->GetLevel() == MARIO_LEVEL_BIG)
	{
		player2->SetLevel(MARIO_LEVEL_SMALL);
	}
	if (time >= 12.5f && time <= 12.55f)
	{
		player2->SetState(MARIO_STATE_RUNNING_RIGHT);
	}
	if (time >= 13.0f && time <= 13.05f)
	{
		player2->SetState(MARIO_STATE_RUNNING_LEFT);
	}
	if (time >= 13.5f && time <= 13.55f)
	{
		player2->SetState(MARIO_STATE_RUNNING_RIGHT);
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
	if (time >= 4.6f)
	{
		for (int i = 0; i < background.size(); i++)
		{
			background[i]->Render();
		}
	}
	if (time >= 3.5f)
	{
		for (int i = 0; i < title.size(); i++)
		{
			title[i]->Render();
		}
	}
	if (time >= 13.5f && player2)
	{
		player2->Render();
	}
	if (time >= 4.6f)
	{
		for (int i = 0; i < background2.size(); i++)
		{
			background2[i]->Render();
		}
	}
	if (time >= 4.6f)
	{
		for (int i = 0; i < objects.size(); i++)
		{
			objects[i]->Render();
		}
	}
	if (time >= 1 && player1) player1->Render();
	if (time >= 1 && time <= 13.5f && player2) player2->Render();
	if (time >= 14.0f)
	{
		for (int i = 0; i < objects2.size(); i++)
		{
			objects2[i]->Render();
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
	for (int i = 0; i < title.size(); i++)
		delete title[i];
	title.clear();
	for (int i = 0; i < background.size(); i++)
		delete background[i];
	background.clear();
	for (int i = 0; i < background2.size(); i++)
		delete background2[i];
	background2.clear();
	for (int i = 0; i < objects.size(); i++)
		delete objects[i];
	objects.clear();
	for (int i = 0; i < objects2.size(); i++)
		delete objects2[i];
	objects2.clear();
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
	curtain.erase(
		std::remove_if(curtain.begin(), curtain.end(), CIntroScene::IsGameObjectDeleted),
		curtain.end());

	for (it = objects.begin(); it != objects.end(); it++)
	{
		LPGAMEOBJECT o = *it;
		if (o->IsDeleted())
		{
			delete o;
			*it = NULL;
		}
	}
	objects.erase(
		std::remove_if(objects.begin(), objects.end(), CIntroScene::IsGameObjectDeleted),
		objects.end());

	for (it = objects2.begin(); it != objects2.end(); it++)
	{
		LPGAMEOBJECT o = *it;
		if (o->IsDeleted())
		{
			delete o;
			*it = NULL;
		}
	}
	objects2.erase(
		std::remove_if(objects2.begin(), objects2.end(), CIntroScene::IsGameObjectDeleted),
		objects2.end());
}