#ifndef _TEXT_H
#define _TEXT_H

#include <string>

#include <SDL_ttf.h>

struct Text
{
	Text(std::string fontpath, int fontsize, SDL_Color color);
	~Text();
	void FreeMemory();

	void Render(SDL_Renderer* renderer);

	void Set(SDL_Renderer* renderer, std::string fontpath, int fontsize, SDL_Color color);
	void Set(SDL_Renderer* renderer);
	void Set(SDL_Renderer* renderer, std::string message, int x, int y);

	std::string message;
	SDL_Texture* texture;
	SDL_Rect rect;
	int size;
	TTF_Font* font;
	SDL_Color color;
};

#endif // _TEXT_H