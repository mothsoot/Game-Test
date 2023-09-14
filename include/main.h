#pragma once

#include <sstream>
using std::stringstream;

#include "screen.h"
#include "tile.h"
#include "math.h"
#include "input.h"
#include "player.h"
#include "items.h"
#include "timer.h"

int level;

const Position startPos = {200, 200};

void menu(Screen &screen, Camera cam, bool &quit);
void game(Screen &screen, Camera cam, bool &quit);

void debugText(Player player, Camera cam, Screen scr);
