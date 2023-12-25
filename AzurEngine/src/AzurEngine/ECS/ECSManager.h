#ifndef _ECS_MANAGER_H
#define _ECS_MANAGER_H

#include "Entity.h"
#include "Component.h"
#include "Tag.h"

// TODO: Take the entity Creation Methods outside of the ECS Folder
class CollisionSystem;


namespace ECS {
	// TODO: Hold a reference to the relevant systems. This should not be in the ECS namespace and Folder anyway...
	class ECSManager {
	public:
		static Entity* entity_add(Entity* entity);

		static void render(SDL_Renderer* renderer);
		static void update();
		static void entity_delete_all();

		static void entity_flag_for_deletion(Entity* entity);
		static void entities_flag_for_deletion_by_tag(Tag tag);

		// TODO: The entities will be moved to a scene object, together with the scenes. This is because entities are tied to a scene.
		static std::vector<Entity*>* get_entities_vector() { return &entities;  }
	private:
		static void entity_delete_flagged();

		static std::vector<Entity*> entities;
		static std::vector<Entity*> flagged_for_deletion;
	};
}

#endif // _ECS_MANAGER_H
