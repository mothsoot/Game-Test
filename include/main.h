#pragma once

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;
#include <cmath>

#include "screen.h"
#include "player.h"
#include "timer.h"

// sprite directions
#define SPRITE {0, 0, 29, 39}; // x coord, y coord, image width, image height
#define SPRITE_UP {29, 0, 29, 39};
#define SPRITE_DOWN {29 * 2, 0, 29, 39};
#define SPRITE_SKID {29 * 3, 0, 29, 39};