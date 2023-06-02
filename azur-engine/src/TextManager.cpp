#include "TextManager.h"

#include "Application.h"

std::vector<std::pair<Position*, Text*>> TextManager::entities;
const int TextManager::FONT_RESOLUTION_RATIO = 2;

void TextManager::init()
{
}

void TextManager::update()
{
	for (auto e : entities)
	{
		Position* position = e.first;
		Text* text = e.second;
		BuildText(position, text);
	}
}

void TextManager::render(SDL_Renderer* renderer)
{
	for (auto e : entities)
	{
		SDL_RenderCopy(renderer, e.second->texture, NULL, &e.second->rect);
	}
}

void TextManager::BuildText(const Position* position, Text* text)
{
	SDL_DestroyTexture(text->texture);
	SDL_Surface* surface = TTF_RenderText_Solid(text->font, text->message.c_str(), text->color);
	text->texture = SDL_CreateTextureFromSurface(Application::renderer, surface);
	text->rect.x = Application::GetWindowTrueX(position->x);
	text->rect.y = Application::GetWindowTrueY(position->y);
	text->rect.w = Application::GetWindowTrueX(surface->w / FONT_RESOLUTION_RATIO);
	text->rect.h = Application::GetWindowTrueY(surface->h / FONT_RESOLUTION_RATIO);
	SDL_FreeSurface(surface);
}
