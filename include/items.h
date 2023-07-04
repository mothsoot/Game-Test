#pragma once

#include "object.h"
#include "screen.h"

class Ring: public Object {
    public:
        const int GRAVITY = 0.09375; // 24 subpixels

        Ring();

        void draw(Screen screen);

    private:
};

class Spring: public Object {
    public:
        Spring();
};

