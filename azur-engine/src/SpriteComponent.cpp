#include "SpriteComponent.h"

void SpriteComponent::init()
{
	this->position = entity->GetComponent<PositionComponent>();
}

void SpriteComponent::draw(SDL_Renderer* renderer)
{
	SDL_Rect dstrect;
	dstrect.x = int(position->x) + sprite->rect.x;
	dstrect.y = int(position->y) + sprite->rect.y;
	dstrect.w = sprite->rect.w;
	dstrect.h = sprite->rect.h;
	SDL_RenderCopy(renderer, sprite->texture, NULL, &dstrect);
}
