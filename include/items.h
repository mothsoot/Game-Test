#pragma once

#include "object.h"

class Ring: public Object {
    public:
        const int GRAVITY = 0.09375; // 24 subpixels

        Ring(Position pos = {0, 0}, SDL_Texture* tex = nullptr): Object(pos, tex) {}

        void create(Position p, SDL_Texture* tex);
        virtual void update();
        virtual void animate();

    private:

};