#ifndef _APPLICATION_H
#define _APPLICATION_H

#include <SDL.h>

struct Application
{
	static SDL_Window* window;
	static SDL_Renderer* renderer;

	static int Start(); // Return 0 if successul
};


#endif // _APPLICATION_H