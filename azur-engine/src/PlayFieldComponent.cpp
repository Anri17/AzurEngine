#include "PlayFieldComponent.h"

#include "Application.h"

float PlayFieldComponent::Top = 40;
float PlayFieldComponent::Right = 440;
float PlayFieldComponent::Bottom = 460;
float PlayFieldComponent::Left = 200;

void PlayFieldComponent::init()
{
	playfield_rect.x = int(PlayFieldComponent::Left);
	playfield_rect.y = int(PlayFieldComponent::Top);
	playfield_rect.w = int(PlayFieldComponent::Right - PlayFieldComponent::Left);
	playfield_rect.h = int(PlayFieldComponent::Bottom - PlayFieldComponent::Top);
}

void PlayFieldComponent::draw(SDL_Renderer* renderer)
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
