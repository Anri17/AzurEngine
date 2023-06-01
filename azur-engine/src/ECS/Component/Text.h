#ifndef _TEXT_COMPONENT_H
#define _TEXT_COMPONENT_H

#include <string>

#include <SDL_ttf.h>

#include ".\..\ECS_Component.h"

#include "Position.h"

namespace ECS
{
	class Text : public Component
	{
	public:
		~Text();

		void init() override;
		void update() override;
		void draw(SDL_Renderer* renderer) override;

		void SetFont(std::string fontpath, int fontsize);
		void SetColor(SDL_Color color);
		void SetMessage(std::string message);

		void BuildText();

		std::string message;
		SDL_Texture* texture;
		SDL_Rect rect;
		int size;
		TTF_Font* font;
		SDL_Color color;

		// Entity and Program References
		Position* position;
		SDL_Renderer* renderer;


	private:
		const int FONT_RESOLUTION_RATIO = 2;
	};
}

#endif // _TEXT_H