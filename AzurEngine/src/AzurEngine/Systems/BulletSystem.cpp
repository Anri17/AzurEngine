#include "BulletSystem.h"

#include "./../Application.h"

BulletSystem::BulletSystem()
{
	AzurEngine::Application::systems.push_back(this);
}

void BulletSystem::Init()
{
	// ...
}

void BulletSystem::Update()
{
	// TODO: For every bullet get its posiution and move it
	// TODO: Differente bullet spawning behavious might give it different paramenters
	// TODO: This means that you might needt o get the type nad hten update te velocity ofthe bullet that way. A bullet with thea angle parameter will use the angle to udapte the velocity, while a bullet withe hx y parameters will havethe velocity defined in itself already bythe initial spawning.

}

void BulletSystem::Render(SDL_Renderer* renderer)
{

	// ...
}

std::vector<Bullet*> BulletManagerbullets;
