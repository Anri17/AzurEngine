#include "Bullet.h"

#include ".\..\ECS_Manager.h"

namespace ECS
{
	void Bullet::init()
	{
		position = entity->GetComponent<Position>();
	}

	void Bullet::update()
	{
		// TODO: The bullet will use a velocity vector to move.
		// The calculations are done given a speed and an angle variable.
		float angle_rad = angle * (float)AzurMath::PI / 180.0f;
		velocity.y = sin(angle_rad) * speed;
		velocity.x = cos(angle_rad) * speed;

		position->x += velocity.x;
		position->y += velocity.y;


		bool is_inside_playfield = false;
		for (size_t i = 0; i < collider->collider_references.size(); ++i)
		{
			if ((collider->collider_references[i]->entity->tag == ECS_Tag::PLAYFIELD))
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
				ECS_Manager::FlagForDeletion(entity);
			}
		}
	}
}
