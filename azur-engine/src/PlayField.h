#ifndef _PLAY_FIELD_H
#define _PLAY_FIELD_H

#include <SDL.h>

class PlayField
{
public:
	PlayField();
	void Render(SDL_Renderer* renderer);

	static float Top;
	static float Right;
	static float Bottom;
	static float Left;
private:
	SDL_Rect playfield_rect;
};

#endif // _PLAY_FIELD