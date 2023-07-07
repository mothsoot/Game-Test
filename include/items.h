#pragma once

#include "object.h"

class Item: public Object {
    public:
        
};

class Ring: public Item {
    public:
        const int GRAVITY = 0.09375; // 24 subpixels

        Ring(int x, int y);


    private:
};

class Spring: public Item {
    public:
        Spring(int x, int y);
};

