#include "PlayerComponent.h"

#include <cmath>

#include <SDL.h>

#include "Application.h"
#include "InputHandler.h"
#include "ECSManager.h"
#include "PlayFieldComponent.h"

void PlayerComponent::init()
{
	position = entity->getComponent<PositionComponent>();
	boxCollider = entity->getComponent<BoxColliderComponent>();
	position->x = spawnX;
	position->y = spawnY;
	fire_frame = 0;
}

void PlayerComponent::update()
{
	float xVelocity = 0;
	float yVelocity = 0;
	float speed = 0;
	float normalSpeed = 3.0f;
	float focusSpeed = 1.5f;

	if (InputHandler::GetKeyDown(InputHandler::KEY_LSHIFT))
	{
		speed = focusSpeed;
	}
	else
	{
		speed = normalSpeed;
	}

	if (InputHandler::GetKeyDown(InputHandler::KEY_UP))
	{
		yVelocity += -speed;
	}
	if (InputHandler::GetKeyDown(InputHandler::KEY_DOWN))
	{
		yVelocity += speed;
	}
	if (InputHandler::GetKeyDown(InputHandler::KEY_LEFT))
	{
		xVelocity += -speed;
	}
	if (InputHandler::GetKeyDown(InputHandler::KEY_RIGHT))
	{
		xVelocity += speed;
	}

	// Diagonal Velocity
	if (yVelocity != 0 && xVelocity != 0)
	{
		xVelocity = (float)cos((M_PI / 4.0)) * xVelocity;
		yVelocity = (float)sin((M_PI / 4.0)) * yVelocity;
	}

	position->y += yVelocity;
	position->x += xVelocity;


	// Limit Player Play Field
	if (position->x < PlayFieldComponent::Left + player_w / 2.0f) position->x = PlayFieldComponent::Left + player_w / 2.0f;
	if (position->x + player_w / 2.0f > PlayFieldComponent::Right) position->x = PlayFieldComponent::Right - player_w / 2.0f;
	if (position->y < PlayFieldComponent::Top + player_h / 2.0f) position->y = PlayFieldComponent::Top + player_h / 2.0f;
	if (position->y + player_h / 2.0f > PlayFieldComponent::Bottom) position->y = PlayFieldComponent::Bottom - player_h / 2.0f;


	// Fire Bullet
	if (InputHandler::GetKeyDown(InputHandler::KEY_Z))
	{
		if ((fire_frame % 10) == 0)
		{
			EntityManager::CreateBulletEntity("Player Bullet", this->position->x, this->position->y, ColliderTag::BULLET_PLAYER);
		}

		fire_frame++;
	}
	else
	{
		fire_frame = 0;
	}

	for (size_t i = 0; i < boxCollider->collider_tags.size(); ++i)
	{
		if (boxCollider->collider_tags[i] == ColliderTag::BULLET_ENEMY || boxCollider->collider_tags[i] == ColliderTag::ENEMY)
		{
			entity->active = false;
			break;
		}
	}
}
