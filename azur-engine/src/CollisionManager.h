#ifndef _COLLISION_MANAGER_H
#define _COLLISION_MANAGER_H

#include <vector>

#include "ECS.h"

#include "AzurLib.h"


class CollisionSystem : public ECS::SystemBase
{
public:
	void Update() override;
	void Render(SDL_Renderer* renderer) override;

	void AddCollider(ECS::Position* position, ECS::Collider* collider);

	void RemoveCollider(ECS::Position* position, ECS::Collider* collider);
	void DeleteNullComponents() override;

private:
	std::pair<vector2float, vector2float> find_closest_collision_border_point(ECS::Collider* collider0, ECS::Collider* collider1);
	void set_collision_status(ECS::Collider* collider0, ECS::Collider* collider1);

	std::vector<std::pair<ECS::Position*, ECS::Collider*>> colliders;
};


#endif // _COLLISION_MANAGER_H