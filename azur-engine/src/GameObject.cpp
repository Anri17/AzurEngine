#include "GameObject.h"

GameObject::GameObject() : x(0.0f), y(0.0f), texture(nullptr)
{

}

GameObject::~GameObject()
{
	SDL_DestroyTexture(texture);
}
