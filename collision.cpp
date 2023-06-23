#include "collision.h"

// right ground
Sensor Collision::sensorA(Player player)
{
    Sensor A;
    A.pos.x = player.pos.x - player.wRadius;
    A.pos.y = player.pos.y - player.hRadius;

    return A;
}

// left ground
Sensor Collision::sensorB(Player player) 
{
    Sensor B;
    B.pos.x = player.pos.x + player.wRadius;
    B.pos.y = player.pos.y - player.hRadius;

    return B;
}

// right ceiling
Sensor Collision::sensorC(Player player)
{
    Sensor C;
    C.pos.x = player.pos.x - player.wRadius;
    C.pos.y = player.pos.y + player.hRadius;

    return C;
}

// left ceiling
Sensor Collision::sensorD(Player player)
{
    Sensor D;
    D.pos.x = player.pos.x + player.wRadius;
    D.pos.y = player.pos.y + player.hRadius;

    return D;
}

// right wall
Sensor Collision::sensorE(Player player)
{
    Sensor E;
    if(player.groundSpeed < 0) {
        E.pos.x = player.pos.x - player.pushRadius;
        E.pos.y = player.pos.y;
        return E;
    }
}

// left wall
Sensor Collision::sensorF(Player player)
{
    Sensor F;
    if(player.groundSpeed < 0) {
        F.pos.x = player.pos.x + player.pushRadius;
        F.pos.y = player.pos.y;
        return F;
    }
}