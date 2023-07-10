#pragma once

#include "screen.h"

class InputHandler {
	public:
		InputHandler();
		~InputHandler() {}

		void keyState(SDL_Event e);

		bool isUp() { return up; }
		bool isDown() { return down; }
		bool isLeft() { return left; }
		bool isRight() { return right; }
		bool isSpace() { return space; }
		bool isNone();

		void reset();

	private:
		bool up;
		bool down;
		bool left;
		bool right;
		bool space;
};