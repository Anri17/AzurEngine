#include "Application.h"

#include <stdio.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <glad/glad.h>
#include <vector>
#include <map>
#include <cstring>

#include "util.h"

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

#include "AssetManager.h"

// TODO: These defines are both game specific and engine speficic
// TODO: What this means is that the values are specific to the need of the applicaiton, but they are needed none the less
//       in every application
#define WINDOW_ASPECT_RATION (3/4)
#define FPS_TARGET 120
#define INPUT_MANAGER_KEY_COUNT 1024

namespace AzurEngine {

	// Initialise libraries, create the window and renderer, set initial program and system states.
	// Initialise SDL, TTF, IMG
	void application_init() {
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

		if (SDL_Init(SDL_INIT_VIDEO) < 0) {
			ERROR_EXIT("SDL_Init Error : %s", SDL_GetError());
		}
		if (TTF_Init() == -1) {
			ERROR_EXIT("TTF_Init Error: %s",  TTF_GetError());
		}
		if (!IMG_Init(IMG_INIT_PNG)) {
			ERROR_EXIT("IMG_Init Error: %s", IMG_GetError());
		}

		Application::screen_resolution     = RES_800x600;
		Application::current_window_width  = 800;
		Application::current_window_height = 600;
		Application::current_window_ratio  = 0.75f; // 4:3

		// Create Window, Renderer & Event
		Application::window = SDL_CreateWindow("Azur Engine",
		                                       SDL_WINDOWPOS_CENTERED,
		                                       SDL_WINDOWPOS_CENTERED,
		                                       Application::current_window_width,
		                                       Application::current_window_height,
		                                       SDL_WINDOW_OPENGL);
		if (!Application::window) {
			ERROR_EXIT("Window Creation Error: %s", IMG_GetError());
		}

		// opengl
		SDL_GL_CreateContext(Application::window);
		if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
			ERROR_EXIT("Failed to load GL: %s", IMG_GetError());
		}

		// Display OpenGL Information
		puts("OpenGL Loaded");
		printf("Vendor:   %s\n", glGetString(GL_VENDOR));
		printf("Renderer: %s\n", glGetString(GL_RENDERER));
		printf("Version:  %s\n", glGetString(GL_VERSION));
		
		Application::renderer = SDL_CreateRenderer(Application::window, -1, 0);
		if (!Application::renderer) {
			ERROR_EXIT("Renderer Creation Error: %s", IMG_GetError());
		}
	}

	void game_init() {
		// Create the Systems
		SpriteSystem::Instance    = new SpriteSystem();
		BulletSystem::Instance    = new BulletSystem();
		StageSystem::Instance     = new StageSystem();
		UISystem::Instance        = new UISystem();
		CollisionSystem::Instance = new CollisionSystem();

		// TODO: Tie the game Entities and Systems to a Scene Class Instance.
		// Initialize the Systems
		for (ECS::ISystem *system : Application::systems) {
			system->Init();
		}

		// Initialise entities
		Application::entity_playfield     = AssetManager::CreatePlayFieldEntity("PlayField");
		Application::entity_player        = AssetManager::CreatePlayerEntity("Player",
		                                                                     ECS::Tag::PLAYER);
		Application::entity_bulletspawner = AssetManager::CreateBulletSpawnerEntity("Bullet Spawner",
		                                                                            320,
		                                                                            180,
		                                                                            ECS::Tag::ENEMY);
		// Get components from entities
		Application::component_player = Application::entity_player->GetComponent<Player>();

		// Create a Stage Component. Most of the gameplayer logic goes here.
		// TODO: In the future, I want to somehow save and load a stage data into a file and into the game
		// TODO: This is so that I can later save the game, but also create a stage editor.
		// START: RESUME DEVELOPMENT FROM HERE
		Entity *stageEntity = new Entity();
		stageEntity->name = "Stage";
		ECS::ECSManager::entity_add(stageEntity);
	}

	void application_mainloop() {
		SDL_Event e;
		bool      application_is_running;
		Uint32    loop_time_start;
		Uint32    loop_time_end;
		Uint32    loop_time_elapsed;

		Application::current_frame = 0;
		application_is_running     = true;
		while (application_is_running) {
			loop_time_start = SDL_GetTicks(); // the time at the start of the loop

			InputHandler::reset_first_taps();
			// Process SDL Events
			while (SDL_PollEvent(&e)) {
				switch (e.type) {
				case SDL_QUIT: {
					application_is_running = false;
				} break;
				case SDL_KEYDOWN: {
					InputHandler::process_sdl_event_keydown(e.key.keysym.sym);
				} break;
				case SDL_KEYUP: {
					InputHandler::process_sdl_event_keyup(e.key.keysym.sym);
				} break;
				}
			}

			// I want to have a scene object with the assets. It also has an update and render function.
			// The question is, do I want to store the instantiated entities in the Scene, or in the systems?
			// If I add them in the systems, then I will not be able to reuse them in other scenes if I need to
			//
			//
			// If I have a system with the components that it needs, then I don't really need to import a component to a scene
			// What tis means is that I just have the dependency for the scenes, which as a dependency for the components
			// This makes the dependency part easier.
			Application::Update(Application::current_frame,
								Application::mouse, application_is_running,
								*Application::component_player,
								Application::entity_player);
			Application::Render();


			// Calculate FPS
			loop_time_end = SDL_GetTicks(); // the time at the end of the loop
			loop_time_elapsed = loop_time_end - loop_time_start;
			if (loop_time_elapsed < 1000.0f / FPS_TARGET) {
				SDL_Delay((Uint32)(1000.0f / FPS_TARGET) - loop_time_elapsed);
			}
			++Application::current_frame;
		}
	}

	void application_cleanup() {
		// Clear Systems
		for (ECS::ISystem *system : Application::systems) {
			delete system;
		}
		// Clear Entity Vector
		ECS::ECSManager::entity_delete_all();
		// Clear Sprites
		SpriteSystem::DeleteSprites();
		// Quit Functions
		SDL_DestroyRenderer(Application::renderer);
		SDL_DestroyWindow(Application::window);
		SDL_Quit();
		TTF_Quit();
		IMG_Quit();
	}

	Application* app;

	// TODO: These systems can then be extracted such that they are modules of the engine. A tetris game might not need a bullet system, for example
	// TODO: This also means that the engine could potentially allowfor the creation of 3d games. As the 3d Rendering and world would be in their own packages
	// TODO: extract the logic from the components into their own separate system
	// I.E.: Rendering of sprites and position to Renderer
	// I.E.: Collider Calculations to ColliderManager
	// 
	// I.E.: Rendering of Text to Renderer
	// I.E.: Movement of Bullets with BulletManager
	// I.E.: Spawning of Shot with ShotManager
	int Application::Start() {
		// Initializse Systems
		application_init();
		game_init();
		AzurDebug::init();
		application_mainloop();
		application_cleanup();

		return 0;
	}

	void application_changeresolution(SCREEN_RESOLUTION screen_resolution) {
		int              window_pos_x;
		int              window_pos_y;
		SDL_DisplayMode display_mode;

		// Change Resolution
		Application::screen_resolution = screen_resolution;
		switch (screen_resolution) {
		case RES_640x480: {
			Application::current_window_width  = 640;
			Application::current_window_height = 480;
		} break;
		case RES_800x600: {
			Application::current_window_width  = 800;
			Application::current_window_height = 600;
		} break;
		case RES_1024x768: {
			Application::current_window_width  = 1024;
			Application::current_window_height = 768;
		} break;
		default: {
			ERROR_EXIT("Unknown Resolution...\n");
		}
		}
		SDL_SetWindowSize(Application::window, Application::current_window_width, Application::current_window_height);

		// Reset Windows Position
		SDL_GetCurrentDisplayMode(0, &display_mode);
		window_pos_x = (display_mode.w / 2) - (Application::current_window_width / 2);
		window_pos_y = (display_mode.h / 2) - (Application::current_window_height / 2);
		SDL_SetWindowPosition(Application::window, window_pos_x, window_pos_y);
	}

	// TODO: Simplify the parameters here.
	void Application::Update(Uint64 &current_frame,
							 Mouse  &mouse,
							 bool   &application_is_running,
							 Player &playerComponent,
							 Entity *playerEntity) {
		// Update Systems
		for (ECS::ISystem* system : systems) {
			system->Update();
		}
		mouse.Update();
		if (InputHandler::get_key_down(InputHandler::KEY_ESCAPE)) {
			application_is_running = false;
		}

		ECS::ECSManager::update();
		
		// Change Window Resolution
		if (InputHandler::get_key_tap(InputHandler::KEY_1)) {
			application_changeresolution(RES_640x480);
		}
		if (InputHandler::get_key_tap(InputHandler::KEY_2)) {
			application_changeresolution(RES_800x600);
		}
		if (InputHandler::get_key_tap(InputHandler::KEY_3)) {
			application_changeresolution(RES_1024x768);
		}
		AzurDebug::update();
	}

	void Application::Render() {
		// Rendering
		SDL_RenderClear(Application::renderer);
		SDL_SetRenderDrawColor(Application::renderer, 0, 0, 0, 1);
		// Render ECS Components
		ECS::ECSManager::render(Application::renderer);
		// Render Systems
		for (auto system : systems)
		{
			system->Render(renderer);
		}
		// Some components use this function to set lines or dot colors. This need to be here so that the backgroud is set to black.
		SDL_SetRenderDrawColor(Application::renderer, 0, 0, 0, 1);
		// Present buffer
		SDL_RenderPresent(Application::renderer);
	}

	Application* CreateApplication() {
		return nullptr;
	}

}
