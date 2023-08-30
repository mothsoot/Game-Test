#pragma once

#include "object.h"

const int MAX_RINGS = 10;

class Ring: public Object {
    public:
        const int GRAVITY = 0.09375; // 24 subpixels

        Ring(Position pos = {0, 0}, SDL_Texture* tex = nullptr): Object(pos, tex) {}

        void create(Position p, SDL_Texture* tex);
        virtual void update();
        virtual void animate();

    private:

};

bool createRingList(Ring* &ringList, Position ringMappings[], SDL_Texture* ringTexture);