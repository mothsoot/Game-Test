#pragma once

#include "player.h"

struct Position;
class Player;

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
};

class Collision {
    public:
        Collision();
        ~Collision();

        bool wallCollision(Player player);
        bool groundCollision(Player player);
        bool ceilingCollision(Player player);

        Sensor sensorA(Player player);
        Sensor sensorB(Player player);
        Sensor sensorC(Player player);
        Sensor sensorD(Player player);
        Sensor sensorE(Player player);
        Sensor sensorF(Player player);

    private:

};
