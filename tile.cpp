#include "tile.h"

Tile::Tile()
{
    ID = 0;
    type = TILE_FULLSOLID;

    sprite.s = {0, 0, 8, 8};
}

void Tile::create(int id, int t, Position p, SDL_Texture* tex)
{
    ID = id;
    type = t;
    pos.set(p.x, p.y);

    switch (ID) {
        case DIRT:
            sprite.s = TILE_SPRITE_DIRT;
            break;
        case GROUND:
            sprite.s = TILE_SPRITE_GROUND;
            break;
        case GRASS:
            sprite.s = TILE_SPRITE_GRASS;
            break;
    }

    sprite.tex = tex;

    hitbox.set(pos, 16, 16);
}

void Tile::destroy()
{
    SDL_DestroyTexture(sprite.tex);
}

void Tile::draw(Screen screen, Camera cam)
{
    if(checkCollision(hitbox, cam.hitbox)) {
        screen.drawFromTop((pos.x - cam.pos.x), (pos.y - cam.pos.y), sprite.s, sprite.tex);
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

// Init tiles & tile mappings here cause yeah
bool createTileList(Tile* &tileList, SDL_Texture* tex)
{
    Position posMap[MAX_TILES];
    int IDMap[MAX_TILES];
    int colMap[MAX_TILES];
    for (int p = 0; p < 30; p++) {
        // positions
        posMap[p].set(16 * p, 201);
        posMap[p + 30].set(16 * p, 217);
        posMap[p + 60].set(16 * p, 233);

        // IDs
        IDMap[p] = GRASS;
        IDMap[p + 30] = GROUND;
        IDMap[p + 60] = DIRT;


        // collision type
        colMap[p] = TILE_NONE;
        colMap[p + 30] = TILE_TOPSOLID;
        colMap[p + 60] = TILE_NONE;
    }

	// create array of tiles
	tileList = new (nothrow) Tile[MAX_TILES];
	if(tileList == nullptr) {
		// cerr << "Error!! tileList not created!\n";
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "tileList not created!\n");
		return false;
	}

	for (int p = 0; p < MAX_TILES; p++) {
		tileList[p].create(IDMap[p], colMap[p], posMap[p], tex);
	}
	return true;
}

/*
bool Tile::collision(Hitbox playerBox)
{
    if(type == TILE_NONE) {
        return false;
    }

    if(type == TILE_TOPSOLID) {
        if(!collisionAbove(playerBox)) {
            return false;
        }
        // else set player y to tileBox.top
    }

    if(type == TILE_SIDEBOTTOMSOLID) {
        if(!collisionLeft(playerBox)) {
            return false;
        }
        if(!collisionRight(playerBox)) {
            return false;
        }
        if(!collisionBelow(playerBox)) {
            return false;
        }
        // else 

    }

    if(type == TILE_FULLSOLID) {
        if(!collisionAbove(playerBox)) {
            return false;
        }
        if(!collisionLeft(playerBox)) {
            return false;
        }
        if(!collisionRight(playerBox)) {
            return false;
        }
        if(!collisionBelow(playerBox)) {
            return false;
        }
        // else
    }

    return true;
}

bool Tile::collisionAbove(Hitbox playerBox)
{
    if(playerBox.bottom < hitbox.top) { // bottom of A is higher than top of B
        return false;
    }
    return true;
}

bool Tile::collisionBelow(Hitbox playerBox)
{
    if(playerBox.top > hitbox.bottom) { // top of A is lower than bottom of B
        return false;
    }
    return true;
}

bool Tile::collisionRight(Hitbox playerBox)
{
    if(playerBox.left > hitbox.right) { // left of A is further right than right of B
        return false;
    }
    return true;
}

bool Tile::collisionLeft(Hitbox playerBox)
{
    if(playerBox.right < hitbox.left) { // right of A is further left than left of B
        return false;
    }
    return true;
}
*/