#include "PlayField.h"

#include ".\..\..\Application.h"

namespace ECS
{
	float PlayField::Top = 40;
	float PlayField::Right = 440;
	float PlayField::Bottom = 460;
	float PlayField::Left = 200;

	void PlayField::init()
	{
		playfield_rect.x = int(PlayField::Left);
		playfield_rect.y = int(PlayField::Top);
		playfield_rect.w = int(PlayField::Right - PlayField::Left);
		playfield_rect.h = int(PlayField::Bottom - PlayField::Top);
	}

	void PlayField::draw(SDL_Renderer* renderer)
	{
		SDL_Rect true_window_rect;
		true_window_rect.x = Application::GetWindowTrueX(playfield_rect.x);
		true_window_rect.y = Application::GetWindowTrueY(playfield_rect.y);
		true_window_rect.w = Application::GetWindowTrueX(playfield_rect.w);
		true_window_rect.h = Application::GetWindowTrueY(playfield_rect.h);
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 1); // while color for playfield
		SDL_RenderDrawRect(renderer, &true_window_rect);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 1); // black color for background
	}
}
