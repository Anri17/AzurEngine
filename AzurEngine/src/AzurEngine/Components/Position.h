#ifndef _POSITION_COMPONENT_H
#define _POSITION_COMPONENT_H

#include <string>
#include <SDL.h>
#include <SDL_image.h>

#include ".\..\ECS.h"

struct Position : public ECS::Component {
	float x = 0.0f;
	float y = 0.0f;
};

#endif // _POSITION_COMPONENT_H