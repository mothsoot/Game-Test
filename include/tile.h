#pragma once;

#include "screen.h"

// TILE 16x16
// CHUNK 256x256 pixel chunks
// BLOCK 16x16 pixel blocks

enum TILE_TYPE {
    TOP_SOLID, // downward sensors
    SIDE_BOTTOM_SOLID, // sideways/upward sensors
    FULL_SOLID // all sensors
};

class Tile {
    public:
        SDL_Rect sprite;
        SDL_RendererFlip flip;

        // collision data
        int type;

        int hArray[16]; // left to right
        int wArray[16]; // top to bottom

        float angle; // 0-256 (0-FF in hex)
        void setAngle(Tile &tile);
        float getAngle() { return angle; }

        bool flagged;
        void setFlagged(Tile &tile);

    private:
    
};

// FOR IN .CPP FILE BUT DONT WANT TO MAKE YET
void Tile::setAngle(Tile &tile)
{
/*    switch(player.mode) {
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

void Tile::setFlagged(Tile &tile)
{
    if(angle == 255) {
        flagged == true;
    }
}