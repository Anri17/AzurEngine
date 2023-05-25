#ifndef _BULLET_POOL
#define _BULLET_POOL

#include <vector>

#include "ECS.h"
#include "BulletTemplate.h"

enum class BulletType
{
	 PLAYER_A,
	 BULLET_A
};

class BulletPool
{
public:
	static void Initialize();

private:
	// TODO: I am not sure if I want a vector of bullet templates or a vector of entityes
	// TODO: One one hand, having a vector of entitites wouyld allow me to just get thet ype of bullet that i wnat without having to initialize it
	// TODO: On the otehr hand, having a vector of template,s would also allow oto get the type of bulelt without having to build it.
	// TODO: I could lalso get a vector of vectors, and get the ttype of bullet from the vbector using hte correct index that is correspondeed of the bullet that the program watns at execution time.
	std::vector<Entity*> bullet_templates;

};

#endif // _BULLET_POOL
