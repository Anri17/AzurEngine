#ifndef _COLLISION_SYSTEM_H
#define _COLLISION_SYSTEM_H

#include <vector>

#include "./../AzurLib.h"
#include "./../ECS.h"
#include "./../Components.h"

class CollisionSystem : public ECS::System<CollisionSystem>
{
public:
	CollisionSystem();
	
	void Init() override;
	void Update() override;
	void Render(SDL_Renderer* renderer) override;

private:
	void set_collision_status(Collider* collider0, Collider* collider1);

	std::vector<Entity*>* entities;
};


#endif // _COLLISION_SYSTEM_H