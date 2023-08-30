#pragma once

#include "screen.h"
#include "math.h"
// #include "tile.h"

const int GROUND_HEIGHT = 200;

class Sensor {
    public:
        Position pos;
        bool active;

        bool collided;

        int detected_height;

        int distance;

        Position tilePos;
        float tileAngle;
        float tileID;
        
        bool flagged;

        void sensorA(bool grounded);
        void sensorB(bool grounded);
        void sensorC();
        void sensorD();
        void sensorE(float speed);
        void sensorF(float speed);
};

bool checkCollision(Hitbox boxA, Hitbox boxB);

bool tileCollision(Hitbox tileBox, Hitbox playerBox, int type);
bool tileCollisionAbove(int pBottom, int tTop);
bool tileCollisionBelow(int pTop, int tBottom);
bool tileCollisionRight(int pLeft, int tRight);
bool tileCollisionLeft(int pRight, int tLeft);

class Collision {
    public:
        Collision();
        ~Collision() {}

        // tile collisions
        bool floor;
		bool lWall;
		bool rWall;
		bool ceiling;

        bool isFloor() { return floor; }
        bool islWall() { return lWall; }
        bool isrWall() { return rWall; }
        bool isCeiling() { return ceiling; }
        bool isNone();

        // screen collisions
        bool isTopScr() { return topScr; }
        bool isBottomScr() { return bottomScr; }
        bool isLeftScr() { return leftScr; }
        bool isRightScr() { return rightScr; }
        bool isNoScr();

        void screenCollision(Position &pos, Hitbox box, SDL_Rect sprite);

    private:
        void reset();

        // screen collision flags
        bool topScr;
        bool bottomScr;
        bool leftScr;
        bool rightScr;

        /*bool wallCollision(Player player);
        bool groundCollision(Player player);
        bool ceilingCollision(Player player);

        Sensor sensorA(Player player);
        Sensor sensorB(Player player);
        Sensor sensorC(Player player);
        Sensor sensorD(Player player);
        Sensor sensorE(Player player);
        Sensor sensorF(Player player);*/
};


