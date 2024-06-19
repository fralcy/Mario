#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scene.h"
#include "GameObject.h"
#include "Tile.h"
#include "Line.h"
#include "Block.h"
#include "Node.h"
#include "MapMario.h"
class CMapScene : public CScene
{
protected:
	// A play scene has to have player, right?
	CMapMario* player;
	vector<LPGAMEOBJECT> objects;

	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);

	void _ParseSection_ASSETS(string line);
	void _ParseSection_OBJECTS(string line);

	void LoadAssets(LPCWSTR assetFile);

public:
	CMapScene(int id, int world, LPCWSTR filePath);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	LPGAMEOBJECT GetPlayer() { return player; }
};

typedef CMapScene* LPMAPSCENE;