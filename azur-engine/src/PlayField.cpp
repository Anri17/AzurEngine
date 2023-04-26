#include "PlayField.h"

float PlayField::Top = 40;
float PlayField::Right = 440;
float PlayField::Bottom = 460;
float PlayField::Left = 200;

PlayField::PlayField()
{
	playfield_rect.x = PlayField::Left;
	playfield_rect.y = PlayField::Top;
	playfield_rect.w = PlayField::Right - PlayField::Left;
	playfield_rect.h = PlayField::Bottom - PlayField::Top;
}

void PlayField::Render(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 1); // while color for playfield
	SDL_RenderDrawRect(renderer, &playfield_rect);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 1); // black color for background
}
