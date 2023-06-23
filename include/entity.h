#pragma once

#include "main.h"

enum TYPE {
    PLAYER,
    ENEMY
};

class Entity {
    public:
        Entity();
        ~Entity();

        Position pos;

        SDL_Rect sprite;
};