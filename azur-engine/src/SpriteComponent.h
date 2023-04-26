#ifndef _SPRITE_COMPONENT_H
#define _SPRITE_COMPONENT_H

#include <string>
#include <SDL.h>
#include <SDL_image.h>

#include "Debug.h"
#include "ECS.h"
#include "PositionComponent.h"

class SpriteComponent : public Component
{
public:
	// return 0 if sucessful
	int setTexture(PositionComponent* position, SDL_Renderer* renderer, const char* imageFileName, int x, int y, int w, int h);
	void draw(SDL_Renderer* renderer) override;

public:
	SDL_Texture* texture;
	SDL_Rect rect;
	PositionComponent* position;
};


#endif // _SPRITE_COMPONENT_H