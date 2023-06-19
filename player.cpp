#include "player.h"

//void updatePlayer()
//{
    // NORMAL
    // check for special actions (balancing, etc.)
    // isSpinDash();
    // adjust ground_speed based on groundAngle
    // isJump();
    // adjust groundSpeed based on input + friction & accel/deccel
    // wallCollision();
        // add xSpeed & ySpeed to sensor position here
    // isRoll();
    // setCamera();
    // movePlayer();
        // calculate xSpeed & ySpeed from groundSpeed & groundAngle
        // update xPos & yPos based on xSpeed & ySpeed
    // floorCollision();
        // update groundAngle
        // align sprite to ground
    // isSlipping()/isFalling();
        // if groundSpeed too low on walls/ceilings

    // ROLLING
    // adjust ground_speed based on groundAngle
    // isJump();
    // adjust groundSpeed based on input + friction & accel/deccel
    // wallCollision();
    // setCamera();
    // movePlayer();
    // floorCollision();
    // isSlipping()/isFalling();

    // AIRBORNE
    // check for jump button release
    // isSuper();
    // update xSpeed based on input
    // apply air drag
    // movePlayer();
    // apply gravity
        // update ySpeed by adding gravity
    // isUnderWater();
    // groundAngle = 0;
    // airCollision();

    // check hitboxes
//}

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
    if(player.groundSpeed < 0) {
        E.x = player.x - player.pushRadius;
        E.y = player.y;
        return E;
    }
}

// Left wall
sensor sensorF(Player player)
{
    sensor F;
    if(player.groundSpeed < 0) {
        F.x = player.x + player.pushRadius;
        F.y = player.y;
        return F;
    }
}

// SPEED
float get_groundSpeed(int input, Player player)
{
    float speed = player.groundSpeed;

    if(input == LEFT) { // pressing left
        while (speed > -top_speed) {
            if(speed > 0) { // moving right
                speed -= deceleration_speed;
                if(speed <= 0) {
                    speed = -0.5;
                }
            } else if(speed > -top_speed) { // moving left
                speed -= acceleration_speed;
                if(speed <= -top_speed) {
                    speed = -top_speed; // limit
                }
            }
        }
    }

    if(input == RIGHT) { // pressing right
        while (speed < top_speed) {
            if(speed < 0) { // moving left
                speed += deceleration_speed;
                if(speed >= 0) {
                    speed = 0.5;
                }
            } else if(speed > top_speed) { // moving right
                speed = (speed + acceleration_speed);
                if(speed >= top_speed) {
                    speed = top_speed; // limit
                }
            }
        }
    }

    // friction
    if(input == NONE) {
        if(speed < 0) { 
            speed += friction_speed;
            if(speed >= 0) {
                speed = 0;
            }
        } else if(speed > 0) {
            speed -= friction_speed;
            if(speed <= 0) {
                speed = 0;
            }
        }
    }

    return speed;
}

float get_xSpeed(Player player)
{
    float x;

    return x; 
}

float get_ySpeed(Player player)
{
    float y;

    return y;
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

// JUMPING
void jumpVelocity(Player player)
{
    player.xSpeed -= jump_force * sin(player.groundAngle);
    player.ySpeed -= jump_force * cos(player.groundAngle);
}

void variableJumpHeight(int input, Player player)
{
    // checked before updating player position & gravity is calculated
    if(input == NONE) {
        if(player.ySpeed < -4) {
            player.ySpeed = -4;
        }
    }
}

// AIRBORNE
void airAcceleration(int input, Player player)
{
    if(input == RIGHT) {
        player.xSpeed -= air_acceleration_speed;
    }
    if(input == LEFT) {
        player.xSpeed += air_acceleration_speed;
    }

    if(player.xSpeed >= top_speed) {
        player.xSpeed = top_speed;
    }
}

void gravity(Player player)
{
    // for every step player is airborne
    player.ySpeed += gravity_force;
}

void airDrag(Player player)
{
    // calculated before gravity
    if (player.ySpeed < 0 && player.ySpeed > -4) {
        player.xSpeed = player.xSpeed - ((player.xSpeed / 0.125) / 256);
    }
}

void airRotation(Player player)
{
    // for every frame
    // depending on quadrant, smoothly return to 0
    player.groundAngle += 2.8125;
}

// MISC
/*
void underwater()
{
    acceleration_speed = 0.0234375;
    deceleration_speed = 0.25;
    friction_speed = 0.0234375;
    top_speed = 3;

    air_acceleration_speed = 0.046875;

    roll_friction_speed = 0.01171875;
    roll_deceleration_speed = 0.125; // unchanged

    gravity_force = 0.0625;
    jump_force = 3.5;
    jump_release = -2;

    // upon entering water
    player.xSpeed *= 0.5;
    player.ySpeed *= 0.25;

    // upon exiting water
    player.ySpeed *= 2;


}
*/