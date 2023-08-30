#pragma once;

#include "math.h"
#include "screen.h"
#include "object.h"

const int MAX_TILES = 90;

enum TILE_ID {
    GRASS,
    GROUND,
    DIRT
};

enum TILE_TYPE {
    TILE_NONE,
    TILE_TOPSOLID, // downward sensors
    TILE_SIDEBOTTOMSOLID, // sideways/upward sensors
    TILE_FULLSOLID // all sensors
};

class Tile {
    // 16x16 pixels
    public:
        Tile();
        ~Tile() {}

        void create(int id, int t, Position p, SDL_Texture* tex);
        void destroy();
        void draw(Screen screen, Camera cam);

        Position getPos() { return pos; }
        int getxPos() { return pos.x; }
        int getyPos() { return pos.y; }

        int getID() { return ID; }
        int getType() { return type; }

        Sprite sprite;
        Hitbox hitbox;

    private:
        Position pos;
        int ID;
        int type;
};

Tile* getTile(Tile* tileList, Position pos);

bool createTileList(Tile* &tileList, SDL_Texture* tex);

class Map {
    public:
        Tile* tileList[MAX_TILES];
};