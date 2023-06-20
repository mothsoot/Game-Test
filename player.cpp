#include "player.h"

void updatePlayer()
{
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
}

void playerMovement(int input, Player player)
{
	get_groundSpeed(input, player);
    get_xSpeed(player);
    get_ySpeed(player);

    player.x += player.xSpeed;
    player.y += player.ySpeed;
}

void getMode(Player &player)
{
    float angle = player.groundAngle;
    if(angle >= 0 && angle <= 45) {
        player.mode = FLOOR;
    } else if(angle >= 46 && angle <= 134) {
        player.mode = LEFT_WALL;
    } else if(angle >= 135 && angle <= 225) {
        player.mode = CEILING;
    } else if(angle >= 226 && angle <= 314) {
        player.mode = RIGHT_WALL;
    } else if(angle >= 315 && angle <= 360) {
        player.mode = FLOOR;
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
                speed += acceleration_speed;
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
    x = player.groundSpeed * cos(player.groundAngle);
    return x;
}

float get_ySpeed(Player player)
{
    float y;
    y = player.groundSpeed * -sin(player.groundAngle);
    return y;
}

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
