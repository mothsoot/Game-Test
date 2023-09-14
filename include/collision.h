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

bool checkCol(Hitbox boxA, Hitbox boxB);

bool tileCol(Hitbox tileBox, Hitbox playerBox, int type);
bool tileColAbove(int pBottom, int tTop);
bool tileColBelow(int pTop, int tBottom);
bool tileColRight(int pLeft, int tRight);
bool tileColLeft(int pRight, int tLeft);

class Collision {
    public:
        Collision();
        ~Collision() {}

        // tile collisions
        bool floor, lWall, rWall, ceiling;

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
        bool isNoneScr();

        void screenCol(Position &pos, Hitbox box, SDL_Rect sprite);

    private:
        void reset();

        // screen collision flags
        bool topScr, bottomScr, leftScr, rightScr;

        /*Sensor sensorA(Player player);
        Sensor sensorB(Player player);
        Sensor sensorC(Player player);
        Sensor sensorD(Player player);
        Sensor sensorE(Player player);
        Sensor sensorF(Player player);*/
};


