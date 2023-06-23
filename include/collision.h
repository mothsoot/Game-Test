#pragma once

#include "player.h"

class Position; // forward declaration
class Player;

class Sensor {
    public:
        Position pos;

        int distance;
        float tile_angle;
        float tile_id;
};

class Collision {
    public:
        Sensor sensorA(Player player);
        Sensor sensorB(Player player);
        Sensor sensorC(Player player);
        Sensor sensorD(Player player);
        Sensor sensorE(Player player);
        Sensor sensorF(Player player);
};