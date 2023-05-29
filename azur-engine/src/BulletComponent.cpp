#include "BulletComponent.h"

#include "PlayFieldComponent.h"
#include "ECSManager.h"

#include "AzurMath.h"

#include "Application.h"

void BulletComponent::init()
{
	position = entity->GetComponent<PositionComponent>();
}

void BulletComponent::update()
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
		if ((collider->collider_references[i]->entity->tag == EntityTag::PLAYFIELD))
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
			EntityManager::FlagForDeletion(entity);
		}
	}

	/*
	// TODO: The life cycle of a bullet should be defined in a different way. If it's out of the playfield, count to 300 frames. If it doesn't get back inside the playfield, flag for deletion
	if (position->y - height / 2 < PlayFieldComponent::Top ||
		position->y + height / 2 > PlayFieldComponent::Bottom ||
		position->x - width / 2 < PlayFieldComponent::Left ||
		position->x + width / 2 > PlayFieldComponent::Right)
	{
		
		EntityManager::FlagForDeletion(this->entity);
	}
	*/
}
