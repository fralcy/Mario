#include "Tile.h"

#include "Sprite.h"
#include "Sprites.h"

void CTile::Render()
{
	CSprites* s = CSprites::GetInstance();
	s->Get(this->spriteId)->Draw(x, y);
}