#ifndef _TEXT_MANAGER_H
#define _TEXT_MANAGER_H

#include <vector>

#include "ECS.h"



class TextManager
{
public:
	static void Init();
	static void Update();
	static void Render(SDL_Renderer* renderer);

	static void BuildText(const Position* position, Text* text);
public:
	static std::vector<std::pair<Position*, Text*>> entities;

private:
	static const int FONT_RESOLUTION_RATIO;
};

#endif // _TEXT_MANAGER_H