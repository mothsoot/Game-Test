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

const int MAX_RINGS = 10;
const int MAX_TILES = 20;

const Position startPos = {200, 200};

const Position ringsMapping[10] = {
	{50, 150},
	{50, 180},
	{60, 180},
	{70, 180},
	{80, 180},
	{120, 180},
	{200, 180},
	{210, 180},
	{220, 180},
	{230, 180}
};

/*const Position tileMappings[MAX_TILES] = {
	{10, 235},
	{20, 235},
	{30, 235},
};*/

void debugText(Player player, Camera cam, Screen scr);
