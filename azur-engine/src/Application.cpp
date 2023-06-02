#include "Application.h"

#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <vector>
#include <map>
#include <cstring>

#include "AzurLib.h"
#include "AzurDebug.h"

// Engine
#include "Mouse.h"
#include "InputHandler.h"

// TODO: Might want to separate these into engine specific components and game specific components
// TODO: A player component doesn't have to be in the engine, compared to a Collider component
// TODO: This is probably best identififed by putting a side the componends that are tied to a system of sorts.
// Game Components

// TODO: Same as the components.
// TODO: Might want to separate the systems that are engine specific and game specific.
// Application and Engine Systems
#include "ECS.h"
#include "CollisionManager.h"
#include "SpriteManager.h"
#include "TextManager.h"

// TODO: These defines are both game specific and engine speficic
// TODO: What this means is that the values are specific to the need of the applicaiton, but they are needed none the less
//       in every application
#define WINDOW_ASPECT_RATION (3/4)
#define FPS_TARGET 60
#define INPUT_MANAGER_KEY_COUNT 1024

SDL_Window* Application::window;
SDL_Renderer* Application::renderer;

int Application::current_window_width = 800;
int Application::current_window_height = 600;
float Application::current_window_ratio = 0.75f; // 4:3

// TODO: extract the logic from the components into their own separate system
// I.E.: Rendering of sprites and position to Renderer
// I.E.: Collider Calculations to ColliderManager
// I.E.: Rendering of Text to Renderer
// I.E.: Movement of Bullets with BulletManager
// I.E.: Spawning of Shot with ShotManager
int Application::Start()
{
	// Initialise libraries, create the window and renderer, set initial program and system states.
	// Initialise SDL, TTF, IMG
	SDL_Init(SDL_INIT_EVERYTHING);
	if (TTF_Init() == -1)
	{
		DEBUG_CONSOLE_LOG("TTF_Init: " << TTF_GetError());
		exit(-1);
	}
	IMG_Init(IMG_INIT_PNG);
	// Create Window, Renderer & Event
	Application::window = SDL_CreateWindow("Azur Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, current_window_width, current_window_height, SDL_WINDOW_OPENGL);
	Application::renderer = SDL_CreateRenderer(Application::window, -1, 0);
	SDL_Event e; // used for input events
	// The running state of the applications
	bool application_is_running = true;


	// Entity and Component Initialization
	// Initialize Sprites
	SpriteManager::InitializeSprites();
	// Initialise Text For Debuging
	std::string basepath = SDL_GetBasePath();
	std::string fontname = "SpaceMono-Regular.ttf";
	std::string fontpath = basepath + fontname;
	int fontsize = 12;
	SDL_Color message_color = { 255, 255, 255 };
	Text* current_frame_text = ECS::ECS_Manager::CreateText("Current Frame Text", "current_frame_text", fontpath, fontsize, message_color)->GetComponent<Text>();
	current_frame_text->position->y = 0;
	Text* mouse_x_text = ECS::ECS_Manager::CreateText("Mouse X Text", "mouse_x_text", fontpath, fontsize, message_color)->GetComponent<Text>();
	mouse_x_text->position->y = current_frame_text->rect.h;
	Text* mouse_y_text = ECS::ECS_Manager::CreateText("Mouse Y Text", "mouse_y_text", fontpath, fontsize, message_color)->GetComponent<Text>();
	mouse_y_text->position->y = mouse_x_text->rect.h + mouse_x_text->position->y;
	Text* player_x_text = ECS::ECS_Manager::CreateText("Player X Text", "player_x_text", fontpath, fontsize, message_color)->GetComponent<Text>();
	player_x_text->position->y = mouse_y_text->rect.h + mouse_y_text->position->y;
	Text* player_y_text = ECS::ECS_Manager::CreateText("Player Y Text", "p_y_text", fontpath, fontsize, message_color)->GetComponent<Text>();
	player_y_text->position->y = player_x_text->rect.h + player_x_text->position->y;
	Text* player_lives_text = ECS::ECS_Manager::CreateText("Player Lives Text", "player_lives_text", fontpath, fontsize, message_color)->GetComponent<Text>();
	player_lives_text->position->y = player_y_text->rect.h + player_y_text->position->y;
	Text* debug_mode_text = ECS::ECS_Manager::CreateText("Debug Mode Text", "debug_mode_text", fontpath, fontsize, message_color)->GetComponent<Text>();
	debug_mode_text->position->y = player_lives_text->rect.h + player_lives_text->position->y;
	// Initialise Mouse
	Mouse mouse;
	Entity* playFieldEntity = ECS::ECS_Manager::CreatePlayFieldEntity("PlayField");
	Entity* playerEntity = ECS::ECS_Manager::CreatePlayerEntity("Player", ECS::ECS_Tag::PLAYER);
	Player* playerComponent = playerEntity->GetComponent<Player>();
	Entity* BulletSpawnerEntity = ECS::ECS_Manager::CreateBulletSpawnerEntity("Bullet Spawner", 320, 180, ECS::ECS_Tag::ENEMY);

	// Create a Stage Component. Most of the gameplayer logic goes here.
	// TODO: In the future, I want to somehow save and load a stage data into a file and into the game
	// TODO: This is so that I can later save the game, but also create a stage editor.
	// START: RESUME DEVELOPMENT FROM HERE
	Entity* stageEntity = new Entity();
	stageEntity->name = "Stage";
	ECS::ECS_Manager::AddEntity(stageEntity);
	// Azur Debug
	AzurDebug::init();

	// The Application Loop
	// FPS Calculation Variables
	Uint64 current_frame = 0;
	Uint32 previousTime = SDL_GetTicks();
	Uint32 currentTime = SDL_GetTicks();
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
		InputHandler::firstTap_LCTRL = false;
		InputHandler::firstTap_ESCAPE = false;
		InputHandler::firstTap_RETURN = false;

		InputHandler::firstTap_1 = false;
		InputHandler::firstTap_2 = false;
		InputHandler::firstTap_3 = false;
		InputHandler::firstTap_4 = false;
		InputHandler::firstTap_5 = false;
		InputHandler::firstTap_6 = false;
		InputHandler::firstTap_7 = false;
		InputHandler::firstTap_8 = false;
		InputHandler::firstTap_9 = false;
		InputHandler::firstTap_0 = false;

		InputHandler::firstTap_UP = false;
		InputHandler::firstTap_DOWN = false;
		InputHandler::firstTap_LEFT = false;
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

				case SDLK_1: if (!InputHandler::isDown_1) { InputHandler::isDown_1 = InputHandler::firstTap_1 = true; break; }
				case SDLK_2: if (!InputHandler::isDown_2) { InputHandler::isDown_2 = InputHandler::firstTap_2 = true; break; }
				case SDLK_3: if (!InputHandler::isDown_3) { InputHandler::isDown_3 = InputHandler::firstTap_3 = true; break; }
				case SDLK_4: if (!InputHandler::isDown_4) { InputHandler::isDown_4 = InputHandler::firstTap_4 = true; break; }
				case SDLK_5: if (!InputHandler::isDown_5) { InputHandler::isDown_5 = InputHandler::firstTap_5 = true; break; }
				case SDLK_6: if (!InputHandler::isDown_6) { InputHandler::isDown_6 = InputHandler::firstTap_6 = true; break; }
				case SDLK_7: if (!InputHandler::isDown_7) { InputHandler::isDown_7 = InputHandler::firstTap_7 = true; break; }
				case SDLK_8: if (!InputHandler::isDown_8) { InputHandler::isDown_8 = InputHandler::firstTap_8 = true; break; }
				case SDLK_9: if (!InputHandler::isDown_9) { InputHandler::isDown_9 = InputHandler::firstTap_9 = true; break; }
				case SDLK_0: if (!InputHandler::isDown_0) { InputHandler::isDown_0 = InputHandler::firstTap_0 = true; break; }

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

				case SDLK_1: InputHandler::isDown_1 = false; break;
				case SDLK_2: InputHandler::isDown_2 = false; break;
				case SDLK_3: InputHandler::isDown_3 = false; break;
				case SDLK_4: InputHandler::isDown_4 = false; break;
				case SDLK_5: InputHandler::isDown_5 = false; break;
				case SDLK_6: InputHandler::isDown_6 = false; break;
				case SDLK_7: InputHandler::isDown_7 = false; break;
				case SDLK_8: InputHandler::isDown_8 = false; break;
				case SDLK_9: InputHandler::isDown_9 = false; break;
				case SDLK_0: InputHandler::isDown_0 = false; break;

				case SDLK_UP:    InputHandler::isDown_UP    = false; break;
				case SDLK_DOWN:  InputHandler::isDown_DOWN  = false; break;
				case SDLK_LEFT:  InputHandler::isDown_LEFT  = false; break;
				case SDLK_RIGHT: InputHandler::isDown_RIGHT = false; break;
				}
			} break;
			}
		}


		// Update Game and Application States
		// Application Level Update
		mouse.Update();
		if (InputHandler::GetKeyDown(InputHandler::KEY_ESCAPE)) application_is_running = false;
		// Game Level Update
		ECS::ECS_Manager::Update();
		// Delete Flagged Entities
		ECS::ECS_Manager::DeleteFlagedEntities();
		// Collision update
		CollisionManager::Update();
		// Update UI
		// Text Update
		current_frame_text->SetMessage(std::string("CurrentFrame: " + std::to_string(current_frame)));
		mouse_x_text->SetMessage(std::string("MouseX: " + std::to_string(mouse.xPos)));
		mouse_y_text->SetMessage(std::string("MouseY: " + std::to_string(mouse.yPos)));
		if (playerEntity->active) // TODO: THis is a temporary Fix. A proper solution would be to probably activate or deactiveate an entity, so taht it doesn't come up when the update and draw loops are executed, having that entity be skipped.
		{
			player_x_text->SetMessage(std::string("PlayerX: " + std::to_string(playerComponent->position->x)));
			player_y_text->SetMessage(std::string("PlayerY: " + std::to_string(playerComponent->position->y)));
			player_lives_text->SetMessage(std::string("Player Lives: " + std::to_string(playerComponent->lives)));
		}
		if (AzurDebug::debug_mode)
		{
			debug_mode_text->SetMessage(std::string("Debug Mode: ON"));
		}
		else
		{
			debug_mode_text->SetMessage(std::string("Debug Mode: OFF"));
		}
		TextManager::Update();
		// Change Window Resolution
		if (InputHandler::GetKeyTap(InputHandler::KEY_1))
		{
			// TODO: Extract this into a SetResolutionFunction(WIdht, Height);
			int prev_window_width  = Application::current_window_width;
			int prev_window_height = Application::current_window_height;
			Application::current_window_width  = 640;
			Application::current_window_height = 480;
			int window_pos_x;
			int window_pos_y;
			SDL_GetWindowPosition(window, &window_pos_x, &window_pos_y);
			window_pos_x = window_pos_x - ((Application::current_window_width - prev_window_width) / 2);
			window_pos_y = window_pos_y - ((Application::current_window_height - prev_window_height) / 2);
			SDL_SetWindowPosition(window, window_pos_x, window_pos_y);
			SDL_SetWindowSize(Application::window, Application::current_window_width, Application::current_window_height);
		}
		if (InputHandler::GetKeyTap(InputHandler::KEY_2))
		{
			// TODO: Extract this into a SetResolutionFunction(WIdht, Height);
			int prev_window_width = Application::current_window_width;
			int prev_window_height = Application::current_window_height;
			Application::current_window_width  = 800;
			Application::current_window_height = 600;
			int window_pos_x;
			int window_pos_y;
			SDL_GetWindowPosition(window, &window_pos_x, &window_pos_y);
			window_pos_x = window_pos_x - ((Application::current_window_width - prev_window_width) / 2);
			window_pos_y = window_pos_y - ((Application::current_window_height - prev_window_height) / 2);
			SDL_SetWindowPosition(window, window_pos_x, window_pos_y);
			SDL_SetWindowSize(Application::window, Application::current_window_width, Application::current_window_height);
		}
		if (InputHandler::GetKeyTap(InputHandler::KEY_3))
		{
			// TODO: Extract this into a SetResolutionFunction(WIdht, Height);
			int prev_window_width = Application::current_window_width;
			int prev_window_height = Application::current_window_height;
			Application::current_window_width  = 1024;
			Application::current_window_height = 768;
			int window_pos_x;
			int window_pos_y;
			SDL_GetWindowPosition(window, &window_pos_x, &window_pos_y);
			window_pos_x = window_pos_x - ((Application::current_window_width - prev_window_width) / 2);
			window_pos_y = window_pos_y - ((Application::current_window_height - prev_window_height) / 2);
			SDL_SetWindowPosition(window, window_pos_x, window_pos_y);
			SDL_SetWindowSize(Application::window, Application::current_window_width, Application::current_window_height);
		}
		// Azur Debug
		AzurDebug::update();


		// Rendering
		SDL_RenderClear(Application::renderer);
		SDL_SetRenderDrawColor(Application::renderer, 0, 0, 0, 1);
		// Render ECS Components
		ECS::ECS_Manager::Render(Application::renderer);
		// Render Collisisons
		CollisionManager::Render(Application::renderer);
		// Render Text
		TextManager::Render(Application::renderer);
		// Some components use this function to set lines or dot colors. This need to be here so that the backgroud is set to black.
		SDL_SetRenderDrawColor(Application::renderer, 0, 0, 0, 1);
		// Present buffer
		SDL_RenderPresent(Application::renderer);


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
	ECS::ECS_Manager::DeleteAllEntities();
	// Clear Sprites
	SpriteManager::DeleteSprites();
	// Quit Functions
	SDL_DestroyRenderer(Application::renderer);
	SDL_DestroyWindow(Application::window);
	SDL_Quit();
	TTF_Quit();
	IMG_Quit();

	return 0;
}

int Application::GetWindowTrueX(float x)
{
	return (x * Application::current_window_width)/Application::base_window_width;
}

int Application::GetWindowTrueY(float y)
{
	return (y * Application::current_window_height) / Application::base_window_height;
}
