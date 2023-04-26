#include "PlayFieldComponent.h"

float PlayFieldComponent::Top = 40;
float PlayFieldComponent::Right = 440;
float PlayFieldComponent::Bottom = 460;
float PlayFieldComponent::Left = 200;

void PlayFieldComponent::init()
{
	playfield_rect.x = PlayFieldComponent::Left;
	playfield_rect.y = PlayFieldComponent::Top;
	playfield_rect.w = PlayFieldComponent::Right - PlayFieldComponent::Left;
	playfield_rect.h = PlayFieldComponent::Bottom - PlayFieldComponent::Top;
}

void PlayFieldComponent::draw(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 1); // while color for playfield
	SDL_RenderDrawRect(renderer, &playfield_rect);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 1); // black color for background
}
