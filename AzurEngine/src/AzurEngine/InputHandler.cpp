#include "InputHandler.h"

namespace InputHandler
{
	bool isDown_A, firstTap_A;
	bool isDown_B, firstTap_B;
	bool isDown_C, firstTap_C;
	bool isDown_D, firstTap_D;
	bool isDown_E, firstTap_E;
	bool isDown_F, firstTap_F;
	bool isDown_G, firstTap_G;
	bool isDown_H, firstTap_H;
	bool isDown_I, firstTap_I;
	bool isDown_J, firstTap_J;
	bool isDown_K, firstTap_K;
	bool isDown_L, firstTap_L;
	bool isDown_M, firstTap_M;
	bool isDown_N, firstTap_N;
	bool isDown_O, firstTap_O;
	bool isDown_P, firstTap_P;
	bool isDown_Q, firstTap_Q;
	bool isDown_R, firstTap_R;
	bool isDown_S, firstTap_S;
	bool isDown_T, firstTap_T;
	bool isDown_U, firstTap_U;
	bool isDown_V, firstTap_V;
	bool isDown_W, firstTap_W;
	bool isDown_X, firstTap_X;
	bool isDown_Y, firstTap_Y;
	bool isDown_Z, firstTap_Z;

	bool isDown_1, firstTap_1;
	bool isDown_2, firstTap_2;
	bool isDown_3, firstTap_3;
	bool isDown_4, firstTap_4;
	bool isDown_5, firstTap_5;
	bool isDown_6, firstTap_6;
	bool isDown_7, firstTap_7;
	bool isDown_8, firstTap_8;
	bool isDown_9, firstTap_9;
	bool isDown_0, firstTap_0;

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
		case InputHandler::KEY_A: return firstTap_A;
		case InputHandler::KEY_B: return firstTap_B;
		case InputHandler::KEY_C: return firstTap_C;
		case InputHandler::KEY_D: return firstTap_D;
		case InputHandler::KEY_E: return firstTap_E;
		case InputHandler::KEY_F: return firstTap_F;
		case InputHandler::KEY_G: return firstTap_G;
		case InputHandler::KEY_H: return firstTap_H;
		case InputHandler::KEY_I: return firstTap_I;
		case InputHandler::KEY_J: return firstTap_J;
		case InputHandler::KEY_K: return firstTap_K;
		case InputHandler::KEY_L: return firstTap_L;
		case InputHandler::KEY_M: return firstTap_M;
		case InputHandler::KEY_N: return firstTap_N;
		case InputHandler::KEY_O: return firstTap_O;
		case InputHandler::KEY_P: return firstTap_P;
		case InputHandler::KEY_Q: return firstTap_Q;
		case InputHandler::KEY_R: return firstTap_R;
		case InputHandler::KEY_S: return firstTap_S;
		case InputHandler::KEY_T: return firstTap_T;
		case InputHandler::KEY_U: return firstTap_U;
		case InputHandler::KEY_V: return firstTap_V;
		case InputHandler::KEY_W: return firstTap_W;
		case InputHandler::KEY_X: return firstTap_X;
		case InputHandler::KEY_Y: return firstTap_Y;
		case InputHandler::KEY_Z: return firstTap_Z;

		case InputHandler::KEY_1: return firstTap_1;
		case InputHandler::KEY_2: return firstTap_2;
		case InputHandler::KEY_3: return firstTap_3;
		case InputHandler::KEY_4: return firstTap_4;
		case InputHandler::KEY_5: return firstTap_5;
		case InputHandler::KEY_6: return firstTap_6;
		case InputHandler::KEY_7: return firstTap_7;
		case InputHandler::KEY_8: return firstTap_8;
		case InputHandler::KEY_9: return firstTap_9;
		case InputHandler::KEY_0: return firstTap_0;

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
		case InputHandler::KEY_A: return isDown_A;
		case InputHandler::KEY_B: return isDown_B;
		case InputHandler::KEY_C: return isDown_C;
		case InputHandler::KEY_D: return isDown_D;
		case InputHandler::KEY_E: return isDown_E;
		case InputHandler::KEY_F: return isDown_F;
		case InputHandler::KEY_G: return isDown_G;
		case InputHandler::KEY_H: return isDown_H;
		case InputHandler::KEY_I: return isDown_I;
		case InputHandler::KEY_J: return isDown_J;
		case InputHandler::KEY_K: return isDown_K;
		case InputHandler::KEY_L: return isDown_L;
		case InputHandler::KEY_M: return isDown_M;
		case InputHandler::KEY_N: return isDown_N;
		case InputHandler::KEY_O: return isDown_O;
		case InputHandler::KEY_P: return isDown_P;
		case InputHandler::KEY_Q: return isDown_Q;
		case InputHandler::KEY_R: return isDown_R;
		case InputHandler::KEY_S: return isDown_S;
		case InputHandler::KEY_T: return isDown_T;
		case InputHandler::KEY_U: return isDown_U;
		case InputHandler::KEY_V: return isDown_V;
		case InputHandler::KEY_W: return isDown_W;
		case InputHandler::KEY_X: return isDown_X;
		case InputHandler::KEY_Y: return isDown_Y;
		case InputHandler::KEY_Z: return isDown_Z;

		case InputHandler::KEY_ESCAPE: return isDown_ESCAPE;
		case InputHandler::KEY_LSHIFT: return isDown_LSHIFT;
		case InputHandler::KEY_LCTRL:  return isDown_LCTRL;
		case InputHandler::KEY_RETURN: return isDown_RETURN;

		case InputHandler::KEY_1: return isDown_1;
		case InputHandler::KEY_2: return isDown_2;
		case InputHandler::KEY_3: return isDown_3;
		case InputHandler::KEY_4: return isDown_4;
		case InputHandler::KEY_5: return isDown_5;
		case InputHandler::KEY_6: return isDown_6;
		case InputHandler::KEY_7: return isDown_7;
		case InputHandler::KEY_8: return isDown_8;
		case InputHandler::KEY_9: return isDown_9;
		case InputHandler::KEY_0: return isDown_0;

		case InputHandler::KEY_UP:    return isDown_UP;
		case InputHandler::KEY_DOWN:  return isDown_DOWN;
		case InputHandler::KEY_LEFT:  return isDown_LEFT;
		case InputHandler::KEY_RIGHT: return isDown_RIGHT;
		}

		return false;
	}
}