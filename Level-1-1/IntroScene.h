#include "Textures.h"
#include "Scene.h"
#include "GameObject.h"
#include "Tile.h"
#include "Line.h"
#include "IntroKeyEventHandler.h"

#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_ASSETS	1
#define SCENE_SECTION_OBJECTS	2

#define ASSETS_SECTION_UNKNOWN -1
#define ASSETS_SECTION_SPRITES 1
#define ASSETS_SECTION_ANIMATIONS 2

#define MAX_SCENE_LINE 1024
class CIntroScene : public CScene
{
protected:
	bool is2player = false;
	vector<LPGAMEOBJECT> objects;

	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);

	void _ParseSection_ASSETS(string line);
	void _ParseSection_OBJECTS(string line);

	void LoadAssets(LPCWSTR assetFile);

public:
	CIntroScene(int id, LPCWSTR filePath);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	bool GetIs2Player() { return is2player; }
	void ToggleIs2Player() { is2player = !is2player; }
};

typedef CIntroScene* LPINTROSCENE;