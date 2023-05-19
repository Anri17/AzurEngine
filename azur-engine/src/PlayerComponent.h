#ifndef _PLAYER_H
#define _PLAYER_H

#include "ECS.h"
#include "PositionComponent.h"
#include "BoxColliderComponent.h"

class PlayerComponent : public Component
{
public:
	void init() override;
	void update() override;

	PositionComponent* position;
	BoxColliderComponent* boxCollider; // TODO: For some reason this is throwing a syntax error and I don't know why

	int player_w = 32; // TODO: Get the sprite w through the SDL_Rect.
	int player_h = 48; // TODO: Get the sprite h through the SDL_Rect.
	float spawnX = 320.0f;
	float spawnY = 400.0f;
	int fire_frame;
};


#endif // _PLAYER_H