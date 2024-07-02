#include "Textures.h"
#include "Scene.h"
#include "GameObject.h"
#include "Tile.h"
#include "Line.h"
#include "Mario.h"
#include "Platform.h"
#include "Block.h"
#include "IntroKeyEventHandler.h"

#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_ASSETS	1
#define SCENE_SECTION_PLATFORM	2
#define SCENE_SECTION_CURTAIN	3
#define SCENE_SECTION_PLAYER	4
#define SCENE_SECTION_TITLE		5

#define ASSETS_SECTION_UNKNOWN -1
#define ASSETS_SECTION_SPRITES 1
#define ASSETS_SECTION_ANIMATIONS 2

#define MAX_SCENE_LINE 1024
class CIntroScene : public CScene
{
protected:
	bool is2player = false;
	vector<LPGAMEOBJECT> platform;
	vector<LPGAMEOBJECT> curtain;
	CMario* player1;
	CMario* player2;
	vector<LPGAMEOBJECT> title;
	vector<LPGAMEOBJECT> gamemode;
	LPGAMEOBJECT pointer;
	float time = 0;
	ULONGLONG timer_tick = GetTickCount64();
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);

	void _ParseSection_ASSETS(string line);
	void _ParseSection_PLATFORM(string line);
	void _ParseSection_CURTAIN(string line);
	void _ParseSection_PLAYER(string line);
	void _ParseSection_TITLE(string line);

	void LoadAssets(LPCWSTR assetFile);

public:
	CIntroScene(int id, int world, LPCWSTR filePath);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();
	static bool IsGameObjectDeleted(const LPGAMEOBJECT& o) { return o == NULL; }
	void PurgeDeletedObjects();
	bool GetIs2Player() { return is2player; }
	void ToggleIs2Player() { is2player = !is2player; }
};

typedef CIntroScene* LPINTROSCENE;