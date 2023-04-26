#ifndef _COMPONENTS_H
#define _COMPONENTS_H

#include <string>
#include <SDL.h>
#include <SDL_image.h>

#include "Debug.h"
#include "ECS.h"

class PositionComponent : public Component
{
public:
	float x = 0.0f;
	float y = 0.0f;

	void init() override
	{
		x = 0.0f;
		y = 0.0f;
	}
};

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

#endif // _COMPONENTS_H
