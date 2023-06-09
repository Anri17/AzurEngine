#ifndef _SPRITE_COMPONENT_H
#define _SPRITE_COMPONENT_H

#include <string>

#include <SDL.h>
#include <SDL_image.h>

#include ".\..\AzurLib.h"
#include ".\..\ECS.h"

#include "Position.h"

class Sprite : public Component
{
public:
	void Init() override;
	void Render(SDL_Renderer* renderer) override;
public:
	SDL_Texture* texture;
	SDL_Rect rect;
	Position* position;
};

#endif // _SPRITE_COMPONENT_H