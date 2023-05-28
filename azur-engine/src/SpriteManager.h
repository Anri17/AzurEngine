#ifndef _SPRITE_MANAGER_H
#define _SPRITE_MANAGER_H

#include "Sprite.h"

class SpriteManager
{
public:
	static Sprite* bullet_a;
	static Sprite* player;
	static Sprite* blank_texture;

public:
	static void InitializeSprites();
	static void DeleteSprites();

private:
	static Sprite* CreateSprite(SDL_Renderer* renderer, const char* imageFileName, int x, int y, int w, int h);
};

#endif // _SPRITE_MANAGER_H
