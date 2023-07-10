#pragma once

#include "object.h"


enum COLLISION_MODE {
	FLOOR,
	RWALL,
	CEILING,
	LWALL
};

struct Sensor {
    Position pos;

    bool collided;

    int detected_height;

    int distance;
    float tileAngle;
    float tileID;
    
    bool flagged;
};

class Collision {
    public:
        Collision();
        ~Collision() {}

        bool isFloor() { return floor; }
        bool islWall() { return lWall; }
        bool isrWall() { return rWall; }
        bool isCeiling() { return ceiling; }
        bool isNone();

        void reset();

        void screenCollision_hor(int x);
        void screenCollision_ver(int y);

    private:
        bool floor;
		bool lWall;
		bool rWall;
		bool ceiling;

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


