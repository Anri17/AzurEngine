#include "TextComponent.h"

#include "AzurDebug.h"
#include "Application.h"

void TextComponent::init()
{
	message = "";
	texture = nullptr;
	rect = { 0, 0, 0, 0 };
	position = entity->GetComponent<PositionComponent>();
	color = { 0, 0, 0, 0 };
	size = 0;
	font = nullptr;
	renderer = Application::renderer;
};

TextComponent::~TextComponent()
{
	SDL_DestroyTexture(texture);
	TTF_CloseFont(font);
}

void TextComponent::draw(SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer, texture, NULL, &rect);
}

void TextComponent::update()
{
	BuildText();
}

void TextComponent::SetFont(std::string fontpath, int fontsize)
{
	TTF_CloseFont(font);
	this->size = fontsize;
	this->font = TTF_OpenFont(fontpath.c_str(), fontsize * FONT_RESOLUTION_RATIO);
	if (font == 0)
	{
		DEBUG_CONSOLE_LOG("Could Not Load Font: " << TTF_GetError());
	}
}

void TextComponent::SetColor(SDL_Color color)
{
	this->color = color;
}

void TextComponent::SetMessage(std::string message)
{
	this->message = message;
}

void TextComponent::BuildText()
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
