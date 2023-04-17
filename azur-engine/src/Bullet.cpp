#include "Bullet.h"

#include "PlayField.h"

Bullet::Bullet(SDL_Renderer* renderer, float x, float y)
{
	position = addComponent<PositionComponent>();
	position->x = x;
	position->y = y;
	addComponent<SpriteComponent>()->setTexture(position, renderer, "small_bullet.png", 0, 0, 12, 12);
}

void Bullet::Logic()
{
	float speed = 2.5f;
	position->y -= speed;

	if (position->y < PlayField::screen_boundaries_top)
	{
		position->y = 400; // TODO: Temporary fix. A system needs to be created to handle the deletion of the components of this entity.
		//delete this;
	}
}
