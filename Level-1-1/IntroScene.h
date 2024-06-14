#include "Scene.h"
#include "GameObject.h"
#include "Tile.h"
#include "Line.h"
#include "IntroKeyEventHandler.h"
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
};

typedef CIntroScene* LPINTROSCENE;