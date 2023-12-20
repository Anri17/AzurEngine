#ifndef _INPUT_HANDLER_H
#define _INPUT_HANDLER_H

#include <SDL.h>

namespace InputHandler
{
	enum InputKey
	{
		KEY_A,
		KEY_B,
		KEY_C,
		KEY_D,
		KEY_E,
		KEY_F,
		KEY_G,
		KEY_H,
		KEY_I,
		KEY_J,
		KEY_K,
		KEY_L,
		KEY_M,
		KEY_N,
		KEY_O,
		KEY_P,
		KEY_Q,
		KEY_R,
		KEY_S,
		KEY_T,
		KEY_U,
		KEY_V,
		KEY_W,
		KEY_X,
		KEY_Y,
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

	extern void UpdateResetFirstTaps();

	// These are the update fuctions for the chosen API, SDL
	extern void UpdateSDLKeydownEvents(SDL_Keycode sdl_keycode);
	extern void UpdateSDLKeyupEvents(SDL_Keycode sdl_keycode);

	extern bool GetKeyTap(InputKey key);
	extern bool GetKeyDown(InputKey key);
};

#endif // _INPUT_HANDLER_H
