#pragma once

#include "screen.h"
#include "object.h"

const int MAP_HEIGHT = 5;
const int MAP_WIDTH = 10;

const int MAX_TILES = 8;

const int TILE_SIZE = 16;

const int MAP_RENDER_WIDTH = 20;
const int MAP_RENDER_HEIGHT = 12;

enum TILE_TYPE {
    TILE_NONE,
    TILE_TOPSOLID, // downward sensors
    TILE_SIDEBOTTOMSOLID, // sideways/upward sensors
    TILE_FULLSOLID // all sensors
};

int map[MAP_HEIGHT][MAP_WIDTH] = {

};

class Tile {
    // 8x8 pixels
    public:
        Tile(int type = 0);
        ~Tile() {}

        Position pos;

        int ID;
        int type;

        void setID();

        bool flagged;

        Sprite sprite;

        Tile load();
        void draw(Screen screen, Camera cam);

    private:

};

class Map {
    public:
        int col, row;

        Tile tileMap[MAP_HEIGHT][MAP_WIDTH];

        SDL_Texture* tileSprites;

        Tile getTile();

        void drawMap();
        void loadMap();
};

void initMap();


void initMap()
{

}

void Map::loadMap()
{
    for (int y = 0; y < MAP_RENDER_HEIGHT; y++) {
		for (int x = 0; x < MAP_RENDER_WIDTH; x++) {
            tileMap[x][y] = getTile(map[x][y]);
        }
    }
}

void Map::drawMap()
{
	for (int y = 0; y < MAP_RENDER_HEIGHT; y++) {
		for (int x = 0; x < MAP_RENDER_WIDTH; x++) {

			if (t != nullptr) {
				drawTile(t, x * TILE_SIZE, y * TILE_SIZE, 0);
			}
		}
	}
}

Tile::Tile(int id): ID(id)
{
    switch (ID) {
        case 0:
            sprite.s;
            break;
        
    }
}

void Tile::load(Tile tileList[])
{
    for (int p = 1; p < MAX_TILES; p++) {

    }
}

void Tile::draw(Screen screen, Camera cam)
{
    Position source, dest;

    source.x = sprite.s.x;
    source.y = sprite.s.y;
    dest; // where to draw it



    screen.drawTile();
}

void Tile::setID()
{
    
}