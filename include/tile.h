#pragma once;

#include "math.h"
#include "screen.h"
#include "object.h"

const int MAX_TILES = 90;

const int TILE_SIZE = 16;

enum TILE_TYPE {
    GRASS,
    GROUND,
    DIRT,
    NONE
};

enum TILE_COL_TYPE {
    TILE_NONE,
    TILE_TOPSOLID, // downward sensors
    TILE_SIDEBOTTOMSOLID, // sideways/upward sensors
    TILE_FULLSOLID // all sensors
};

class Tile {
    public:
        Tile() {} //int x = 0, int y = 0, int type = 0): pos(x, y), type(type) {
/*            hitbox.set(pos, TILE_SIZE, TILE_SIZE);
            switch (type) {
                case DIRT:
                    sprite.s = TILE_SPRITES[0];
                    break;
                case GROUND:
                    sprite.s = TILE_SPRITES[1];
                    break;
                case GRASS:
                    sprite.s = TILE_SPRITES[2];
                    break;
                case NONE:
                    sprite.s = TILE_SPRITES[4];
                    break;
            };
            col = TILE_NONE;
        }*/
        ~Tile() {}

        void create(int t, int c, Position p);
        void destroy();
        void draw(Screen screen, Camera cam);

        Position getPos() { return pos; }
        int getxPos() { return pos.x; }
        int getyPos() { return pos.y; }

        int getType() { return type; }
        int getCol() { return col; }

        Sprite sprite;
        Hitbox hitbox;

    private:
        Position pos;
        int type;
        int col;
};

Tile* getTile(Tile* tileList, Position pos);

Tile* createTileList(Position posMap[], int typeMap[], int colMap[]);

Position* loadPosMap(string file);
int* loadTypeMap(string file);
int* loadColMap(string file);

class Map {
    public:
        Tile* tileList;

        Position* loadPosMap(string file);
        int* loadTypeDMap(string file);
        int* loadColMap(string file);

        bool loadTiles();

        void loadMap();

    private:
        SDL_Texture* tex;

        Position* posMap;
        int* typeMap;
        int* colMap;

        bool loadTile();
};