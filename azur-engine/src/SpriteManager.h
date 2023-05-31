#ifndef _SPRITE_MANAGER_H
#define _SPRITE_MANAGER_H

#include "SpriteData.h"

class SpriteManager
{
public:
	static SpriteData* bullet_a;
	static SpriteData* player;
	static SpriteData* blank_texture;

public:
	static void InitializeSprites();
	static void DeleteSprites();

private:
	static SpriteData* CreateSprite(SDL_Renderer* renderer, const char* imageFileName, int x, int y, int w, int h);
};

#endif // _SPRITE_MANAGER_H
