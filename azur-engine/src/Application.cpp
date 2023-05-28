#include "Application.h"

#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <vector>
#include <map>
#include <cstring>

#include "AzurMemoryLeakFinder.h"

// Engine
#include "Application.h"
#include "AzurDebug.h"
#include "Mouse.h"
#include "InputHandler.h"

// TODO: Might want to separate these into engine specific components and game specific components
// TODO: A player component doesn't have to be in the engine, compared to a Collider component
// TODO: This is probably best identififed by putting a side the componends that are tied to a system of sorts.
// Game Components
#include "Components.h"
// TODO: Same as the components.
// TODO: Might want to separate the systems that are engine specific and game specific.
// Application and Engine Systems
#include "ECSManager.h"
#include "CollisionManager.h"
#include "SpriteManager.h"

// TODO: These defines are both game specific and engine speficic
// TODO: What this means is that the values are specific to the need of the applicaiton, but they are needed none the less
//       in every application
#define WINDOW_WIDTH  640
#define WINDOW_HEIGHT 480
#define FPS_TARGET 60
#define INPUT_MANAGER_KEY_COUNT 1024

SDL_Window* Application::window;
SDL_Renderer* Application::renderer;

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
	Application::window = SDL_CreateWindow("Azur Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
	Application::renderer = SDL_CreateRenderer(Application::window, -1, 0);
	// TODO: replace all of renderers to Application::renderer
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
	TextComponent* current_frame_text = EntityManager::CreateText("Current Frame Text", "current_frame_text", fontpath, fontsize, message_color)->GetComponent<TextComponent>();
	current_frame_text->position->y = 0;
	TextComponent* mouse_x_text = EntityManager::CreateText("Mouse X Text", "mouse_x_text", fontpath, fontsize, message_color)->GetComponent<TextComponent>();
	mouse_x_text->position->y = current_frame_text->rect.h;
	TextComponent* mouse_y_text = EntityManager::CreateText("Mouse Y Text", "mouse_y_text", fontpath, fontsize, message_color)->GetComponent<TextComponent>();
	mouse_y_text->position->y = mouse_x_text->rect.h + mouse_x_text->position->y;
	TextComponent* player_x_text = EntityManager::CreateText("Player X Text", "player_x_text", fontpath, fontsize, message_color)->GetComponent<TextComponent>();
	player_x_text->position->y = mouse_y_text->rect.h + mouse_y_text->position->y;
	TextComponent* player_y_text = EntityManager::CreateText("Player Y Text", "p_y_text", fontpath, fontsize, message_color)->GetComponent<TextComponent>();
	player_y_text->position->y = player_x_text->rect.h + player_x_text->position->y;
	TextComponent* player_lives_text = EntityManager::CreateText("Player Lives Text", "player_lives_text", fontpath, fontsize, message_color)->GetComponent<TextComponent>();
	player_lives_text->position->y = player_y_text->rect.h + player_y_text->position->y;
	TextComponent* debug_mode_text = EntityManager::CreateText("Debug Mode Text", "debug_mode_text", fontpath, fontsize, message_color)->GetComponent<TextComponent>();
	debug_mode_text->position->y = player_lives_text->rect.h + player_lives_text->position->y;
	// Initialise Mouse
	Mouse mouse;
	Entity* playFieldEntity = EntityManager::CreatePlayFieldEntity("PlayField");
	Entity* playerEntity = EntityManager::CreatePlayerEntity("Player", EntityTag::PLAYER);
	PlayerComponent* playerComponent = playerEntity->GetComponent<PlayerComponent>();
	Entity* BulletSpawnerEntity = EntityManager::CreateBulletSpawnerEntity("Bullet Spawner", 320, 180, EntityTag::ENEMY);

	// Create a Stage Component. Most of the gameplayer logic goes here.
	// TODO: In the future, I want to somehow save and load a stage data into a file and into the game
	// TODO: This is so that I can later save the game, but also create a stage editor.
	// START: RESUME DEVELOPMENT FROM HERE
	Entity* stageEntity = new Entity();
	stageEntity->name = "Stage";
	EntityManager::AddEntity(stageEntity);
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
				case SDLK_LCTRL:  if (!InputHandler::isDown_LCTRL) { InputHandler::isDown_LCTRL = InputHandler::firstTap_LCTRL = true; } break;
				case SDLK_ESCAPE: if (!InputHandler::isDown_ESCAPE) { InputHandler::isDown_ESCAPE = InputHandler::firstTap_ESCAPE = true; } break;
				case SDLK_RETURN: if (!InputHandler::isDown_RETURN) { InputHandler::isDown_RETURN = InputHandler::firstTap_RETURN = true; } break;

				case SDLK_UP:    if (!InputHandler::isDown_UP) { InputHandler::isDown_UP = InputHandler::firstTap_UP = true; } break;
				case SDLK_DOWN:  if (!InputHandler::isDown_DOWN) { InputHandler::isDown_DOWN = InputHandler::firstTap_DOWN = true; } break;
				case SDLK_LEFT:  if (!InputHandler::isDown_LEFT) { InputHandler::isDown_LEFT = InputHandler::firstTap_LEFT = true; } break;
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
				case SDLK_LCTRL:  InputHandler::isDown_LCTRL = false; break;
				case SDLK_ESCAPE: InputHandler::isDown_ESCAPE = false; break;
				case SDLK_RETURN: InputHandler::isDown_RETURN = false; break;

				case SDLK_UP:    InputHandler::isDown_UP = false; break;
				case SDLK_DOWN:  InputHandler::isDown_DOWN = false; break;
				case SDLK_LEFT:  InputHandler::isDown_LEFT = false; break;
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
		EntityManager::Update();
		// Delete Flagged Entities
		EntityManager::DeleteFlagedEntities();
		// Collision update
		CollisionManager::Update();


		// Update UI
		// Text Updae
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
		// Azur Debug
		AzurDebug::update();


		// Rendering
		SDL_RenderClear(Application::renderer);
		SDL_SetRenderDrawColor(Application::renderer, 0, 0, 0, 1);
		// Render ECS Components
		EntityManager::Render(Application::renderer);
		// Render Text


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
	EntityManager::DeleteAllEntities();
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
