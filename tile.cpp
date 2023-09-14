#include "tile.h"

void Tile::create(int t, int c, Position p)
{
    type = t;
    col = c;
    pos.set(p.x, p.y);

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

    //sprite.tex = tex;

    hitbox.set(pos, 16, 16);
}

void Tile::destroy()
{
    SDL_DestroyTexture(sprite.tex);
}

void Tile::draw(Screen screen, Camera cam)
{
    if(checkCol(hitbox, cam.hitbox)) {
        screen.drawFromTop((pos.x - cam.pos.x), (pos.y - cam.pos.y), sprite.s, screen.getTileTex());
    }
}

Tile* getTile(Tile* tileList, Position pos)
{
    for (int p = 0; p < MAX_TILES; p++) {
        if(tileList[p].getxPos() == pos.x) {
            return &tileList[p];
        }
    }

    return nullptr;
}

Tile* createTileList(Position posMap[], int typeMap[], int colMap[])
{
    // create array of tiles
    Tile* tileList = new (nothrow) Tile[MAX_TILES];
    if(tileList == nullptr) {
        // cerr << "Error!! tileList not created!\n";
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "tileList not created!\n");
    }

    for (int p = 0; p < MAX_TILES; p++) {
        tileList[p].create(typeMap[p], colMap[p], posMap[p]);
    }
    return tileList;
}

Position* loadPosMap(string file)
{
    Position* posMap = new (nothrow) Position[MAX_TILES];
    /*ifstream inf;

    inf.open(file);
    if (!inf.is_open()) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not open file!\n");
    }

    for (int p = 0; p < MAX_TILES; p++) {
        int x, y;
        inf >> x;
        inf >> y;

        posMap[p].set(x, y);
    }

    inf.close();*/

    for (int p = 0; p < 30; p++) {
        // positions
        posMap[p].set(16 * p, 201);
        posMap[p + 30].set(16 * p, 217);
        posMap[p + 60].set(16 * p, 233);
    }

    return posMap;
}

int* loadTypeMap(string file)
{
    int* typeMap = new (nothrow) int[MAX_TILES];
    /*ifstream inf;

    inf.open(file);
    if (!inf.is_open()) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not open file!\n");
    }

    for (int p = 0; p < MAX_TILES; p++) {
        int x;
        inf >> x;

        typeMap[p] = x;
    }

    inf.close();*/

    for (int p = 0; p < 30; p++) {
        // IDs
        typeMap[p] = GRASS;
        typeMap[p + 30] = GROUND;
        typeMap[p + 60] = DIRT;
    }

    return typeMap;
}

int* loadColMap(string file)
{
    int* colMap = new (nothrow) int[MAX_TILES];
    /*ifstream inf;

    inf.open(file);
    if (!inf.is_open()) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not open file!\n");
    }

    for (int p = 0; p < MAX_TILES; p++) {
        int x;
        inf >> x;

        colMap[p] = x;
    }

    inf.close();*/

    for (int p = 0; p < 30; p++) {
        // collision type
        colMap[p] = TILE_NONE;
        colMap[p + 30] = TILE_FULLSOLID;
        colMap[p + 60] = TILE_NONE;
    }

    return colMap;
}

bool Map::loadTiles()
{
    tileList = new (nothrow) Tile[MAX_TILES];
    if(tileList == nullptr) {
        return false;
    }

     // tile pos
    int x = 0;
    int y = 0;

    ifstream map;
    map.open("tiles.txt");
    if (!map.is_open()) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not open file!\n");
        return false;
    }

    //if(map == nullptr) {
        // uh oh
    //    return false;
    //}

    for( int t = 0; t < MAX_TILES; t++ ) {
        //Determines what kind of tile will be made
        int tileType;

        //Read tile from map file
        map >> tileType;

        //If the was a problem in reading the map
        if(map.fail() == true) {
            //Stop loading map
            map.close();
            return false;
        }

        //If the number is a valid tile number
        if(0 <= tileType < 4) {
            //tileList[t] = Tile(x, y, tileType);
        }

        //If we don't recognize the tile type
        else {
            //Stop loading map
            map.close();
            return false;
        }

        //Move to next tile spot
        x += TILE_SIZE;
        
        //If we've gone too far
        if(x >= LEVEL_WIDTH){
            //Move back
            x = 0;
            
            //Move to the next row
            y += TILE_SIZE;
        }
    }
    
    //Close the file
    map.close();
    
    //If the map was loaded fine
    return true;

}

void Map::loadMap()
{

}