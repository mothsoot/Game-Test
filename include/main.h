#pragma once

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;
using std::string;
#include <sstream>
using std::stringstream;
#include <cmath>

#include "screen.h"
#include "player.h"
#include "items.h"
#include "timer.h"
#include "math.h"

enum Key {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    NONE
};

void debugText(Player player, Screen screen);
