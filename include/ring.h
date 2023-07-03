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

