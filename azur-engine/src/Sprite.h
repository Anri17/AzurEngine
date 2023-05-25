#ifndef _SPRITE_H
#define _SPRITE_H

#include <SDL.h>

struct Sprite
{
	SDL_Texture* texture;
	SDL_Rect rect;
};


#endif // _SPRITE_H