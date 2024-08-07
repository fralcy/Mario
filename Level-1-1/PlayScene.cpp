#include <iostream>
#include <fstream>
#include "AssetIDs.h"

#include "PlayScene.h"
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include "Portal.h"
#include "Coin.h"
#include "Platform.h"
#include "Shroom.h"
#include "Mysteryblock.h"
#include "Switchblock.h"
#include "Leaf.h"
#include "Tile.h"
#include "Line.h"
#include "Block.h"
#include "Venus.h"
#include "Fireball.h"
#include "Koopa.h"
#include "Pipe.h"
#include "Goal.h"
#include "Spawner.h"
#include "Hitbox.h"
#include "MapBound.h"
#include "Hub.h"
#include "SampleKeyEventHandler.h"

using namespace std;

CPlayScene::CPlayScene(int id, int world, LPCWSTR filePath):
	CScene(id, world, filePath)
{
	player = NULL;
	key_handler = new CSampleKeyHandler(this);
	cx = cy = 0;
	type = 2;
}


#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_ASSETS	1
#define SCENE_SECTION_OBJECTS	2

#define ASSETS_SECTION_UNKNOWN -1
#define ASSETS_SECTION_SPRITES 1
#define ASSETS_SECTION_ANIMATIONS 2

#define MAX_SCENE_LINE 1024

void CPlayScene::_ParseSection_SPRITES(string line)
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

void CPlayScene::_ParseSection_ASSETS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 1) return;

	wstring path = ToWSTR(tokens[0]);
	
	LoadAssets(path.c_str());
}

void CPlayScene::_ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	LPANIMATION ani = new CAnimation();

	int ani_id = atoi(tokens[0].c_str());
	for (int i = 1; i < tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time  
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[i+1].c_str());
		ani->Add(sprite_id, frame_time);
	}

	CAnimations::GetInstance()->Add(ani_id, ani);
}

/*
	Parse a line in section [OBJECTS] 
*/
void CPlayScene::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);
	
	// skip invalid lines - an object set must have at least id, x, y
	if (tokens.size() < 2) return;

	int object_type = atoi(tokens[0].c_str());
	float x = (float)atof(tokens[1].c_str());
	float y = (float)atof(tokens[2].c_str());

	CGameObject *obj = NULL;

	switch (object_type)
	{
	case OBJECT_TYPE_MARIO:
		//if (player!=NULL) 
		//{
		//	DebugOut(L"[ERROR] MARIO object was created before!\n");
		//	return;
		//}
	{
		int nx = atoi(tokens[3].c_str());
		int isMario = atoi(tokens[4].c_str());
		obj = new CMario(x, y, CGame::GetInstance()->GetMarioLevel(), nx, isMario);
		player = (CMario*)obj;
		DebugOut(L"[INFO] Player object has been created!\n");
		break;
	}
	case OBJECT_TYPE_GOOMBA: {
		int type = (int)atof(tokens[3].c_str());
		obj = new CGoomba(x, y, type);
		break;
	}
	case OBJECT_TYPE_BRICK: obj = new CBrick(x, y); switchableObjects.push_back(obj); break;
	case OBJECT_TYPE_COIN: obj = new CCoin(x, y, 1); break;
	case OBJECT_TYPE_MYSTERY_BLOCK: {
		int item = (int)atof(tokens[3].c_str());
		obj = new CMysteryBlock(x, y, item, MYSTERY_BLOCK_STATE_ACTIVE); 
		break; }
	case OBJECT_TYPE_SWITCH_BLOCK: {
		obj = new CSwitchBlock(x, y);
		break;
	}
	case OBJECT_TYPE_LEAF: obj = new CLeaf(x, y); break;
	case OBJECT_TYPE_TILE: {
		int spriteid = (int)atof(tokens[3].c_str());
		obj = new CTile(x, y, spriteid);
		break; }
	case OBJECT_TYPE_LINE: {
		int length = (int)atof(tokens[3].c_str());
		int spriteId = (int)atof(tokens[4].c_str());
		obj = new CLine(x, y, length, spriteId); break;
		break;
	}
	case OBJECT_TYPE_BLOCK:{
		int spriteid = (int)atof(tokens[3].c_str());
		obj = new CBlock(x, y, spriteid);
		break; }
	case OBJECT_TYPE_PLANT: {
		float vineLength = (float)(int)atof(tokens[3].c_str());
		int canFire = (int)atof(tokens[4].c_str());
		int headColor = (int)atof(tokens[5].c_str());
		obj = new CVenus(x, y, vineLength, canFire, headColor);
		break;
	}
	case OBJECT_TYPE_FIRE_BALL: {
		int dir = (int)atof(tokens[3].c_str());
		obj = new CFireball(x, y, dir);
		break;
	}
	case OBJECT_TYPE_KOOPA: {
		int color = (int)atof(tokens[3].c_str());
		int type = (int)atof(tokens[4].c_str());
		obj = new CKoopa(x, y, color, type); break;
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
	case OBJECT_TYPE_PIPE:
	{
		float w = (float)atof(tokens[3].c_str());
		float h = (float)atof(tokens[4].c_str());
		float desX = (float)atof(tokens[5].c_str());
		float desY = (float)atof(tokens[6].c_str());
		obj = new CPipe(x, y, w, h, desX, desY);
		break;
	}
	case OBJECT_TYPE_GOAL:
	{
		obj = new CGoal(x, y);
		break;
	}
	case OBJECT_TYPE_SPAWNER:
	{
		float r = (float)atof(tokens[3].c_str());
		float b = (float)atof(tokens[4].c_str());
		int obj_type = 0, p = 0, p2 = 0;
		float obj_x = 0, obj_y = 0;
		vector<LPGAMEOBJECT> objs;
		int obj_count = atoi(tokens[5].c_str()), i = 6, j = 0;
		for (; j < obj_count; j++)
		{
			obj_type = atoi(tokens[i++].c_str());
			obj_x = (float)atof(tokens[i++].c_str());
			obj_y = (float)atof(tokens[i++].c_str());
			switch (obj_type)
			{
			case OBJECT_TYPE_GOOMBA:
				p = atoi(tokens[i++].c_str());
				obj = new CGoomba(obj_x, obj_y, p);
				break;
			case OBJECT_TYPE_KOOPA:
				p = atoi(tokens[i++].c_str());
				p2 = atoi(tokens[i++].c_str());
				obj = new CKoopa(obj_x, obj_y, p, p2);
				break;
			}
			objs.push_back(obj);
		}
		obj = new CSpawner(x, y, r, b, objs);
	}
	break;
	case OBJECT_TYPE_MAPBOUND:
	{
		float r = (float)atof(tokens[3].c_str());
		float b = (float)atof(tokens[4].c_str());
		obj = new CMapBound(x, y, r, b);
	}
	break;
	case OBJECT_TYPE_PORTAL:
	{
		float r = (float)atof(tokens[3].c_str());
		float b = (float)atof(tokens[4].c_str());
		int scene_id = atoi(tokens[5].c_str());
		obj = new CPortal(x, y, r, b, scene_id);
	}
	break;
	case OBJECT_TYPE_HUB: {
		obj = new CHub(x, y);
		break;
	}
	default:
		DebugOut(L"[ERROR] Invalid object type: %d\n", object_type);
		return;
	}

	// General object setup
	obj->SetPosition(x, y);


		objects.push_back(obj);
}

void CPlayScene::LoadAssets(LPCWSTR assetFile)
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

void CPlayScene::Load()
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
		if (line == "[OBJECTS]") { section = SCENE_SECTION_OBJECTS; continue; };
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }	

		//
		// data section
		//
		switch (section)
		{ 
			case SCENE_SECTION_ASSETS: _ParseSection_ASSETS(line); break;
			case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
		}
	}

	f.close();
	if (!key_handler->IsEnabled()) key_handler->ToggleEnabled();
	CGame::GetInstance()->SetWorld(world);
	time = 300;
	DebugOut(L"[INFO] Done loading scene  %s\n", sceneFilePath);
}

void CPlayScene::Update(DWORD dt)
{
	// We know that Mario is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 

	vector<LPGAMEOBJECT> coObjects;
	for (size_t i = 0; i < objects.size(); i++)
	{
		if (!dynamic_cast<CMario*>(objects[i]))
		coObjects.push_back(objects[i]);
	}
	if (player->GetState() != MARIO_STATE_USING_PIPE && player->GetState() != MARIO_STATE_LEVEL_UP)
	{
		DebugOut(L"%d\n", player->GetState());
		for (size_t i = 0; i < objects.size(); i++)
		{
			objects[i]->Update(dt, &coObjects);
		}
	}
	else player->Update(dt, &coObjects);
	// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
	if (player == NULL) return; 

	if (player->GetState() != MARIO_STATE_DIE)
	{
		// Update camera to follow mario
		player->GetPosition(cx, cy);
		CGame* game = CGame::GetInstance();
		cx -= game->GetBackBufferWidth() / 2;
		cy -= game->GetBackBufferHeight() / 2;
		if (cx < 0) cx = 0;
		if (cx > 2585) cx = 2585;
		if (!player->NeedTracking() && cy <= 150 || cy > 0 && cy <= 150) cy = 0;
		else if (cy > 150 && cy < 295) cy = 230;
		if (cy < -240) cy = -240;
		if (cy == 230) cx = 2262;
	}
	//count time
	if (key_handler->IsEnabled())
	{
		if (GetTickCount64() - timer_tick > 1000)
		{
			time--;
			timer_tick = GetTickCount64();
		}
	}
	//kill mario when time's up
	if (time == 0)
	{
		player->SetState(MARIO_STATE_DIE);
	}

	CGame::GetInstance()->SetCamPos(cx, cy);

	PurgeDeletedObjects();
	StoreAddedbOjects();
}

void CPlayScene::Render()
{
	CHub* hub = NULL;
	CMario* mario = NULL;
	vector<CBlock*> block;
	vector<CGameObject*> items;
	vector<CGameObject*> itemblock;
	for (int i = 0; i < objects.size(); i++)
	{
		if (dynamic_cast<CHub*>(objects[i]))
		{
			hub = (CHub *)objects[i];
			continue;
		}
		if (dynamic_cast<CBlock*>(objects[i]))
		{
			block.push_back((CBlock*)objects[i]);
			continue;
		}
		if (dynamic_cast<CMario*>(objects[i]))
		{
			mario = (CMario*)objects[i];
			continue;
		}
		if (dynamic_cast<CShroom*>(objects[i]) || dynamic_cast<CLeaf*>(objects[i]) || dynamic_cast<CCoin*>(objects[i])|| dynamic_cast<CFireball*>(objects[i]))
		{
			items.push_back(objects[i]);
			continue;
		}
		if (abs(objects[i]->GetX() - cx) < 16 * 20 && abs(objects[i]->GetY() - cy) < 16 * 14 || dynamic_cast<CPlatform*>(objects[i]))
			objects[i]->Render();
	}
	mario->Render();
	for (int i = 0; i < block.size(); i++)
	{
		block[i]->Render();
	}
	for (int i = 0; i < items.size(); i++)
	{
		items[i]->Render();
	}
	hub->Render();
}

/*
*	Clear all objects from this scene
*/
void CPlayScene::Clear()
{
	vector<LPGAMEOBJECT>::iterator it;
	for (it = objects.begin(); it != objects.end(); it++)
	{
		delete (*it);
	}
	objects.clear();
}

/*
	Unload scene

	TODO: Beside objects, we need to clean up sprites, animations and textures as well 

*/
void CPlayScene::Unload()
{
	for (int i = 0; i < objects.size(); i++)
		delete objects[i];
	objects.clear();
	switchableObjects.clear();
	//player = NULL;
	CSprites::GetInstance()->Clear();
	CAnimations::GetInstance()->Clear();
	DebugOut(L"[INFO] Scene %d unloaded! \n", id);
}

void CPlayScene::AddObj(LPGAMEOBJECT obj)
{
	if (obj != NULL)
	{
		addedObjects.push_back(obj);
	}
}

bool CPlayScene::IsGameObjectDeleted(const LPGAMEOBJECT& o) { return o == NULL; }

void CPlayScene::DeletMapBound()
{
	//delete all map bound when ending play scene
	for (size_t i = 0; i < objects.size(); i++)
	{
		if (dynamic_cast<CMapBound*>(objects[i]))
			objects[i]->Delete();
	}
}

void CPlayScene::StoreAddedbOjects()
{
	for (int i = 0; i < addedObjects.size(); i++)
	{
		objects.push_back(addedObjects[i]);
	}
	addedObjects.clear();
}



void CPlayScene::PurgeDeletedObjects()
{
	vector<LPGAMEOBJECT>::iterator it;
	for (it = objects.begin(); it != objects.end(); it++)
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
	objects.erase(
		std::remove_if(objects.begin(), objects.end(), CPlayScene::IsGameObjectDeleted),
		objects.end());
}