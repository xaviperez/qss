#pragma once

#include "SDL.h"

class Input {

	static bool _up;
	static bool _down;
	static bool _right;
	static bool _left;
	static bool _fire;

public:
	static void keyUp(SDL_Keysym keysym);
	static void keyDown(SDL_Keysym keysym);
	static float getHorizontalAxis();
	static float getVerticalAxis();
	inline static bool isButtonDown() { return Input::_fire; }
};