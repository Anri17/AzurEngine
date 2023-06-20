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

	Position* position;
	Collider* collider;
	int width = 12;
	int height = 12;

	float speed = 1.0f;
	float angle = 0.0f;
private:
	vector2float velocity;

	int deletion_timer_frame = 0;
	int deletion_cooldown = 60; // 1 seconds
};

#endif // _BULLET_COMPONENT_H