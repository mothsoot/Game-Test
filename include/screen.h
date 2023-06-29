#pragma once

#include <SDL.h>
#include <SDL_image.h>

#include "main.h"

const int SCREEN_WIDTH = 320;
const int SCREEN_HEIGHT = 224;

// VIEW BORDERS
const int H_BORDER_LEFT = 144;
const int H_BORDER_RIGHT = 160;

const int V_FOCAL_POINT = 96;
const int V_BORDER_TOP = V_FOCAL_POINT - 32;
const int V_BORDER_BOTTOM = V_FOCAL_POINT + 32;
// CHANGES FROM LOOKING UP/DOWN!! MESS WITH IT 

// if player on ground
const int CAMERA_TOP_SPEED = 16;

// forward declaration
class Player;

bool startUp(SDL_Window* &window, SDL_Renderer* &renderer, SDL_Texture* &texture);
void drawPlayer(SDL_Renderer* renderer, SDL_Texture* texture, Player player);
void shutDown(SDL_Window* &window, SDL_Renderer* &renderer, SDL_Texture* &texture);

void prep(SDL_Renderer* renderer);
void present(SDL_Renderer* renderer);

SDL_Texture *loadTexture(SDL_Renderer* renderer);

// void loadSprites();
// void drawSprite();
// void drawTile();