#ifndef _PLAYER_H
#define _PLAYER_H

#include ".\..\ECS.h"

#include "Position.h"
#include "Collider.h"
#include "Sprite.h"

class Sprite; // This is to prevent a weird syntac error where a semicolon was missing before an asterist
//#include "SpriteComponent.h"



class Player : public Component {
public:
	void Init()   override;
	void Update() override;

	Position *position;
	Collider *collider;
	Sprite   *sprite;

	int lives;

	// Player States
	bool is_dead;
	bool is_invincible;

	// Death System Variables
	int death_frame_duration; // in frames. 1.5 second, when locked at 60 fps
	int death_frame_count;
	int invincibility_frame_duration = 240; // 4 seconds
	int invincibility_frame_count = 0;

	float spawnX;
	float spawnY;

	// collision box
	int player_w; // TODO: Get the sprite w through the SDL_Rect.
	int player_h; // TODO: Get the sprite h through the SDL_Rect.
	
	// fire
	float bullet_speed = 32.0f;
	float bullet_angle = 270.0f;
	int   fire_frame;

	// movement
	float normalSpeed;
	float focusSpeed;

	float  xVelocity;
	float  yVelocity;
	float  speed;
	size_t collider_count;
};

#endif // _PLAYER_H