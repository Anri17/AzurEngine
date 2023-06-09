#include "Text.h"

#include ".\..\AzurLib.h"
#include ".\..\Application.h"

#include ".\..\AzurDebug.h"

void Text::Init()
{
	message = "";
	texture = nullptr;
	rect = { 0, 0, 0, 0 };
	position = entity->GetComponent<Position>();
	color = { 0, 0, 0, 0 };
	size = 0;
	font = nullptr;
	renderer = Application::renderer;
	alignment = TextAlignment::LEFT;
};

Text::~Text()
{
	SDL_DestroyTexture(texture);
	TTF_CloseFont(font);
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

void Text::SetAlignment(TextAlignment alignment)
{
	this->alignment = alignment;
}
