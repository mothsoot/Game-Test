#pragma once

#include "object.h"

const int MAX_RINGS = 10;

class Ring: public Object {
    public:
        Ring(Position pos = {0, 0}, SDL_Texture* tex = nullptr): Object(pos, tex) {}

        virtual void create(Position p, SDL_Texture* tex);
        virtual void update();
        virtual void animate();

    private:

};

Ring* createRingList(Position posMap[], SDL_Texture* tex);
Position* loadRingPosMap(string file);