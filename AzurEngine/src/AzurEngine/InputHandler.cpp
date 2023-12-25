#include "InputHandler.h"

namespace InputHandler {
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

	void reset_first_taps() {
		firstTap_A = false;
		firstTap_B = false;
		firstTap_C = false;
		firstTap_D = false;
		firstTap_E = false;
		firstTap_F = false;
		firstTap_G = false;
		firstTap_H = false;
		firstTap_I = false;
		firstTap_J = false;
		firstTap_K = false;
		firstTap_L = false;
		firstTap_M = false;
		firstTap_N = false;
		firstTap_O = false;
		firstTap_P = false;
		firstTap_Q = false;
		firstTap_R = false;
		firstTap_S = false;
		firstTap_T = false;
		firstTap_U = false;
		firstTap_V = false;
		firstTap_W = false;
		firstTap_X = false;
		firstTap_Y = false;
		firstTap_Z = false;

		firstTap_LSHIFT = false;
		firstTap_LCTRL = false;
		firstTap_ESCAPE = false;
		firstTap_RETURN = false;

		firstTap_1 = false;
		firstTap_2 = false;
		firstTap_3 = false;
		firstTap_4 = false;
		firstTap_5 = false;
		firstTap_6 = false;
		firstTap_7 = false;
		firstTap_8 = false;
		firstTap_9 = false;
		firstTap_0 = false;

		firstTap_UP = false;
		firstTap_DOWN = false;
		firstTap_LEFT = false;
		firstTap_RIGHT = false;
	}

	void process_sdl_event_keydown(SDL_Keycode sdl_keycode) {
		switch (sdl_keycode) {
		case SDLK_a: if (!InputHandler::isDown_A) { InputHandler::isDown_A = InputHandler::firstTap_A = true; } break;
		case SDLK_b: if (!InputHandler::isDown_B) { InputHandler::isDown_B = InputHandler::firstTap_B = true; } break;
		case SDLK_c: if (!InputHandler::isDown_C) { InputHandler::isDown_C = InputHandler::firstTap_C = true; } break;
		case SDLK_d: if (!InputHandler::isDown_D) { InputHandler::isDown_D = InputHandler::firstTap_D = true; } break;
		case SDLK_e: if (!InputHandler::isDown_E) { InputHandler::isDown_E = InputHandler::firstTap_E = true; } break;
		case SDLK_f: if (!InputHandler::isDown_F) { InputHandler::isDown_F = InputHandler::firstTap_F = true; } break;
		case SDLK_g: if (!InputHandler::isDown_G) { InputHandler::isDown_G = InputHandler::firstTap_G = true; } break;
		case SDLK_h: if (!InputHandler::isDown_H) { InputHandler::isDown_H = InputHandler::firstTap_H = true; } break;
		case SDLK_i: if (!InputHandler::isDown_I) { InputHandler::isDown_I = InputHandler::firstTap_I = true; } break;
		case SDLK_j: if (!InputHandler::isDown_J) { InputHandler::isDown_J = InputHandler::firstTap_J = true; } break;
		case SDLK_k: if (!InputHandler::isDown_K) { InputHandler::isDown_K = InputHandler::firstTap_K = true; } break;
		case SDLK_l: if (!InputHandler::isDown_L) { InputHandler::isDown_L = InputHandler::firstTap_L = true; } break;
		case SDLK_m: if (!InputHandler::isDown_M) { InputHandler::isDown_M = InputHandler::firstTap_M = true; } break;
		case SDLK_n: if (!InputHandler::isDown_N) { InputHandler::isDown_N = InputHandler::firstTap_N = true; } break;
		case SDLK_o: if (!InputHandler::isDown_O) { InputHandler::isDown_O = InputHandler::firstTap_O = true; } break;
		case SDLK_p: if (!InputHandler::isDown_P) { InputHandler::isDown_P = InputHandler::firstTap_P = true; } break;
		case SDLK_q: if (!InputHandler::isDown_Q) { InputHandler::isDown_Q = InputHandler::firstTap_Q = true; } break;
		case SDLK_r: if (!InputHandler::isDown_R) { InputHandler::isDown_R = InputHandler::firstTap_R = true; } break;
		case SDLK_s: if (!InputHandler::isDown_S) { InputHandler::isDown_S = InputHandler::firstTap_S = true; } break;
		case SDLK_t: if (!InputHandler::isDown_T) { InputHandler::isDown_T = InputHandler::firstTap_T = true; } break;
		case SDLK_u: if (!InputHandler::isDown_U) { InputHandler::isDown_U = InputHandler::firstTap_U = true; } break;
		case SDLK_v: if (!InputHandler::isDown_V) { InputHandler::isDown_V = InputHandler::firstTap_V = true; } break;
		case SDLK_w: if (!InputHandler::isDown_W) { InputHandler::isDown_W = InputHandler::firstTap_W = true; } break;
		case SDLK_x: if (!InputHandler::isDown_X) { InputHandler::isDown_X = InputHandler::firstTap_X = true; } break;
		case SDLK_y: if (!InputHandler::isDown_Y) { InputHandler::isDown_Y = InputHandler::firstTap_Y = true; } break;
		case SDLK_z: if (!InputHandler::isDown_Z) { InputHandler::isDown_Z = InputHandler::firstTap_Z = true; } break;

		case SDLK_LSHIFT: if (!InputHandler::isDown_LSHIFT) { InputHandler::isDown_LSHIFT = InputHandler::firstTap_LSHIFT = true; } break;
		case SDLK_LCTRL:  if (!InputHandler::isDown_LCTRL) { InputHandler::isDown_LCTRL = InputHandler::firstTap_LCTRL = true; } break;
		case SDLK_ESCAPE: if (!InputHandler::isDown_ESCAPE) { InputHandler::isDown_ESCAPE = InputHandler::firstTap_ESCAPE = true; } break;
		case SDLK_RETURN: if (!InputHandler::isDown_RETURN) { InputHandler::isDown_RETURN = InputHandler::firstTap_RETURN = true; } break;

		case SDLK_1: if (!InputHandler::isDown_1) { InputHandler::isDown_1 = InputHandler::firstTap_1 = true; } break;
		case SDLK_2: if (!InputHandler::isDown_2) { InputHandler::isDown_2 = InputHandler::firstTap_2 = true; } break;
		case SDLK_3: if (!InputHandler::isDown_3) { InputHandler::isDown_3 = InputHandler::firstTap_3 = true; } break;
		case SDLK_4: if (!InputHandler::isDown_4) { InputHandler::isDown_4 = InputHandler::firstTap_4 = true; } break;
		case SDLK_5: if (!InputHandler::isDown_5) { InputHandler::isDown_5 = InputHandler::firstTap_5 = true; } break;
		case SDLK_6: if (!InputHandler::isDown_6) { InputHandler::isDown_6 = InputHandler::firstTap_6 = true; } break;
		case SDLK_7: if (!InputHandler::isDown_7) { InputHandler::isDown_7 = InputHandler::firstTap_7 = true; } break;
		case SDLK_8: if (!InputHandler::isDown_8) { InputHandler::isDown_8 = InputHandler::firstTap_8 = true; } break;
		case SDLK_9: if (!InputHandler::isDown_9) { InputHandler::isDown_9 = InputHandler::firstTap_9 = true; } break;
		case SDLK_0: if (!InputHandler::isDown_0) { InputHandler::isDown_0 = InputHandler::firstTap_0 = true; } break;

		case SDLK_UP:    if (!InputHandler::isDown_UP) { InputHandler::isDown_UP = InputHandler::firstTap_UP = true; } break;
		case SDLK_DOWN:  if (!InputHandler::isDown_DOWN) { InputHandler::isDown_DOWN = InputHandler::firstTap_DOWN = true; } break;
		case SDLK_LEFT:  if (!InputHandler::isDown_LEFT) { InputHandler::isDown_LEFT = InputHandler::firstTap_LEFT = true; } break;
		case SDLK_RIGHT: if (!InputHandler::isDown_RIGHT) { InputHandler::isDown_RIGHT = InputHandler::firstTap_RIGHT = true; } break;
		}
	}

	void process_sdl_event_keyup(SDL_Keycode sdl_keycode) {
		switch (sdl_keycode) {
		case SDLK_a: InputHandler::isDown_A = false; break;
		case SDLK_b: InputHandler::isDown_B = false; break;
		case SDLK_c: InputHandler::isDown_C = false; break;
		case SDLK_d: InputHandler::isDown_D = false; break;
		case SDLK_e: InputHandler::isDown_E = false; break;
		case SDLK_f: InputHandler::isDown_F = false; break;
		case SDLK_g: InputHandler::isDown_G = false; break;
		case SDLK_h: InputHandler::isDown_H = false; break;
		case SDLK_i: InputHandler::isDown_I = false; break;
		case SDLK_j: InputHandler::isDown_J = false; break;
		case SDLK_k: InputHandler::isDown_K = false; break;
		case SDLK_l: InputHandler::isDown_L = false; break;
		case SDLK_m: InputHandler::isDown_M = false; break;
		case SDLK_n: InputHandler::isDown_N = false; break;
		case SDLK_o: InputHandler::isDown_O = false; break;
		case SDLK_p: InputHandler::isDown_P = false; break;
		case SDLK_q: InputHandler::isDown_Q = false; break;
		case SDLK_r: InputHandler::isDown_R = false; break;
		case SDLK_s: InputHandler::isDown_S = false; break;
		case SDLK_t: InputHandler::isDown_T = false; break;
		case SDLK_u: InputHandler::isDown_U = false; break;
		case SDLK_v: InputHandler::isDown_V = false; break;
		case SDLK_w: InputHandler::isDown_W = false; break;
		case SDLK_x: InputHandler::isDown_X = false; break;
		case SDLK_y: InputHandler::isDown_Y = false; break;
		case SDLK_z: InputHandler::isDown_Z = false; break;

		case SDLK_LSHIFT: InputHandler::isDown_LSHIFT = false; break;
		case SDLK_LCTRL:  InputHandler::isDown_LCTRL = false; break;
		case SDLK_ESCAPE: InputHandler::isDown_ESCAPE = false; break;
		case SDLK_RETURN: InputHandler::isDown_RETURN = false; break;

		case SDLK_1: InputHandler::isDown_1 = false; break;
		case SDLK_2: InputHandler::isDown_2 = false; break;
		case SDLK_3: InputHandler::isDown_3 = false; break;
		case SDLK_4: InputHandler::isDown_4 = false; break;
		case SDLK_5: InputHandler::isDown_5 = false; break;
		case SDLK_6: InputHandler::isDown_6 = false; break;
		case SDLK_7: InputHandler::isDown_7 = false; break;
		case SDLK_8: InputHandler::isDown_8 = false; break;
		case SDLK_9: InputHandler::isDown_9 = false; break;
		case SDLK_0: InputHandler::isDown_0 = false; break;

		case SDLK_UP:    InputHandler::isDown_UP = false; break;
		case SDLK_DOWN:  InputHandler::isDown_DOWN = false; break;
		case SDLK_LEFT:  InputHandler::isDown_LEFT = false; break;
		case SDLK_RIGHT: InputHandler::isDown_RIGHT = false; break;
		}
	}

	bool get_key_tap(InputKey key) {
		switch (key) {
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

	bool get_key_down(InputKey key) {
		switch (key) {
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