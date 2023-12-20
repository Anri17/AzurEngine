#ifndef _PLAYER_H
#define _PLAYER_H

#include ".\..\ECS.h"

#include "Position.h"
#include "Collider.h"
#include "Sprite.h"

class Sprite; // This is to prevent a weird syntac error where a semicolon was missing before an asterist
//#include "SpriteComponent.h"

class Player : public Component
{
public:
	void Init() override;
	void Update() override;

	Position* position;
	Collider* collider;
	Sprite* sprite;

	int lives = 2;

	bool was_hit = false;
	bool is_invincible = false;

	// Revive variables
	int revive_cooldown = 90; // 1.5 second
	int revive_frame_count = 0;

	// Invincibility Variables
	int invincibility_cooldown = 240; // 4 seconds
	int invincibility_frame_count = 0;

	int player_w = 32; // TODO: Get the sprite w through the SDL_Rect.
	int player_h = 48; // TODO: Get the sprite h through the SDL_Rect.
	float spawnX = 320.0f;
	float spawnY = 400.0f;
	int fire_frame;
};

#endif // _PLAYER_H