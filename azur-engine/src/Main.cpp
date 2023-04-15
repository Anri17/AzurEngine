#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include <vector>
#include <map>
#include <cstring>

// Engine
#include "GameObject.h"
#include "Mouse.h"
#include "InputHandler.h"

// Game
#include "ECSEntities.h"


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


// PlayScreen

struct Text
{
	Text(std::string fontpath, int fontsize, SDL_Color color) : message(""), texture(nullptr), rect({ 0,0,0,0 })
	{
		this->color = color;
		this->size = fontsize;
		this->font = TTF_OpenFont(fontpath.c_str(), fontsize);
		if (font == 0)
		{
			std::cout << "Could Not Load Font: " << TTF_GetError() << "\n";
		}
	};
	~Text()
	{
		SDL_DestroyTexture(texture);
		TTF_CloseFont(font);
	}

	void Render(SDL_Renderer* renderer)
	{
		SDL_RenderCopy(renderer, texture, NULL, &rect);
	}

	void Set(SDL_Renderer* renderer, std::string fontpath, int fontsize, SDL_Color color)
	{
		this->font = font;
		this->color = color;

		SDL_DestroyTexture(texture);
		SDL_Surface* surface = TTF_RenderText_Solid(font, message.c_str(), color);
		texture = SDL_CreateTextureFromSurface(renderer, surface);
		rect.w = surface->w;
		rect.h = surface->h;
		SDL_FreeSurface(surface);
	}
	void Set(SDL_Renderer* renderer)
	{
		SDL_DestroyTexture(texture);
		SDL_Surface* surface = TTF_RenderText_Solid(font, message.c_str(), color);
		texture = SDL_CreateTextureFromSurface(renderer, surface);
		rect.w = surface->w;
		rect.h = surface->h;
		SDL_FreeSurface(surface);
	}
	void Set(SDL_Renderer* renderer, std::string message, int x, int y)
	{
		this->message = message;
		this->rect.x = x;
		this->rect.y = y;

		SDL_DestroyTexture(texture);
		SDL_Surface* surface = TTF_RenderText_Solid(font, message.c_str(), color);
		texture = SDL_CreateTextureFromSurface(renderer, surface);
		rect.w = surface->w;
		rect.h = surface->h;
		SDL_FreeSurface(surface);
	}

	std::string message;
	SDL_Texture* texture;
	SDL_Rect rect;
	int size;
	TTF_Font* font;
	SDL_Color color;
};

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
	SDL_Color message_color = { 255, 255, 255 };
	Text msg_current_frame(fontpath, fontsize, message_color);
	Text msg_mouse_x(fontpath, fontsize, message_color);
	Text msg_mouse_y(fontpath, fontsize, message_color);
	Text msg_player_x(fontpath, fontsize, message_color);
	Text msg_player_y(fontpath, fontsize, message_color);

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
		player->Logic();
		// End Application
		if (InputHandler::GetKeyDown(InputHandler::KEY_ESCAPE)) application_is_running = false;


		// Drawing to Screen
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 1);
		// Draw Play Field
		SDL_Rect playfield_rect;
		playfield_rect.x = PlayField::screen_boundaries_left;
		playfield_rect.y = PlayField::screen_boundaries_top;
		playfield_rect.w = PlayField::screen_boundaries_right - PlayField::screen_boundaries_left;
		playfield_rect.h = PlayField::screen_boundaries_bottom - PlayField::screen_boundaries_top;
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 1); // while color for playfield
		SDL_RenderDrawRect(renderer, &playfield_rect);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 1); // black color for background
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
		msg_current_frame.Render(renderer);
		msg_mouse_x.Render(renderer);
		msg_mouse_y.Render(renderer);
		msg_player_x.Render(renderer);
		msg_player_y.Render(renderer);
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

	// Quit Functions
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	TTF_Quit();
	IMG_Quit();

	return 0;
}