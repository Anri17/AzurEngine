#ifndef _SPRITE_H
#define _SPRITE_H

#include <SDL.h>

struct SpriteData
{
	SDL_Texture* texture;
	SDL_Rect rect;
};

#endif // _SPRITE_H