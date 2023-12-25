#include "Bullet.h"

void Bullet::Init()
{
	position = entity->GetComponent<Position>();
}



void Bullet::Update()
{
	// TODO: The bullet will use a velocity vector to move.
	// TODO: MOve the Update and Draw to the Bullet Manager
	// TODO: Make it so that there is a Bullet A which takes an angle and a bullet B which takes the x and y coords for the velocity
	// TODO: Create a getvelocity() method which takes the parameters and types nad sets the velocity that way.
	// The calculations are done given a speed and an angle variable.
	float angle_rad = angle * (float)AzurMath::PI / 180.0f;
	velocity.y = (float)sin(angle_rad) * speed;
	velocity.x = (float)cos(angle_rad) * speed;

	position->x += velocity.x;
	position->y += velocity.y;


	bool is_inside_playfield = false;
	for (size_t i = 0; i < collider->collider_references.size(); ++i)
	{
		if ((collider->collider_references[i]->entity->tag == ECS::Tag::PLAYFIELD))
		{
			is_inside_playfield = true;
			deletion_timer_frame = 0;
			break;
		}
	}
	if (!is_inside_playfield)
	{
		deletion_timer_frame++;
		if (deletion_timer_frame % deletion_cooldown == 0)
		{
			ECS::ECSManager::entity_flag_for_deletion(entity);
		}
	}
}

void Bullet::Render(SDL_Renderer* renderer)
{

}