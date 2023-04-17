#include "InputHandler.h"

namespace InputHandler
{
	bool isDown_W, firstTap_W;
	bool isDown_A, firstTap_A;
	bool isDown_S, firstTap_S;
	bool isDown_D, firstTap_D;
	bool isDown_Z, firstTap_Z;

	bool isDown_ESCAPE, firstTap_ESCAPE;
	bool isDown_LSHIFT, firstTap_LSHIFT;
	bool isDown_LCTRL, firstTap_LCTRL;
	bool isDown_RETURN, firstTap_RETURN;

	bool isDown_UP, firstTap_UP;
	bool isDown_DOWN, firstTap_DOWN;
	bool isDown_LEFT, firstTap_LEFT;
	bool isDown_RIGHT, firstTap_RIGHT;

	bool GetKeyTap(InputKey key)
	{
		switch (key)
		{
		case InputHandler::KEY_W: return firstTap_W;
		case InputHandler::KEY_A: return firstTap_A;
		case InputHandler::KEY_S: return firstTap_S;
		case InputHandler::KEY_D: return firstTap_D;
		case InputHandler::KEY_Z: return firstTap_Z;

		case InputHandler::KEY_ESCAPE: return firstTap_ESCAPE;
		case InputHandler::KEY_LSHIFT: return firstTap_LSHIFT;
		case InputHandler::KEY_LCTRL:  return firstTap_LCTRL;
		case InputHandler::KEY_RETURN: return firstTap_RETURN;

		case InputHandler::KEY_UP:    return firstTap_UP;
		case InputHandler::KEY_DOWN:  return firstTap_DOWN;
		case InputHandler::KEY_LEFT:  return firstTap_LEFT;
		case InputHandler::KEY_RIGHT: return firstTap_RIGHT;
		}

		return false;
	}

	bool GetKeyDown(InputKey key)
	{
		switch (key)
		{
		case InputHandler::KEY_W: return isDown_W;
		case InputHandler::KEY_A: return isDown_A;
		case InputHandler::KEY_S: return isDown_S;
		case InputHandler::KEY_D: return isDown_D;
		case InputHandler::KEY_Z: return isDown_Z;

		case InputHandler::KEY_ESCAPE: return isDown_ESCAPE;
		case InputHandler::KEY_LSHIFT: return isDown_LSHIFT;
		case InputHandler::KEY_LCTRL:  return isDown_LCTRL;
		case InputHandler::KEY_RETURN: return isDown_RETURN;

		case InputHandler::KEY_UP:    return isDown_UP;
		case InputHandler::KEY_DOWN:  return isDown_DOWN;
		case InputHandler::KEY_LEFT:  return isDown_LEFT;
		case InputHandler::KEY_RIGHT: return isDown_RIGHT;
		}

		return false;
	}
}