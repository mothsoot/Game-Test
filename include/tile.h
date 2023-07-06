#pragma once;

#include "screen.h"

enum TILE_TYPE {
    TILE_NONE,
    TILE_TOPSOLID, // downward sensors
    TILE_SIDEBOTTOMSOLID, // sideways/upward sensors
    TILE_FULLSOLID // all sensors
};

class Tile {
    // 8x8 pixels
    public:
        Tile();
        ~Tile() {}

        Position pos;

        int tileID;
        int typeID;
        float tileAngle; // 0-256 (0-FF in hex)
        
        void setID();
        void setAngle();

        // collision data
        int hArray[16]; // left to right
        int wArray[16]; // top to bottom

        bool flagged;
        void setFlagged();

        SDL_Rect sprite;
        SDL_RendererFlip flip;

    private:
    
};

class Block {
    // 16x16 pixels
    public:
        Block();
        ~Block() {}

        int blockID;
};

class Chunk {
    // 256x256 pixels (S1/SCD), 128x128 pixels (S2/S3/S&K)
    public:
        Chunk();
        ~Chunk() {}

        int chunkID;
};

// FOR IN .CPP FILE BUT DONT WANT TO MAKE YET
Tile::Tile()
{
    tileID = 0;
    typeID = TILE_NONE;
}

void Tile::setID()
{
    
}

void Tile::setAngle()
{
    /*switch(player.mode) {
        case CMODE_FLOOR:
            return floorAngle;
            break;
        
        case CMODE_LWALL:
            return lwallAngle;
            break;
        
        case CMODE_CEILING:
            return ceilingAngle;
            break;

        case CMODE_RWALL:
            return rwallAngle;
            break;
    }*/
}

void Tile::setFlagged()
{
    if(tileAngle == 255) {
        flagged == true;
    }
}

Block::Block()
{
    blockID = 0;
}

Chunk::Chunk()
{
    chunkID = 0;
}