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
	int setTexture(PositionComponent* position, SDL_Renderer* renderer, const char* imageFileName, int x, int y, int w, int h)
	{
		this->position = position;

		const char* baseDir = SDL_GetBasePath();
		std::string fileDir = baseDir;
		fileDir += imageFileName;

		SDL_Surface* surface = IMG_Load(fileDir.c_str());
		if (surface == NULL)
		{
			DEBUG_CONSOLE_LOG("IMG_Load failed: " << SDL_GetError());
			return 1;
		}
		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
		if (texture == NULL)
		{
			DEBUG_CONSOLE_LOG("SDL_CreateTextureFromSurface failed: " << SDL_GetError());
			return 1;
		}
		this->texture = texture;
		SDL_FreeSurface(surface);
		rect.x = x;
		rect.y = y;
		rect.w = w;
		rect.h = h;

		return 0;
	}

	void draw(SDL_Renderer* renderer) override
	{
		SDL_Rect dstrect;
		dstrect.x = position->x + rect.x;
		dstrect.y = position->y + rect.y;
		dstrect.w = rect.w;
		dstrect.h = rect.h;
		SDL_RenderCopy(renderer, texture, NULL, &dstrect);
	}

public:
	SDL_Texture* texture;
	SDL_Rect rect;
	PositionComponent* position;
};

#endif // _COMPONENTS_H
