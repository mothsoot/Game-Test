#pragma once

#include "main.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// forward declaration
class Player;

bool startUp(SDL_Window* &window, SDL_Renderer* &renderer, SDL_Surface* &image, SDL_Texture* &texture);
void render(SDL_Renderer* renderer, SDL_Texture* texture, Player player);
void shutDown(SDL_Window* &window, SDL_Renderer* &renderer, SDL_Texture* &texture);

// void loadSprites();
// void drawSprite();
// void drawTile();