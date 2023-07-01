#pragma once

#include "object.h"

class Ring: public Object {
    public:
        Ring(): Object() {};

        void create();
        void draw();
        
        int hRadius = 8;
        int wRadius = 8;

    private:
};

// FOR IN .CPP FILE
void Ring::create()
{
    type = TYPE_RING;

    setPos(10, 10);
    setRadius(8, 8);

    // sprite = RING;
}

void Ring::draw()
{
    //screen.draw(pos, sprite);
}

