#pragma once

#include "main.h"

class Object {
    public:
        Object();
        ~Object();
        
        Position pos;

        SDL_Rect sprite;
};
