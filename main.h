#pragma once

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;
#include <cmath>
#include "windows.h"

#include <SDL.h>
#include <SDL_image.h>

#include "screen.h"
#include "player.h"
#include "timer.h"

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

// forward declaration
struct Player;

struct tile {
	float angle; // 0-256 (0-FF in hex)
};

void handleEvent(SDL_Event e, Player &player);
void move(float time, Player &player);

int getInput(SDL_Event e);
