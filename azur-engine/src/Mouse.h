#ifndef _MOUSE_H
#define _MOUSE_H

#include <SDL.h>

class Mouse
{
public:
	Mouse();
	virtual ~Mouse();

	void Update();

	Uint32 MouseState;
	int xPos;
	int yPos;
};



#endif // !_MOUSE_H

