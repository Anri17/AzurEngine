#include "Text.h"

#include "Debug.h"

Text::Text(std::string fontpath, int fontsize, SDL_Color color) : message(""), texture(nullptr), rect({ 0,0,0,0 })
{
	this->color = color;
	this->size = fontsize;
	this->font = TTF_OpenFont(fontpath.c_str(), fontsize);
	if (font == 0)
	{
		DEBUG_CONSOLE_LOG("Could Not Load Font: " << TTF_GetError());
	}
};
Text::~Text()
{
	SDL_DestroyTexture(texture);
	//TTF_CloseFont(font);
}

void Text::Render(SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer, texture, NULL, &rect);
}

void Text::Set(SDL_Renderer* renderer, std::string fontpath, int fontsize, SDL_Color color)
{
	TTF_CloseFont(font);
	this->color = color;
	this->size = fontsize;
	this->font = TTF_OpenFont(fontpath.c_str(), fontsize);
	if (font == 0)
	{
		std::cout << "Could Not Load Font: " << TTF_GetError() << "\n";
	}

	SDL_DestroyTexture(texture);
	SDL_Surface* surface = TTF_RenderText_Solid(font, message.c_str(), color);
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	rect.w = surface->w;
	rect.h = surface->h;
	SDL_FreeSurface(surface);
}
void Text::Set(SDL_Renderer* renderer)
{
	SDL_DestroyTexture(texture);
	SDL_Surface* surface = TTF_RenderText_Solid(font, message.c_str(), color);
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	rect.w = surface->w;
	rect.h = surface->h;
	SDL_FreeSurface(surface);
}
void Text::Set(SDL_Renderer* renderer, std::string message, int x, int y)
{
	this->message = message;
	this->rect.x = x;
	this->rect.y = y;

	SDL_DestroyTexture(texture);
	SDL_Surface* surface = TTF_RenderText_Solid(font, message.c_str(), color);
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	rect.w = surface->w;
	rect.h = surface->h;
	SDL_FreeSurface(surface);
}