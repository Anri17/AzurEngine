#ifndef _APPLICATION_H
#define _APPLICATION_H

#include "Core.h"

//#include <SDL.h>

#include "ECS.h"

#include "Systems.h"
#include "Mouse.h"

namespace AzurEngine {
	typedef enum {
		RES_640x480,
		RES_800x600,
		RES_1024x768
	} SCREEN_RESOLUTION;

	class AZUR_API Application {
	public:
		inline static SDL_Window   *window;
		inline static SDL_Renderer *renderer;

		static int  Start(); // Return 0 if successul
		static void Update(Uint64 &current_frame,
						   Mouse  &mouse,
						   bool   &application_is_running,
						   Player &playerComponent,
						   Entity *playerEntity);
		static void Render();

		inline static int GetWindowTrueX(float x) { return int((x * (float)Application::current_window_width) / (float)Application::base_window_width); }
		inline static int GetWindowTrueY(float y) { return int((y * (float)Application::current_window_height) / (float)Application::base_window_height); }

		inline static const int base_window_width = 640;
		inline static const int base_window_height = 480;

		inline static int   current_window_width;
		inline static int   current_window_height;
		inline static float current_window_ratio;

		inline static SCREEN_RESOLUTION screen_resolution;


		// Game Assets
		inline static Entity *entity_playfield;
		inline static Entity *entity_player;
		inline static Player *component_player;
		inline static Entity *entity_bulletspawner;

		inline static Uint64 current_frame;
		inline static Mouse  mouse;

		inline static std::vector<ECS::ISystem*> systems;
	};

	Application *CreateApplication();



	extern AZUR_API Application *app;
}

#endif // _APPLICATION_H