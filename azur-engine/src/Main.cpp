#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include <vector>

#include "GameObject.h"

#define WINDOW_WIDTH  640
#define WINDOW_HEIGHT 480

#define FPS_TARGET 60


// Game Related Objects
std::vector<GameObject*> gameObjects;


int main(int argc, char* argv[])
{
	// Init
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	IMG_Init(IMG_INIT_PNG);
	SDL_Window* window = SDL_CreateWindow("Azur Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_Event e;
	Uint64 current_frame = 0;
	bool application_is_running = true;
	

	// Game Related Objects
	GameObject* myGameObject = new GameObject();
	// TODO: IMG_Load is not working for some reason.
	SDL_Surface* surface = IMG_Load("89244799_p0.png");
	if (surface == NULL)
	{
		std::cout << "CreateRGBSurface failed: " << SDL_GetError() << "\n";
	}
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (texture == NULL)
	{
		std::cout << "CreateTextureFromSurface failed: " << SDL_GetError() << "\n";
	}
	myGameObject->texture = texture;
	SDL_FreeSurface(surface);
	surface = NULL;
	myGameObject->rect.w = 50;
	myGameObject->rect.h = 50;
	gameObjects.push_back(myGameObject);


	// FPS Calculations
	Uint32 previousTime = SDL_GetTicks();
	Uint32 currentTime = SDL_GetTicks();
	while (application_is_running)
	{
		// DEBUG MESSAGES
		std::cout << "CurrentFrame: " << current_frame << "\n";


		// SDL Event Processing
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				application_is_running = false;
			}
		}


		// Rendering
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 1);
		for (GameObject* gm : gameObjects)
		{
			SDL_RenderCopy(renderer, gm->texture, NULL, &gm->rect);
		}
		SDL_RenderPresent(renderer);


		// FPS Calculations
		currentTime = SDL_GetTicks();
		if (currentTime - previousTime < 1000.0f / FPS_TARGET)
		{
			SDL_Delay((Uint32)(1000.0f / FPS_TARGET) - currentTime + previousTime);
		}
		current_frame++;
		previousTime = SDL_GetTicks();
	}


	// Clear Memory
	for (GameObject* gm : gameObjects)
	{
		delete gm;
	}


	// Quit
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	TTF_Quit();
	IMG_Quit();

	return 0;
}