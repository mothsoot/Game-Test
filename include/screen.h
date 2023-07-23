#pragma once

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::nothrow;
#include <fstream>
using std::ifstream;

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "math.h"

const int SCREEN_WIDTH = 320;
const int SCREEN_HEIGHT = 224;

const int LEVEL_WIDTH = 500;
const int LEVEL_HEIGHT = 300;

// player sprites
const SDL_Rect PLAYER_SPRITES_IDLE[1] = {
    {0, 3, 22, 33}
};
const SDL_Rect PLAYER_SPRITES_WALK[8] = {
    {105, 1, 23, 34},
    {128, 2, 25, 33},
    {153, 2, 23, 33},
    {176, 0, 21, 36},
    {197, 2, 23, 33},
    {220, 2, 25, 33},
    {245, 2, 23, 24},
    {268, 0, 21, 36}
};
const SDL_Rect PLAYER_SPRITES_LOOKUP[1] = {
    {22, 0, 24, 36}
};
const SDL_Rect PLAYER_SPRITES_CROUCH[1] = {
    {46, 10, 28, 26}
};
const SDL_Rect PLAYER_SPRITES_SKID[1] = {
    {74, 0, 31, 36}
};
const SDL_Rect PLAYER_SPRITES_JUMP[2] = {
    {289, 0, 27, 42},
    {316, 0, 27, 39},
};

// ring sprites
const SDL_Rect RING_SPRITES[4] = {
    {0, 0, 16, 16},
    {16, 0, 12, 16},
    {28, 0, 8, 16},
    {36, 0, 12, 16}
};

bool openFile();

class Screen {
    public:
        Screen() {}
        ~Screen() {}

        enum Mode {
            TITLE,
            GAME
        };

        SDL_Window* window;
        SDL_Renderer* renderer;
        TTF_Font* font;

        SDL_Texture* textTexture;
        SDL_Texture* bgTexture;
        SDL_Texture* playerTexture;
        SDL_Texture* ringTexture;

        SDL_Colour textColour = {0, 0, 0}; // black

        bool startUp();
        void shutDown();

        void drawSprite(int x, int y, SDL_Rect sprite, SDL_Texture* tex, SDL_RendererFlip flips = SDL_FLIP_NONE);
        void drawText(int x, int y);
        void drawTile();
        void drawBG(int x, int y, SDL_Rect cam);

        void prep();
        void present();

        SDL_Texture* loadPNG(string file);
        SDL_Texture* loadText(string text);

    private:

};

// camera stuff :P
class Camera {
    public:
        Camera();
        ~Camera() {}

        Position pos;

        SDL_Rect c;
        // int x, y, w, h

        Hitbox hitbox;

        void update(Position playerPos);
};