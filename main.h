#pragma once

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;
#include <cmath>
#include "windows.h"

#include <SDL.h>
#include <SDL_image.h>

#include "player.h"

// input directions
enum KEY_INPUT { LEFT = 1, RIGHT = 2, UP = 3, DOWN = 4, QUIT = 5, NONE = 6 };

// sprite directions
#define SPRITE_LEFT {29, 0, 29, 39}; // x coord, y coord, image width, image height
#define SPRITE_RIGHT {0, 0, 29, 39};
#define SPRITE_UP_LEFT {29 * 3, 0, 29, 39};
#define SPRITE_UP_RIGHT {29 * 2, 0, 29, 39};
#define SPRITE_DOWN_LEFT {29 * 5, 0, 29, 39};
#define SPRITE_DOWN_RIGHT {29 * 4, 0, 29, 39};
#define SPRITE_SKID_LEFT {29 * 6, 0, 29, 39};
#define SPRITE_SKID_RIGHT {29 * 7, 0, 20, 39};

const int FPS = 60;
const int SKIP_TICKS = 1000 / FPS;

struct Player;

struct tile {
	float angle; // 0-256 (0-FF in hex)
};

//The application time based timer
class timer
{
    public:
		//Initializes variables
		timer();

		//The various clock actions
		void start();
		void stop();
		void pause();
		void unpause();

		//Gets the timer's time
		Uint32 getTicks();

		//Checks the status of the timer
		bool isStarted();
		bool isPaused();

    private:
		//The clock time when the timer started
		Uint32 mStartTicks;

		//The ticks stored when the timer was paused
		Uint32 mPausedTicks;

		//The timer status
		bool mPaused;
		bool mStarted;
};

void startUp(SDL_Window* &window, SDL_Renderer* &renderer, SDL_Surface* &image, SDL_Texture* &texture);
void render(SDL_Renderer* renderer, SDL_Texture* texture, Player player);
void shutDown(SDL_Window* &window, SDL_Renderer* &renderer, SDL_Texture* &texture);
SDL_Rect spriteDirection(SDL_Event e);
void movement(int input, Player &player);

void handleEvent(SDL_Event e, Player &player);
void move(float time, Player &player);

int getInput(SDL_Event e);
//bool isRight();
//bool isLeft();
