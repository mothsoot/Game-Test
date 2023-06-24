#pragma once

#include "main.h"

enum TYPE {
    TYPE_PLAYER
};

class Entity {
    public:
        Entity();
        ~Entity();

        Position pos;

        SDL_Rect sprite;

};