#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

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

// player sprite
#define SPRITE {0, 0, 29, 39}; // x coord, y coord, image width, image height
#define SPRITE_UP {29, 0, 29, 39};
#define SPRITE_DOWN {29 * 2, 0, 29, 39};
#define SPRITE_SKID {29 * 3, 0, 29, 39};

// ring sprite
#define SPRITE_RING {0, 0, 16, 16};

// forward declaration
class Player;

class Screen {
    public:
        SDL_Window* window = nullptr;
        SDL_Renderer* renderer = nullptr;
        TTF_Font* font = nullptr;

        SDL_Texture* sonicSprites = nullptr;
        SDL_Texture* ringSprites = nullptr;
        SDL_Texture* textTexture = nullptr;

        SDL_Colour textColour = {0, 0, 0}; // black

        bool startUp();
        void drawSprite(int x, int y, SDL_Rect sprite, bool flipSprite);
        void drawSprite(int x, int y, SDL_Rect sprite);
        void shutDown();

        void drawText(int x, int y);

        void prep();
        void present();

        SDL_Texture* loadSprites(string file);
        SDL_Texture* loadText(string text);
    private:

};



