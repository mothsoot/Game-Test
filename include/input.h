#pragma once;

#include <SDL.h>

class Input {
    public:
        bool isUp(SDL_Event e);
        bool isDown(SDL_Event e);
        bool isLeft(SDL_Event e);
        bool isRight(SDL_Event e);

        bool up;
        bool down;
        bool left;
        bool right;
};

bool Input::isUp(SDL_Event e)
{
    if(e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        if(e.key.keysym.sym == SDLK_UP) {
            return true;
        }
    }
    return false;
}

bool Input::isDown(SDL_Event e)
{
    if(e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        if(e.key.keysym.sym == SDLK_DOWN) {
            return true;
        }
    }
    return false;
}

bool Input::isRight(SDL_Event e)
{
    if(e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        if(e.key.keysym.sym == SDLK_RIGHT) {
            return true;
        }
    }
    return false;
}

bool Input::isLeft(SDL_Event e)
{
    if(e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        if(e.key.keysym.sym == SDLK_LEFT) {
            return true;
        }
    }
    return false;
}

void clearInput(Input &input) {
    input.up = false;
    input.down = false;
    input.left = false;
    input.right = false;
}





