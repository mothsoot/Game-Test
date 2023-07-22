#pragma once

#include "screen.h"
#include "math.h"

enum COLLISION_MODE {
	FLOOR,
	RWALL,
	CEILING,
	LWALL
};

class Sensor {
    public:
        Position pos;
        bool active;

        bool collided;

        int detected_height;

        int distance;
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

class Collision {
    public:
        Collision();
        ~Collision() {}

        bool isFloor() { return floor; }
        bool islWall() { return lWall; }
        bool isrWall() { return rWall; }
        bool isCeiling() { return ceiling; }
        bool isNone();

        void screenCollision(Position &pos, SDL_Rect sprite);

    private:
        void reset();

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


