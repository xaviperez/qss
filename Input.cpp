#include "Input.h"

bool Input::_up = false;
bool Input::_down = false;
bool Input::_right = false;
bool Input::_left = false;
bool Input::_fire = false;

void Input::keyUp(SDL_Keysym keysym) {
	switch (keysym.sym) {
		case SDLK_UP:
		case SDLK_w:
			Input::_up = false;
			break;
		case SDLK_DOWN:
		case SDLK_s:
			Input::_down = false;
		case SDLK_RIGHT:
		case SDLK_d:
			Input::_right = false;
			break;
		case SDLK_LEFT:
		case SDLK_a:
			Input::_left = false;
			break;
		case SDLK_SPACE:
			Input::_fire = false;
			break;
	}
}

void Input::keyDown(SDL_Keysym keysym) {
	switch (keysym.sym) {
		case SDLK_UP:
		case SDLK_w:
			Input::_up = true;
			break;
		case SDLK_DOWN:
		case SDLK_s:
			Input::_down = true;
			break;
		case SDLK_RIGHT:
		case SDLK_d:
			Input::_right = true;
			break;
		case SDLK_LEFT:
		case SDLK_a:
			Input::_left = true;
			break;
		case SDLK_SPACE:
			Input::_fire = true;
			break;
	}
}

float Input::getHorizontalAxis() {
	float horizontalAxis = 0;

	if (Input::_left)
		horizontalAxis -= 1;

	if (Input::_right)
		horizontalAxis += 1;

	return horizontalAxis;
}

float Input::getVerticalAxis() {
	float verticalAxis = 0;

	if (Input::_up)
		verticalAxis -= 1;

	if (Input::_down)
		verticalAxis += 1;

	return verticalAxis;
}
