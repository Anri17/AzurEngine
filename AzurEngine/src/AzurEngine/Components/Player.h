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

	bool is_dead;
	bool is_invincible;

	// Revive variables
	int revive_cooldown = 90; // 1.5 second
	int revive_frame_count = 0;

	// Invincibility Variables
	int invincibility_cooldown = 240; // 4 seconds
	int invincibility_frame_count = 0;

	float spawnX;
	float spawnY;

	int player_w; // TODO: Get the sprite w through the SDL_Rect.
	int player_h; // TODO: Get the sprite h through the SDL_Rect.
	int fire_frame;

	float normalSpeed;
	float focusSpeed;


private:
	float xVelocity;
	float yVelocity;
	float speed;
};

#endif // _PLAYER_H