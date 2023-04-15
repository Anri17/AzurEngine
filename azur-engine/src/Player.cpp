#include "Player.h"

#include <cmath>

#include "InputHandler.h"


Player::Player(SDL_Renderer* renderer)
{
	position = addComponent<PositionComponent>();
	position->x = spawnX;
	position->y = spawnY;
	addComponent<SpriteComponent>()->setTexture(renderer, "player.png", 0, 0, 32, 48);
}

void Player::Logic()
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
		xVelocity = cos((M_PI / 4.0)) * xVelocity;
		yVelocity = cos((M_PI / 4.0)) * yVelocity;
	}

	position->y += yVelocity;
	position->x += xVelocity;
}