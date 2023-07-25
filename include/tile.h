#pragma once;

#include "math.h"
#include "screen.h"
#include "object.h"

enum TILE_TYPE {
    TILE_NONE,
    TILE_TOPSOLID, // downward sensors
    TILE_SIDEBOTTOMSOLID, // sideways/upward sensors
    TILE_FULLSOLID // all sensors
};

class Tile {
    // 10x10 pixels
    public:
        Tile();
        ~Tile() {}

        void create(Position p, SDL_Texture* tex);
        void destroy();
        void draw(Screen screen, Camera cam);

        Position pos;

        int ID;
        int type;

        Sprite sprite;
        Hitbox hitbox;

    private:
    
};