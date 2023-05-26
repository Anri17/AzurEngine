#include "BulletComponent.h"

#include "PlayFieldComponent.h"
#include "ECSManager.h"

#include "AzurMath.h"

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

	// TODO: The life cycle of a bullet should be defined in a different way. If it's out of the playfield, count to 300 frames. If it doesn't get back inside the playfield, flag for deletion
	if (position->y - height / 2 < PlayFieldComponent::Top ||
		position->y + height / 2 > PlayFieldComponent::Bottom ||
		position->x - width / 2 < PlayFieldComponent::Left ||
		position->x + width / 2 > PlayFieldComponent::Right)
	{
		EntityManager::FlagForDeletion(this->entity);
	}
}
