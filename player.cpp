#include "player.h"

// SENSORS
sensor sensorA(Player player)
{
    sensor A;
    A.pos_x = player.x - player.wRadius;
    A.pos_y = player.y + player.hRadius;
    
    A.distance;
    A.tile_angle;
    A.tile_id;

    return A;
}

sensor sensorB(Player player) 
{
    sensor B;
    int x, y;
    x = player.x + player.wRadius;
    y = player.y + player.hRadius;

    return B;
}

sensor sensorC(Player player)
{

}

sensor sensorD(Player player)
{

}

sensor sensorE(Player player)
{

}

sensor sensorF(Player player)
{

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