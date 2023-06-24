#pragma once

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;
#include <cmath>

#include <SDL.h>
#include <SDL_image.h>

#include "screen.h"
#include "player.h"
#include "timer.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// input directions
enum KEY_INPUT {KEY_LEFT = 1, KEY_RIGHT = 2, KEY_UP = 3, KEY_DOWN = 4, KEY_QUIT = 5};

// sprite directions
#define SPRITE_LEFT {29, 0, 29, 39}; // x coord, y coord, image width, image height
#define SPRITE_RIGHT {0, 0, 29, 39};
#define SPRITE_UP_LEFT {29 * 3, 0, 29, 39};
#define SPRITE_UP_RIGHT {29 * 2, 0, 29, 39};
#define SPRITE_DOWN_LEFT {29 * 5, 0, 29, 39};
#define SPRITE_DOWN_RIGHT {29 * 4, 0, 29, 39};
#define SPRITE_SKID_LEFT {29 * 6, 0, 29, 39};
#define SPRITE_SKID_RIGHT {29 * 7, 0, 20, 39};

struct Tile {
	float angle; // 0-256 (0-FF in hex)

	bool flagged;
};

void handleEvent(SDL_Event e, Player &player);

int getInput(SDL_Event e);
