#pragma once

#include "screen.h"

class InputHandler {
	public:
		InputHandler();
		~InputHandler() {}

		void keyState(SDL_Event e);
		void mouseState(SDL_Event e);

		// keyboard
		bool isUp() { return up; }
		bool isDown() { return down; }
		bool isLeft() { return left; }
		bool isRight() { return right; }
		bool isSpace() { return space; }
		bool isNone();
		bool isAny();

		// mouse
		bool isMouseLeft() { return mouseLeft; }
		bool isMouseRight() { return mouseRight; }
		bool isAnyMouse();

		Position getMousePos() { return mousePos; }

	private:
		void reset();

		// keyboard
		bool up, down, left, right, space;

		// mouse
		bool mouseLeft, mouseRight;
		Position mousePos;
};