#pragma once

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;
using std::string;
#include <sstream>
using std::stringstream;

#include "screen.h"
#include "player.h"
#include "items.h"
#include "timer.h"
#include "math.h"

class Screen;

void debugText(Player player, Screen screen);
