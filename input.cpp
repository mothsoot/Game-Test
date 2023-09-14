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

	mouseLeft = false;
	mouseRight = false;
}

void InputHandler::keyState(SDL_Event e)
{
    switch(e.type) {
		case SDL_KEYDOWN:
			switch(e.key.keysym.sym) {
				case SDLK_UP:
				case SDLK_w:
					up = true;
					break;
				case SDLK_DOWN:
				case SDLK_s:
					down = true;
					break;
				case SDLK_LEFT:
				case SDLK_a:
					left = true;
					break;
				case SDLK_RIGHT:
				case SDLK_d:
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
				case SDLK_w:
					up = false;
					break;
				case SDLK_DOWN:
				case SDLK_s:
					down = false;
					break;
				case SDLK_LEFT:
				case SDLK_a:
					left = false;
					break;
				case SDLK_RIGHT:
				case SDLK_d:
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

void InputHandler::mouseState(SDL_Event e)
{
	switch (e.type) {
		case SDL_MOUSEBUTTONDOWN:
			switch (e.button.button) {
				case SDL_BUTTON_LEFT:
					mouseLeft = true;
					break;

				case SDL_BUTTON_RIGHT:
					mouseRight = true;
					break;
			}
			break;

		case SDL_MOUSEBUTTONUP:
			switch (e.button.button) {
				case SDL_BUTTON_LEFT:
					mouseLeft = false;
					break;
					
				case SDL_BUTTON_RIGHT:
					mouseRight = false;
					break;
			}
			break;

		case SDL_MOUSEMOTION:
			mousePos.set(e.motion.x, e.motion.y);
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

bool InputHandler::isAny()
{
	if(isUp() || isDown() || isLeft() || isRight() || isSpace()) {
		return true;
	}
	return false;
}

bool InputHandler::isAnyMouse()
{
	if(isMouseLeft() || isMouseRight()) {
		return true;
	}
	return false;
}