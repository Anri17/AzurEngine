#include "Sprite.h"

#include ".\..\Application.h"

void Sprite::Init()
{
	this->position = entity->GetComponent<Position>();
}

void Sprite::Render(SDL_Renderer* renderer)
{
	SDL_Rect dstrect;
	dstrect.x = Application::GetWindowTrueX(position->x + float(rect.x));
	dstrect.y = Application::GetWindowTrueY(position->y + float(rect.y));
	dstrect.w = Application::GetWindowTrueX(float(rect.w));
	dstrect.h = Application::GetWindowTrueY(float(rect.h));
	SDL_RenderCopy(renderer, texture, NULL, &dstrect);
}
