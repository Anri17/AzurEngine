#include "UISystem.h"

#include ".\..\Application.h"

std::vector<std::pair<Position*, Text*>> UISystem::entities;
const int UISystem::FONT_RESOLUTION_RATIO = 2;

UISystem::UISystem()
{
	Application::systems.push_back(this);
}

void UISystem::Init()
{

}

void UISystem::Update()
{
	for (auto e : entities)
	{
		Position* position = e.first;
		Text* text = e.second;
		BuildText(position, text);
	}
}

void UISystem::Render(SDL_Renderer* renderer)
{
	for (auto e : entities)
	{
		if (e.second->texture != nullptr)
			SDL_RenderCopy(renderer, e.second->texture, NULL, &e.second->rect);
	}
}

void UISystem::BuildText(const Position* position, Text* text)
{
	SDL_DestroyTexture(text->texture);
	SDL_Surface* surface = TTF_RenderText_Solid(text->font, text->message.c_str(), text->color);
	if (surface == nullptr)
	{
		text->rect.x = Application::GetWindowTrueX(position->x);
		text->rect.y = Application::GetWindowTrueY(position->y);
		text->rect.w = Application::GetWindowTrueX(0);
		text->rect.h = Application::GetWindowTrueY(0);
		text->texture = nullptr;
	}
	else if (text->alignment == TextAlignment::LEFT)
	{
		text->rect.x = (int)Application::GetWindowTrueX(position->x);
		text->rect.y = (int)Application::GetWindowTrueY(position->y);
		text->rect.w = (int)Application::GetWindowTrueX(surface->w / (float)FONT_RESOLUTION_RATIO);
		text->rect.h = (int)Application::GetWindowTrueY(surface->h / (float)FONT_RESOLUTION_RATIO);
		text->texture = SDL_CreateTextureFromSurface(Application::renderer, surface);
	}
	else if (text->alignment == TextAlignment::CENTER)
	{
		int full_w = int(surface->w / (float)FONT_RESOLUTION_RATIO);
		int half_w = int(full_w / 2.0f);

		text->rect.x = Application::GetWindowTrueX(position->x - half_w);
		text->rect.y = Application::GetWindowTrueY(position->y);
		text->rect.w = (int)Application::GetWindowTrueX(float(full_w));
		text->rect.h = Application::GetWindowTrueY(surface->h / (float)FONT_RESOLUTION_RATIO);
		text->texture = SDL_CreateTextureFromSurface(Application::renderer, surface);
	}
	else if (text->alignment == TextAlignment::RIGHT)
	{
		int full_w = surface->w / FONT_RESOLUTION_RATIO;

		text->rect.x = Application::GetWindowTrueX(position->x - full_w);
		text->rect.y = Application::GetWindowTrueY(position->y);
		text->rect.w = Application::GetWindowTrueX(0);
		text->rect.h = Application::GetWindowTrueY(surface->h / (float)FONT_RESOLUTION_RATIO);
		text->texture = SDL_CreateTextureFromSurface(Application::renderer, surface);
	}

	SDL_FreeSurface(surface);
}