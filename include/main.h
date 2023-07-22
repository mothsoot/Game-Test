#pragma once

#include <iostream>
using std::cerr;
using std::endl;
using std::string;
using std::nothrow;
#include <sstream>
using std::stringstream;

#include "screen.h"
#include "input.h"
#include "player.h"
#include "items.h"
#include "timer.h"

int MAX_RINGS = 10;

void create(Object* obj, int x, int y, SDL_Texture* spriteTex);
void update(Object* obj);
void draw(Object* obj, Screen scr, Camera cam);
void destroy(Object* obj);

void debugText(Player player, Camera cam, Screen scr);
