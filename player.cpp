#include "player.h"

// SENSORS
// Right ground
sensor sensorA(Player player)
{
    sensor A;
    A.x = player.x - player.wRadius;
    A.y = player.y - player.hRadius;

    return A;
}

// Left ground
sensor sensorB(Player player) 
{
    sensor B;
    B.x = player.x + player.wRadius;
    B.y = player.y - player.hRadius;

    return B;
}

// Right ceiling
sensor sensorC(Player player)
{
    sensor C;
    C.x = player.x - player.wRadius;
    C.y = player.y + player.hRadius;

    return C;
}

// Left ceiling
sensor sensorD(Player player)
{
    sensor D;
    D.x = player.x + player.wRadius;
    D.y = player.y + player.hRadius;

    return D;
}

// Right wall
sensor sensorE(Player player)
{
    sensor E;
    if(player.ground_speed < 0) {
        E.x = player.x - player.pushRadius;
        E.y = player.y;
        return E;
    } else {
        return;
    }
}

// Left wall
sensor sensorF(Player player)
{
    sensor F;
    if(player.ground_speed < 0) {
        F.x = player.x + player.pushRadius;
        F.y = player.y;
        return F;
    } else {
        return;
    }
}

// INPUT STUFF
void speed(int input, Player player)
{
    int ground_speed = player.ground_speed;

    if(input == LEFT) { // pressing left
        while (ground_speed > -top_speed) {
            if(ground_speed > 0) { // moving right
                ground_speed = (ground_speed - deceleration_speed);
                if(ground_speed <= 0) {
                    ground_speed = -0.5;
                }
            } else if(ground_speed > -top_speed) { // moving left
                ground_speed = (ground_speed - acceleration_speed);
                if(ground_speed <= -top_speed) {
                    ground_speed = -top_speed; // limit
                }
            }
        }
    }

    if(input == RIGHT) { // pressing right
        while (ground_speed < top_speed) {
            if(ground_speed < 0) { // moving left
                ground_speed = (ground_speed + deceleration_speed);
                if(ground_speed >= 0) {
                    ground_speed = 0.5;
                }
            } else if(ground_speed > top_speed) { // moving right
                ground_speed = (ground_speed + acceleration_speed);
                if(ground_speed >= top_speed) {
                    ground_speed = top_speed; // limit
                }
            }
        }
    }

    // friction
    if(input == NONE) {
        if(ground_speed < 0) { 
            ground_speed = ground_speed + friction_speed;
            if(ground_speed >= 0) {
                ground_speed = 0;
            }
        } else if(ground_speed > 0) {
            ground_speed = ground_speed - friction_speed;
            if(ground_speed <= 0) {
                ground_speed = 0;
            }
        }
    }
}

/*
bool collision_right(Player player) {
    for (int p = 4; p < player.hitbox_y - 4; p++) {
        float xx = player.x + player.hitbox_x / 2 + 1;
        float yy = player.y - player.hitbox_y / 2 + p + player.ySpeed;
        if((yy > player.y - player.hitbox_y / 2) && (yy < player.y + player.hitbox_y / 2) &&
        (xx > player.x - player.hitbox_x / 2) && (xx < player.x + player.hitbox_x / 2)) {
            return true;
        }
        return false;
    }
}
*/