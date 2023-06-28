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

// input directions
enum KEY_INPUT {KEY_LEFT = 1, KEY_RIGHT = 2, KEY_UP = 3, KEY_DOWN = 4, KEY_QUIT = 5};

// sprite directions
#define SPRITE {0, 0, 29, 39}; // x coord, y coord, image width, image height
#define SPRITE_UP {29, 0, 29, 39};
#define SPRITE_DOWN {29 * 2, 0, 29, 39};
#define SPRITE_SKID {29 * 3, 0, 29, 39};

void handleEvent(SDL_Event e, Player &player);

int getInput(SDL_Event e);
