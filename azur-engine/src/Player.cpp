#include "Player.h"

#include <cmath>

#include "InputHandler.h"

#include "PlayField.h"

Player::Player(SDL_Renderer* renderer)
{
	position = addComponent<PositionComponent>();
	position->x = spawnX;
	position->y = spawnY;
	addComponent<SpriteComponent>()->setTexture(position, renderer, "player.png", -player_w/2, -player_h/2, player_w, player_h);
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
		yVelocity = sin((M_PI / 4.0)) * yVelocity;
	}

	position->y += yVelocity;
	position->x += xVelocity;


	// Limit Player Play Field
	if (position->x < PlayField::screen_boundaries_left + player_w / 2.0f) position->x = PlayField::screen_boundaries_left + player_w / 2.0f;
	if (position->x + player_w / 2.0f > PlayField::screen_boundaries_right) position->x = PlayField::screen_boundaries_right - player_w / 2.0f;
	if (position->y < PlayField::screen_boundaries_top + player_h / 2.0f) position->y = PlayField::screen_boundaries_top + player_h / 2.0f;
	if (position->y + player_h/2.0f > PlayField::screen_boundaries_bottom) position->y = PlayField::screen_boundaries_bottom - player_h / 2.0f;
}