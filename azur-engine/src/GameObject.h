#ifndef _GAME_OBJECT_H
#define _GAME_OBJECT_H

#include <SDL_image.h>

class GameObject
{
public:
	GameObject();
	~GameObject();

public:
	SDL_Rect rect;
	float x;
	float y;
	SDL_Texture* texture;
};

#endif // _GAME_OBJECT_H