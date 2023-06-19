#ifndef _ECS_TAG_H
#define _ECS_TAG_H

namespace ECS
{
	enum class Tag
	{
		UNDEFINED = -1,
		PLAYER = 0,
		ENEMY = 1,
		BULLET_PLAYER = 2,
		BULLET_ENEMY = 3,
		PLAYFIELD = 10,
		UI_TEXT = 100
	};
}

#endif // _ECS_TAG_H