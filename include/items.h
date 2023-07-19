#pragma once

#include "object.h"

class Item: public Object {
    public:
};

class Ring: public Item {
    public:
        const int GRAVITY = 0.09375; // 24 subpixels
        //Ring();
        Ring(int x = 0, int y = 0);

        virtual void update();

        SDL_Rect ringSprites[4] = {
            SPRITE_RING_1,
            SPRITE_RING_2,
            SPRITE_RING_3,
            SPRITE_RING_4
        };
    private:
};

class Spring: public Item {
    public:
        Spring(int x, int y);
};

