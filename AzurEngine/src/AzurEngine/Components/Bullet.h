#ifndef _BULLET_COMPONENT_H
#define _BULLET_COMPONENT_H


#include "./../AzurLib.h"
#include "./../ECS.h"

#include "Position.h"
#include "Collider.h"

class Position;

class Bullet : public ECS::Component
{
public:
	void Init() override;
	void Update() override;
	void Render(SDL_Renderer* renderer) override;

	//vector2float GetVelocity();

	// Components
	Position *position;
	Collider *collider;

	// collision box
	int   width     = 12;
	int   height    = 12;

	// movement
	float speed     = 1.0f;
	float angle_deg = 0.0f;
	float angle_rad;
private:
	vector2float velocity;

	// When bullet is outside of the playfield
	bool is_inside_playfield;
	int  deletion_frame_count    = 0;
	int  deletion_frame_duration = 60; // 60 frames, 1 seconds if 60fps
};

#endif // _BULLET_COMPONENT_H