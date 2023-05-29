#include "SpriteComponent.h"

#include "Application.h"

void SpriteComponent::init()
{
	this->position = entity->GetComponent<PositionComponent>();
}

void SpriteComponent::draw(SDL_Renderer* renderer)
{
	SDL_Rect dstrect;
	dstrect.x = Application::GetWindowTrueX(int(position->x) + sprite->rect.x);
	dstrect.y = Application::GetWindowTrueY(int(position->y) + sprite->rect.y);
	dstrect.w = Application::GetWindowTrueX(sprite->rect.w);
	dstrect.h = Application::GetWindowTrueY(sprite->rect.h);
	SDL_RenderCopy(renderer, sprite->texture, NULL, &dstrect);
}
