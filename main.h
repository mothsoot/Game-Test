#pragma once

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

#include <SDL.h>
#include <SDL_image.h>

#include "player.h"

// input directions
enum INPUT { LEFT, RIGHT, UP, DOWN, QUIT, NONE };

// sprite directions
#define SPRITE_LEFT {29, 0, 29, 39}; // x coord, y coord, image width, image height
#define SPRITE_RIGHT {0, 0, 29, 39};
#define SPRITE_UP_LEFT {29 * 3, 0, 29, 39};
#define SPRITE_UP_RIGHT {29 * 2, 0, 29, 39};
#define SPRITE_DOWN_LEFT {29 * 5, 0, 29, 39};
#define SPRITE_DOWN_RIGHT {29 * 4, 0, 29, 39};

struct Player;

struct tile {
	float angle; // 0-256 (0-FF in hex)
};

void startUp(SDL_Window* &window, SDL_Renderer* &renderer, SDL_Surface* &sprite, SDL_Texture* &texture);
void render(SDL_Renderer* renderer, SDL_Texture* texture, Player player);
void shutDown(SDL_Window* &window, SDL_Renderer* &renderer, SDL_Texture* &texture);
int getInput();
SDL_Rect spriteDirection(int input);
void movement(int input, Player &player);
