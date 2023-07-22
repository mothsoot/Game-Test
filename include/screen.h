#pragma once

#include <iostream>
using std::cerr;
using std::endl;
using std::string;

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "math.h"

const int SCREEN_WIDTH = 320;
const int SCREEN_HEIGHT = 224;

const int LEVEL_WIDTH = 500;
const int LEVEL_HEIGHT = 300;

// VIEW BORDERS FOR PLAYER TO STAY IN, AREA INSIDE CAMERA
const int H_BORDER_LEFT = 144;
const int H_BORDER_RIGHT = 160;

const int V_FOCAL_POINT = 96;
const int V_BORDER_TOP = V_FOCAL_POINT - 32;
const int V_BORDER_BOTTOM = V_FOCAL_POINT + 32;
// CHANGES FROM LOOKING UP/DOWN!! MESS WITH IT 

// if player on ground
const int CAMERA_TOP_SPEED = 16;

// player sprite
const SDL_Rect SPRITE = {0, 3, 22, 33}; // {0, 0, 29, 39}; // x coord, y coord, image width, image height
const SDL_Rect SPRITE_UP = {22 , 0, 24, 36}; // {29, 0, 29, 39};
const SDL_Rect SPRITE_DOWN = {46, 10, 28, 26}; // {29 * 2, 0, 29, 39};
const SDL_Rect SPRITE_SKID = {46 + 28, 0, 31, 36}; // {29 * 3, 0, 29, 39};

// ring sprites
const SDL_Rect SPRITE_RING_1 = {0, 0, 16, 16};
const SDL_Rect SPRITE_RING_2 = {24, 0, 16, 16};
const SDL_Rect SPRITE_RING_3 = {48, 0, 8, 16};
const SDL_Rect SPRITE_RING_4 = {64, 0, 16, 16};

class Screen {
    public:
        Screen() {}
        ~Screen() {}

        enum Mode {
            TITLE,
            GAME
        };

        SDL_Window* window = nullptr;
        SDL_Renderer* renderer = nullptr;
        TTF_Font* font = nullptr;

        SDL_Texture* textTexture = nullptr;
        SDL_Texture* bgTexture = nullptr;

        SDL_Colour textColour = {0, 0, 0}; // black

        bool startUp();
        void shutDown();

        void drawSprite(int x, int y, SDL_Rect sprite, SDL_Texture* tex, SDL_RendererFlip flips = SDL_FLIP_NONE);
        void drawText(int x, int y);
        void drawTile();
        void drawBG(SDL_Rect cam);

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

        SDL_Rect c;
        // int x, y, w, h

        Hitbox hitbox;

        void update(Position playerPos);
};