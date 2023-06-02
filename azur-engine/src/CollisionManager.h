#ifndef _COLLISION_MANAGER_H
#define _COLLISION_MANAGER_H

#include <vector>

#include "ECS.h"

#include "AzurLib.h"

class CollisionManager
{
public:
	static void Update();
	static void Render(SDL_Renderer* renderer);

	static void AddCollider(Position* position, Collider* collider);

	static void RemoveCollider(Position* position, Collider* collider);

private:
	static std::pair<vector2float, vector2float> find_closest_collision_border_point(Collider* collider0, Collider* collider1);
	static void set_collision_status(Collider* collider0, Collider* collider1);
private:
	static std::vector<std::pair<Position*, Collider*>> colliders;

};


#endif // _COLLISION_MANAGER_H