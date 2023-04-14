#ifndef _COMPONENTS_H
#define _COMPONENTS_H

#include <string>
#include <SDL.h>
#include <SDL_image.h>

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
	int setTexture(SDL_Renderer* renderer, const char* imageFileName, int x, int y, int w, int h)
	{
		const char* baseDir = SDL_GetBasePath();
		std::string fileDir = baseDir;
		fileDir += imageFileName;

		SDL_Surface* surface = IMG_Load(fileDir.c_str());
		if (surface == NULL)
		{
			std::cout << "IMG_Load failed: " << SDL_GetError() << "\n";
			return 1;
		}
		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
		if (texture == NULL)
		{
			std::cout << "SDL_CreateTextureFromSurface failed: " << SDL_GetError() << "\n";
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

public:
	SDL_Texture* texture;
	SDL_Rect rect;
};

#endif // _COMPONENTS_H
