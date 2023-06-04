#ifndef _APPLICATION_H
#define _APPLICATION_H

#include <SDL.h>

#include "ECS.h"

struct Application
{
	static SDL_Window* window;
	static SDL_Renderer* renderer;

	static int Start(); // Return 0 if successul

	static int GetWindowTrueX(float x);
	static int GetWindowTrueY(float y);

	static const int base_window_width = 640;
	static const int base_window_height = 480;

	static int current_window_width;
	static int current_window_height;
	static float current_window_ratio;

	static std::vector<ECS::SystemBase*> systems;
};


#endif // _APPLICATION_H