#ifndef _SPRITE_COMPONENT_H
#define _SPRITE_COMPONENT_H

#include <string>
#include <SDL.h>
#include <SDL_image.h>

#include "AzurDebug.h"
#include "ECS.h"
#include "Components.h"

#include "Sprite.h"

class SpriteComponent : public Component
{
public:
	void init() override;
	void draw(SDL_Renderer* renderer) override;
public:
	Sprite* sprite;
	PositionComponent* position;
};


#endif // _SPRITE_COMPONENT_H