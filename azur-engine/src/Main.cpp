#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <vector>
#include <map>
#include <cstring>

// Engine
#include "Debug.h"
#include "Mouse.h"
#include "InputHandler.h"
#include "Text.h"

// Game
#include "ECSEntities.h"


#define WINDOW_WIDTH  640
#define WINDOW_HEIGHT 480

#define FPS_TARGET 60

#define INPUT_MANAGER_KEY_COUNT 1024


// Game Related Objects
std::vector<Entity*>	 entities;


// All the bullets
std::vector<Bullet*> bullets;

int main(int argc, char* argv[])
{
	// Initialise SDL, TTF, IMG
	SDL_Init(SDL_INIT_EVERYTHING);
	if (TTF_Init() == -1)
	{
		DEBUG_CONSOLE_LOG("TTF_Init: " << TTF_GetError());
		exit(-1);
	}
	IMG_Init(IMG_INIT_PNG);


	// Create Window, Renderer & Event
	SDL_Window* window = SDL_CreateWindow("Azur Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_Event e; // used for input events
	
	// The running state of the applications
	bool application_is_running = true;
	

	// Initialise Text For Debuging
	std::string basepath = SDL_GetBasePath();
	std::string fontname = "SpaceMono-Regular.ttf";
	std::string fontpath = basepath + fontname;
	int fontsize = 12;
	SDL_Color message_color = { 255, 255, 255 };
	Text msg_current_frame(fontpath, fontsize, message_color);
	Text msg_mouse_x(fontpath, fontsize, message_color);
	Text msg_mouse_y(fontpath, fontsize, message_color);
	Text msg_player_x(fontpath, fontsize, message_color);
	Text msg_player_y(fontpath, fontsize, message_color);


	// Initialise Mouse
	Mouse mouse;
	// Initialise PlayField
	PlayField playField;


	// Initialise Player with ECS
	Player* player = new Player(renderer);
	// Save the ESC components
	entities.push_back(player);


	// FPS Calculation Variables
	Uint64 current_frame = 0;
	Uint32 previousTime = SDL_GetTicks();
	Uint32 currentTime = SDL_GetTicks();


	// The Application Loop
	while (application_is_running)
	{
		// Abstract SDL events into engine components and systems
		// Reset First Tap Event
		// First Tap variables of the InputHandler are only true on the first frame when the keys are pressed.
		InputHandler::firstTap_W = false;
		InputHandler::firstTap_A = false;
		InputHandler::firstTap_S = false;
		InputHandler::firstTap_D = false;
		InputHandler::firstTap_Z = false;

		InputHandler::firstTap_LSHIFT = false;
		InputHandler::firstTap_LCTRL  = false;
		InputHandler::firstTap_ESCAPE = false;
		InputHandler::firstTap_RETURN = false;

		InputHandler::firstTap_UP    = false;
		InputHandler::firstTap_DOWN  = false;
		InputHandler::firstTap_LEFT  = false;
		InputHandler::firstTap_RIGHT = false;
		// Process SDL Events
		while (SDL_PollEvent(&e))
		{
			switch (e.type)
			{
				// Window Events
				case SDL_QUIT: {
					application_is_running = false;
				} break;
				case SDL_KEYDOWN: {
					switch (e.key.keysym.sym)
					{
					case SDLK_w: if (!InputHandler::isDown_W) { InputHandler::isDown_W = InputHandler::firstTap_W = true; } break;
					case SDLK_a: if (!InputHandler::isDown_A) { InputHandler::isDown_A = InputHandler::firstTap_A = true; } break;
					case SDLK_s: if (!InputHandler::isDown_S) { InputHandler::isDown_S = InputHandler::firstTap_S = true; } break;
					case SDLK_d: if (!InputHandler::isDown_D) { InputHandler::isDown_D = InputHandler::firstTap_D = true; } break;
					case SDLK_z: if (!InputHandler::isDown_Z) { InputHandler::isDown_Z = InputHandler::firstTap_Z = true; } break;

					case SDLK_LSHIFT: if (!InputHandler::isDown_LSHIFT) { InputHandler::isDown_LSHIFT = InputHandler::firstTap_LSHIFT = true; } break;
					case SDLK_LCTRL:  if (!InputHandler::isDown_LCTRL)  { InputHandler::isDown_LCTRL  = InputHandler::firstTap_LCTRL  = true; } break;
					case SDLK_ESCAPE: if (!InputHandler::isDown_ESCAPE) { InputHandler::isDown_ESCAPE = InputHandler::firstTap_ESCAPE = true; } break;
					case SDLK_RETURN: if (!InputHandler::isDown_RETURN) { InputHandler::isDown_RETURN = InputHandler::firstTap_RETURN = true; } break;

					case SDLK_UP:    if (!InputHandler::isDown_UP)    { InputHandler::isDown_UP    = InputHandler::firstTap_UP    = true; } break;
					case SDLK_DOWN:  if (!InputHandler::isDown_DOWN)  { InputHandler::isDown_DOWN  = InputHandler::firstTap_DOWN  = true; } break;
					case SDLK_LEFT:  if (!InputHandler::isDown_LEFT)  { InputHandler::isDown_LEFT  = InputHandler::firstTap_LEFT  = true; } break;
					case SDLK_RIGHT: if (!InputHandler::isDown_RIGHT) { InputHandler::isDown_RIGHT = InputHandler::firstTap_RIGHT = true; } break;
					}
				} break;
				case SDL_KEYUP: {
					switch (e.key.keysym.sym)
					{
					case SDLK_w: InputHandler::isDown_W = false; break;
					case SDLK_a: InputHandler::isDown_A = false; break;
					case SDLK_s: InputHandler::isDown_S = false; break;
					case SDLK_d: InputHandler::isDown_D = false; break;
					case SDLK_z: InputHandler::isDown_Z = false; break;

					case SDLK_LSHIFT: InputHandler::isDown_LSHIFT = false; break;
					case SDLK_LCTRL:  InputHandler::isDown_LCTRL  = false; break;
					case SDLK_ESCAPE: InputHandler::isDown_ESCAPE = false; break;
					case SDLK_RETURN: InputHandler::isDown_RETURN = false; break;
					
					case SDLK_UP:    InputHandler::isDown_UP    = false; break;
					case SDLK_DOWN:  InputHandler::isDown_DOWN  = false; break;
					case SDLK_LEFT:  InputHandler::isDown_LEFT  = false; break;
					case SDLK_RIGHT: InputHandler::isDown_RIGHT = false; break;
					}
				} break;
			}
		}


		// Update Game and Application States
		// Mouse Update
		mouse.Update();
		player->Logic();
		if (InputHandler::GetKeyDown(InputHandler::KEY_ESCAPE)) application_is_running = false; // End Application
		for (auto bullet : bullets)
		{
			bullet->Logic();
		}
		if (InputHandler::GetKeyTap(InputHandler::KEY_Z)) // Fire Bullet
		{
			// Initialise Bullet with ECS
			Bullet* bullet = new Bullet(renderer, player->position->x, player->position->y);
			// Save the ESC components
			entities.push_back(bullet);
			bullets.push_back(bullet);
		}

		// Update UI
		// Text Update
		msg_current_frame.Set(
			renderer,
			std::string("CurrentFrame: " + std::to_string(current_frame)),
			0,
			0
		);
		msg_mouse_x.Set(
			renderer,
			std::string("MouseX: " + std::to_string(mouse.xPos)),
			0,
			msg_current_frame.rect.h
		);
		msg_mouse_y.Set(
			renderer,
			std::string("MouseY: " + std::to_string(mouse.yPos)),
			0,
			msg_mouse_x.rect.y + msg_mouse_x.rect.h
		);
		msg_player_x.Set(
			renderer,
			std::string("PlayerX: " + std::to_string(player->position->x)),
			0,
			msg_mouse_y.rect.y + msg_mouse_y.rect.h
		);
		msg_player_y.Set(
			renderer,
			std::string("PlayerY: " + std::to_string(player->position->y)),
			0,
			msg_player_x.rect.y + msg_player_x.rect.h
		);


		// Rendering
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 1);
		// Render Play Field
		playField.Render(renderer);
		// Render ECS Components
		for (int i = 0; i < entities.size(); i++)
		{
			entities[i]->draw(renderer);
		}
		// Render Text
		msg_current_frame.Render(renderer);
		msg_mouse_x.Render(renderer);
		msg_mouse_y.Render(renderer);
		msg_player_x.Render(renderer);
		msg_player_y.Render(renderer);
		// Present buffer
		SDL_RenderPresent(renderer);


		// Calculate FPS
		currentTime = SDL_GetTicks();
		if (currentTime - previousTime < 1000.0f / FPS_TARGET)
		{
			SDL_Delay((Uint32)(1000.0f / FPS_TARGET) - currentTime + previousTime);
		}
		current_frame++;
		previousTime = SDL_GetTicks();
	}


	// Memory Cleaning
	// Clear Entity Vector
	for (Entity* e : entities)
	{
		delete e;
	}


	// Quit Functions
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	TTF_Quit();
	IMG_Quit();

	return 0;
}