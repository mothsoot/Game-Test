#pragma once

#include <iostream>
using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::string;
#include <sstream>
using std::stringstream;

#include "screen.h"
#include "input.h"
#include "player.h"
#include "items.h"
#include "timer.h"

void update(Object* obj);
void draw(Object* obj, Screen scr, Camera cam);
void destroy(Object* obj);

void debugText(Player player, Camera cam, Screen scr);
