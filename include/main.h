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

const Position startPos = {200, 200};

Position ringMappings[MAX_RINGS] = {
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

void debugText(Player player, Camera cam, Screen scr);
