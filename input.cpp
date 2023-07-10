#include "input.h"

InputHandler::InputHandler()
{
	reset();
}

void InputHandler::reset()
{
	up = false;
	down = false;
	left = false;
	right = false;
	space = false;
}

void InputHandler::keyState(SDL_Event e)
{
    switch(e.type) {
		case SDL_KEYDOWN:
			switch(e.key.keysym.sym) {
				case SDLK_UP:
					up = true;
					break;
				case SDLK_DOWN:
					down = true;
					break;
				case SDLK_LEFT:
					left = true;
					break;
				case SDLK_RIGHT:
					right = true;
					break;
				case SDLK_SPACE:
					space = true;
					break;
				default:
					break;
			}
			break;

		case SDL_KEYUP:
			switch(e.key.keysym.sym) {
				case SDLK_UP:
					up = false;
					break;
				case SDLK_DOWN:
					down = false;
					break;
				case SDLK_LEFT:
					left = false;
					break;
				case SDLK_RIGHT:
					right = false;
					break;
				case SDLK_SPACE:
					space = false;
					break;
				default:
					break;
			}
			break;
	}
}

bool InputHandler::isNone()
{
	if(!isUp() && !isDown() && !isLeft() && !isRight() && !isSpace()) {
		return true;
	}
	return false;
}