#pragma once

#include "object.h"
#include "screen.h"

class Ring: public Object {
    public:
        Ring(): Object() {};

        void create();
        void draw(Screen screen);

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

void Ring::draw(Screen screen)
{
    screen.draw(pos.x, pos.y, sprite, flipSprite);
}

