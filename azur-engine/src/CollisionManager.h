#ifndef _COLLISION_MANAGER_H
#define _COLLISION_MANAGER_H

#include <vector>

#include "Components.h"

#include "AzurMath.h"

class CollisionManager
{
public:
	static void Update();
	static void AddCollider(ColliderComponent* collider);
	static void RemoveCollider(ColliderComponent* collider);

private:
	static std::pair<vector2float, vector2float> find_closest_collision_border_point(ColliderComponent* collider0, ColliderComponent* collider1);

private:
	static std::vector<ColliderComponent*> colliders;

};


#endif // _COLLISION_MANAGER_H