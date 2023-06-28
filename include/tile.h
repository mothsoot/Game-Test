#pragma once;

#include "main.h"

enum TILE_TYPE {
    TOP_SOLID, // downward sensors
    SIDE_BOTTOM_SOLID, // sideways/upward sensors
    FULL_SOLID // all sensors
};

class Tile {
    public:
        void setAngle(Tile &tile);
        float getAngle() { return angle; }

        void setFlagged(Tile &tile);

    private:
	    float angle; // 0-256 (0-FF in hex)
        bool flagged;
};

// FOR IN .CPP FILE BUT DONT WANT TO MAKE YET
void Tile::setAngle(Tile &tile)
{
/*    switch(player.cMode) {
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