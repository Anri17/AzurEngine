#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include <vector>
#include <map>
#include <cstring>

#include "GameObject.h"
#include "Mouse.h"

#include "ECS.h"
#include "Components.h"
#include "ECSEntities.h"

#include "InputHandler.h"

#define WINDOW_WIDTH  640
#define WINDOW_HEIGHT 480

#define FPS_TARGET 60

#define INPUT_MANAGER_KEY_COUNT 1024


// Game Related Objects
std::vector<GameObject*> gameObjects;
std::vector<Entity*>	 entities;


// Rendering System Data Lists
// Hold the references of the components needed for rendering
std::vector<PositionComponent*> Render_PositionComponents;
std::vector<SpriteComponent*>	Render_SpriteComponents;


struct TextMessage
{
	TextMessage() : message(""), texture(nullptr), rect({ 0,0,0,0 }) {};
	std::string message;
	SDL_Texture* texture;
	SDL_Rect rect;
};

void SetText(TextMessage* message, SDL_Renderer* renderer, TTF_Font* font, SDL_Color color)
{
	SDL_DestroyTexture(message->texture);
	SDL_Surface* surface = TTF_RenderText_Solid(font, message->message.c_str(), color);
	message->texture = SDL_CreateTextureFromSurface(renderer, surface);
	message->rect.w = surface->w;
	message->rect.h = surface->h;
}


int main(int argc, char* argv[])
{
	// Init graphics, create window
	SDL_Init(SDL_INIT_EVERYTHING);
	if (TTF_Init() == -1)
	{
		std::cout << "TTF_Init: " << TTF_GetError() << "\n";
		exit(-1);
	}
	IMG_Init(IMG_INIT_PNG);
	SDL_Window* window = SDL_CreateWindow("Azur Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_Event e; // used for input events
	Uint64 current_frame = 0; // FPS limiting and counting
	bool application_is_running = true; // Controls the applications life cycle
	
	// Init Text For Debuging
	std::string basepath = SDL_GetBasePath();
	std::string fontname = "SpaceMono-Regular.ttf";
	std::string fontpath = basepath + fontname;
	int fontsize = 12;
	TTF_Font* font = TTF_OpenFont(fontpath.c_str(), fontsize);
	if (font == 0)
	{
		std::cout << "Could Not Load Font: " << TTF_GetError() << "\n";
	}
	SDL_Color message_color = { 255, 255, 255 };
	TextMessage msg_current_frame;
	TextMessage msg_mouse_x;
	TextMessage msg_mouse_y;
	TextMessage msg_player_x;
	TextMessage msg_player_y;

	// Mouse
	Mouse mouse;


	// Entities from ECS
	// Create Player
	Player* player = new Player(renderer);
	// Save the components for the ECS
	entities.push_back(player);
	Render_PositionComponents.push_back(player->getComponent<PositionComponent>());
	Render_SpriteComponents.push_back(player->getComponent<SpriteComponent>());


	// FPS Calculation Variables
	Uint32 previousTime = SDL_GetTicks();
	Uint32 currentTime = SDL_GetTicks();


	std::cout << "Text on Screen is temporary. TODO: Make it a debug feature." << "\n";

	while (application_is_running)
	{
		// DEBUG TEXT
		msg_current_frame.message = "CurrentFrame: " + std::to_string(current_frame);
		SetText(&msg_current_frame, renderer, font, message_color);
		msg_mouse_x.message = "MouseX: " + std::to_string(mouse.xPos);
		msg_mouse_x.rect.y = msg_current_frame.rect.h;
		SetText(&msg_mouse_x, renderer, font, message_color);
		msg_mouse_y.message = "MouseY: " + std::to_string(mouse.yPos);
		msg_mouse_y.rect.y = msg_mouse_x.rect.y + msg_mouse_x.rect.h;
		SetText(&msg_mouse_y, renderer, font, message_color);
		msg_player_x.message = "PlayerX: " + std::to_string(player->position->x);
		msg_player_x.rect.y = msg_mouse_y.rect.y + msg_mouse_y.rect.h;
		SetText(&msg_player_x, renderer, font, message_color);
		msg_player_y.message = "PlayerY: " + std::to_string(player->position->y);
		msg_player_y.rect.y = msg_player_x.rect.y + msg_player_x.rect.h;
		SetText(&msg_player_y, renderer, font, message_color);

		// Abstract SDL events into engine components and systems
		// Reset First Tap Event
		InputHandler::firstTap_W = false;
		InputHandler::firstTap_A = false;
		InputHandler::firstTap_S = false;
		InputHandler::firstTap_D = false;

		InputHandler::firstTap_LSHIFT = false;
		InputHandler::firstTap_LCTRL  = false;
		InputHandler::firstTap_ESCAPE = false;
		InputHandler::firstTap_RETURN = false;

		InputHandler::firstTap_UP    = false;
		InputHandler::firstTap_DOWN  = false;
		InputHandler::firstTap_LEFT  = false;
		InputHandler::firstTap_RIGHT = false;
		// SDL Event Processing
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


		// Object State Processing
		// Mouse Update
		mouse.Update();


		// Object Input Handling
		player->InputLogic();
		// End Application
		if (InputHandler::GetKeyDown(InputHandler::KEY_ESCAPE)) application_is_running = false;


		// Drawing to Screen
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 1);
		// Render GameObject Textures
		for (GameObject* gm : gameObjects)
		{
			SDL_Rect rect;
			rect.x = gm->rect.x + gm->x;
			rect.y = gm->rect.y + gm->y;
			rect.w = gm->rect.w;
			rect.h = gm->rect.h;
			SDL_RenderCopy(renderer, gm->texture, NULL, &rect);
		}
		// ECS Rendering System using Components
		// Render ECS Entities
		for (int i = 0; i < Render_PositionComponents.size(); i++)
		{
			PositionComponent* pc = Render_PositionComponents[i];
			SpriteComponent* sc = Render_SpriteComponents[i];
			SDL_Rect rect;
			rect.x = pc->x + sc->rect.x;
			rect.y = pc->y + sc->rect.y;
			rect.w = sc->rect.w;
			rect.h = sc->rect.h;
			SDL_RenderCopy(renderer, sc->texture, NULL, &rect);
		}
		// Render Text
		SDL_RenderCopy(renderer, msg_current_frame.texture, NULL, &msg_current_frame.rect);
		SDL_RenderCopy(renderer, msg_mouse_x.texture, NULL, &msg_mouse_x.rect);
		SDL_RenderCopy(renderer, msg_mouse_y.texture, NULL, &msg_mouse_y.rect);
		SDL_RenderCopy(renderer, msg_player_x.texture, NULL, &msg_player_x.rect);
		SDL_RenderCopy(renderer, msg_player_y.texture, NULL, &msg_player_y.rect);
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


	// Memory Cleaning
	// Clear GameObject Vector
	for (GameObject* gm : gameObjects)
	{
		delete gm;
	}
	// Clear Entity Vector
	for (Entity* e : entities)
	{
		delete e;
	}
	// Clear Text
	SDL_DestroyTexture(msg_current_frame.texture);
	SDL_DestroyTexture(msg_mouse_x.texture);
	SDL_DestroyTexture(msg_mouse_y.texture);
	SDL_DestroyTexture(msg_player_x.texture);
	SDL_DestroyTexture(msg_player_y.texture);

	// Quit Functions
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	TTF_Quit();
	IMG_Quit();

	return 0;
}