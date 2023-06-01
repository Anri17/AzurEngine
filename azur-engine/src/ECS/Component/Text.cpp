#include "Text.h"

#include ".\..\..\AzurLib.h"
#include ".\..\..\Application.h"

#include ".\..\..\AzurDebug.h"

namespace ECS
{
	void Text::init()
	{
		message = "";
		texture = nullptr;
		rect = { 0, 0, 0, 0 };
		position = entity->GetComponent<Position>();
		color = { 0, 0, 0, 0 };
		size = 0;
		font = nullptr;
		renderer = Application::renderer;
	};

	Text::~Text()
	{
		SDL_DestroyTexture(texture);
		TTF_CloseFont(font);
	}

	void Text::draw(SDL_Renderer* renderer)
	{
		SDL_RenderCopy(renderer, texture, NULL, &rect);
	}

	void Text::update()
	{
		BuildText();
	}

	void Text::SetFont(std::string fontpath, int fontsize)
	{
		TTF_CloseFont(font);
		this->size = fontsize;
		this->font = TTF_OpenFont(fontpath.c_str(), fontsize * FONT_RESOLUTION_RATIO);
		if (font == 0)
		{
			DEBUG_CONSOLE_LOG("Could Not Load Font: " << TTF_GetError());
		}
	}

	void Text::SetColor(SDL_Color color)
	{
		this->color = color;
	}

	void Text::SetMessage(std::string message)
	{
		this->message = message;
	}

	void Text::BuildText()
	{
		SDL_DestroyTexture(texture);
		SDL_Surface* surface = TTF_RenderText_Solid(font, message.c_str(), color);
		texture = SDL_CreateTextureFromSurface(renderer, surface);
		rect.x = Application::GetWindowTrueX(position->x);
		rect.y = Application::GetWindowTrueY(position->y);
		rect.w = Application::GetWindowTrueX(surface->w / FONT_RESOLUTION_RATIO);
		rect.h = Application::GetWindowTrueY(surface->h / FONT_RESOLUTION_RATIO);
		SDL_FreeSurface(surface);
	}
}
