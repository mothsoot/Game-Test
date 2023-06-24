#pragma once

#include "main.h"

// forward declaration
class Player;

bool startUp(SDL_Window* &window, SDL_Renderer* &renderer, SDL_Surface* &image, SDL_Texture* &texture);
void render(SDL_Renderer* renderer, SDL_Texture* texture, Player player);
void shutDown(SDL_Window* &window, SDL_Renderer* &renderer, SDL_Texture* &texture);

//void render( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );
