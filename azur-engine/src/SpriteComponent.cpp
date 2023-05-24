#include "SpriteComponent.h"

// return 0 if sucessful
int SpriteComponent::setTexture(PositionComponent* position, SDL_Renderer* renderer, const char* imageFileName, int x, int y, int w, int h)
{
	// TODO: instead of creating a sprite for each component, create an class with preloaded asset textures, and use that to reference the needed texture for each of the bullet that uses it
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

void SpriteComponent::draw(SDL_Renderer* renderer)
{
	SDL_Rect dstrect;
	dstrect.x = int(position->x) + rect.x;
	dstrect.y = int(position->y) + rect.y;
	dstrect.w = rect.w;
	dstrect.h = rect.h;
	SDL_RenderCopy(renderer, texture, NULL, &dstrect);
}

SpriteComponent::~SpriteComponent()
{
	SDL_DestroyTexture(texture);
}
