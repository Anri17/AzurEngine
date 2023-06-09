#ifndef _APPLICATION_H
#define _APPLICATION_H

#include <SDL.h>

#include "ECS.h"

#include "Systems.h"
#include "Mouse.h"

struct Application
{
	static SDL_Window* window;
	static SDL_Renderer* renderer;

	static int Start(); // Return 0 if successul

	static void Update(Uint64& current_frame, Mouse& mouse, bool& application_is_running, Player& playerComponent, Entity* playerEntity);
	static void Render();

	static int GetWindowTrueX(float x);
	static int GetWindowTrueY(float y);

	inline static const int base_window_width = 640;
	inline static const int base_window_height = 480;

	inline static int current_window_width = 800;
	inline static int current_window_height = 600;
	inline static float current_window_ratio = 0.75f; // 4:3

	// Game Assets
	// This will need to be separated to another class for the Scene
	
	inline static Entity* playFieldEntity;
	inline static Entity* playerEntity;
	inline static Player* playerComponent;
	inline static Entity* BulletSpawnerEntity;

	inline static Uint64 current_frame;
	inline static Mouse mouse;

	inline static std::vector<ECS::ISystem*> systems;
};


#endif // _APPLICATION_H