#pragma once

#include "main.h"
#include "tile.h"

const int MAX_FILENAME_LENGTH = 15;

const int MAP_HEIGHT = 40;
const int MAP_WIDTH = 20;

const int MAX_TILES = 8;

const int TILE_SIZE = 16;

const int MAP_RENDER_WIDTH = 20;
const int MAP_RENDER_HEIGHT = 12;

struct Map {
    int map[MAP_HEIGHT][MAP_WIDTH];
};

void initMap();
void loadTiles();
void loadMap(const char *filename);

void initMap()
{
    int* map[MAP_HEIGHT][MAP_WIDTH];

    loadTiles();

    loadMap("filename");
}

void loadTiles(Tile tileList[])
{
    char filename[MAX_FILENAME_LENGTH];
    for (int p = 1; p < MAX_TILES; p++) {
        sprintf(filename, "tiles/tile%d.png", p);
        
        tileList[p].sprite = loadTexture(filename);
    }
}
