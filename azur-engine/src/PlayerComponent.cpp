#include "PlayerComponent.h"

#include <cmath>

#include <SDL.h>

#include "Application.h"
#include "InputHandler.h"
#include "ECSManager.h"
#include "PlayFieldComponent.h"
#include "SpriteManager.h"

void PlayerComponent::init()
{
	position = entity->GetComponent<PositionComponent>();
	sprite = entity->GetComponent<SpriteComponent>();
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

	if (AzurDebug::debug_mode)
	{
		lives = 99;
	}

	if (!was_hit)
	{
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
			if ((fire_frame % 8) == 0)
			{
				// float bulletSpeed = 4.0f;
				float bulletSpeed = 32.0f;
				float bulletAngle = 270.0f;
				EntityManager::CreateBulletEntityA(
					"Player Bullet",
					this->position->x,
					this->position->y,
					EntityTag::BULLET_PLAYER,
					bulletSpeed,
					bulletAngle,
					BulletType::PLAYER);
			}

			fire_frame++;
		}
		else
		{
			fire_frame = 0;
		}
	}

	for (size_t i = 0; i < collider->collider_references.size(); ++i)
	{
		if ((collider->collider_references[i]->entity->tag == EntityTag::BULLET_ENEMY || collider->collider_references[i]->entity->tag == EntityTag::ENEMY) && (!was_hit && !is_invincible))
		{
			EntityManager::FlagForDeletion(collider->collider_references[i]->entity);
			--lives;
			was_hit = true;
			sprite->sprite = SpriteManager::blank_texture;
			break;
		}
	}

	// Player is dead and is now going to revive
	if (was_hit && lives >= 0)
	{
		revive_frame_count++;
		if (revive_frame_count % revive_cooldown == 0)
		{
			position->x = spawnX;
			position->y = spawnY;
			sprite->sprite = SpriteManager::player;
			was_hit = false;
			revive_frame_count = 0;
			EntityManager::FlagForDeletionAllTagged(EntityTag::BULLET_ENEMY);
			is_invincible = true;
		}
	}

	// Player has revived and is now invincible for a few seconds
	if (is_invincible)
	{
		invincibility_frame_count++;
		// Player flashes while invincible
		if (invincibility_frame_count % 3 == 0) sprite->sprite = SpriteManager::blank_texture;
		if (invincibility_frame_count % 6 == 0) sprite->sprite = SpriteManager::player;

		// Cool down is over, invincibility is over
		if (invincibility_frame_count % invincibility_cooldown == 0)
		{
			// TODO: 
			is_invincible = false;
			sprite->sprite = SpriteManager::player;
		}
	}
}
