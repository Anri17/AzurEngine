#include "Sprite.h"

#include ".\..\..\Application.h"

namespace ECS
{
	void Sprite::init()
	{
		this->position = entity->GetComponent<Position>();
	}

	void Sprite::draw(SDL_Renderer* renderer)
	{
		SDL_Rect dstrect;
		dstrect.x = Application::GetWindowTrueX(int(position->x) + rect.x);
		dstrect.y = Application::GetWindowTrueY(int(position->y) + rect.y);
		dstrect.w = Application::GetWindowTrueX(rect.w);
		dstrect.h = Application::GetWindowTrueY(rect.h);
		SDL_RenderCopy(renderer, texture, NULL, &dstrect);
	}
}
