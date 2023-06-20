#ifndef _INPUT_HANDLER_H
#define _INPUT_HANDLER_H

#include <SDL.h>

namespace InputHandler
{
	enum InputKey
	{
		KEY_W,
		KEY_A,
		KEY_S,
		KEY_D,
		KEY_Z,

		KEY_1,
		KEY_2,
		KEY_3,
		KEY_4,
		KEY_5,
		KEY_6,
		KEY_7,
		KEY_8,
		KEY_9,
		KEY_0,

		KEY_ESCAPE,
		KEY_LSHIFT,
		KEY_LCTRL,
		KEY_RETURN,

		KEY_UP,
		KEY_DOWN,
		KEY_LEFT,
		KEY_RIGHT,
	};

	extern bool GetKeyTap(InputKey key);
	extern bool GetKeyDown(InputKey key);

	// These are updated by the chosen API or Library's Event System (SDL KeyUp/KeyDown Events)
	extern bool isDown_W, firstTap_W;
	extern bool isDown_A, firstTap_A;
	extern bool isDown_S, firstTap_S;
	extern bool isDown_D, firstTap_D;
	extern bool isDown_Z, firstTap_Z;

	extern bool isDown_ESCAPE, firstTap_ESCAPE;
	extern bool isDown_LSHIFT, firstTap_LSHIFT;
	extern bool isDown_LCTRL,  firstTap_LCTRL;
	extern bool isDown_RETURN, firstTap_RETURN;
		   
	extern bool isDown_1, firstTap_1;
	extern bool isDown_2, firstTap_2;
	extern bool isDown_3, firstTap_3;
	extern bool isDown_4, firstTap_4;
	extern bool isDown_5, firstTap_5;
	extern bool isDown_6, firstTap_6;
	extern bool isDown_7, firstTap_7;
	extern bool isDown_8, firstTap_8;
	extern bool isDown_9, firstTap_9;
	extern bool isDown_0, firstTap_0;

	extern bool isDown_UP,	  firstTap_UP;
	extern bool isDown_DOWN,  firstTap_DOWN;
	extern bool isDown_LEFT,  firstTap_LEFT;
	extern bool isDown_RIGHT, firstTap_RIGHT;
};

#endif // _INPUT_HANDLER_H
