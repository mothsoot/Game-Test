#include "player.h"

// constructor
Player::Player(int x, int y)
{
    type = TYPE_PLAYER;
    action = ACTION_NORMAL;
    mode = FLOOR;

    active = true;

    collide.floor = false;
    collide.lWall = false;
    collide.rWall = false;
    collide.ceiling = false;
    grounded = true;

    setPos(x, y);
    setRadius(19, 9, 10); // height, width, push. 14, 7, 10 when jump/roll
    xSpeed = 0;
    ySpeed = 0;
    groundSpeed = 0;
    groundAngle = 0;

    sprite.s = SPRITE;
    sprite.flip = false;
}

void Player::update()
{
    if(!active) {
        // player dead!!
    } else {

    if(collide.floor) {
        grounded = true;
    }

    // AIRBORNE
    if(!grounded) {
        setRadius(19, 9);

        groundSpeed = 0; // not on ground!

        if(collide.lWall || collide.rWall) {
            xSpeed = 0;
        }

        if(!input.keyDown) {
            // jump button released
        }

        // check for jump button release

        xSpeed = getSpeed(xSpeed);
            // update xSpeed based on input

        // apply air drag

        // move();
        airDrag();
        ySpeed += GRAVITY_FORCE;
            // apply gravity, update ySpeed by adding gravity

        if(ySpeed >= 6) {
            ySpeed = 6; // limit, 16 in CD
        }

        if(ySpeed <= -6) {
            ySpeed = -6;
        }

        airRotation();
            // rotate groundAngle back to 0

        if(collide.floor) {
            ySpeed = 0;
        }

        // airCollision();
        
    }

    // NORMAL
    else if(grounded) {
        setRadius(19, 9);

        // check for special actions (balancing, etc.)

        if(mode != CEILING) {
            groundSpeed -= SLOPE_FACTOR * sin(groundAngle);
        }
            // adjust groundSpeed based on groundAngle

        // ifJump();
        if(input.key == SPACE) {
            action = ACTION_JUMP;
            grounded = false;
            jumpVelocity();
        } else {

        if(action == ACTION_NORMAL || action == ACTION_SKID || action == ACTION_CROUCH || action == ACTION_LOOKUP) {

        groundSpeed = getSpeed(groundSpeed);
            // adjust groundSpeed based on input + friction & accel/decel

        if(action == ACTION_CROUCH) {
            setRadius(14, 7);
        }
        
        // wallCollision();
        if((collide.lWall && (groundSpeed < 0)) || (collide.rWall && (groundSpeed > 0))) {
            groundSpeed = 0;
        }

        // if(collide) {

        // } else {
            /* if(groundSpeed < 0) { // moving left
                sensorF.pos.x += xSpeed;
            } else if(groundSpeed > 0) { // moving right
                sensorE.pos.x += xSpeed;
            } */
                // add xSpeed & ySpeed to sensor position

        // setCamera();

        getxSpeed();
        // getySpeed();
            // calculate xSpeed & ySpeed from groundSpeed & groundAngle
            
        // }

        // move()
            // update xPos & yPos based on xSpeed & ySpeed

        // groundCollision();
        // groundAngle = groundSensor.tileAngle;
            // update groundAngle
        // pos.y += groundSensor.distance;
            // align sprite to ground
        }
    }
    }

    // check hitboxes

    setSprite();

    move();
    }
}

void Player::move()
{
    // move left or right
    pos.x += xSpeed;

    // too far left or right
    collide.screenCollision(pos.x);

    // move up or down
    pos.y += ySpeed;

    // too far up or down
	if(pos.y <= 0) {
        pos.y = 0;
        collide.ceiling = true;
    } else {
        collide.ceiling = false;
    }
    
    if(pos.y >= SCREEN_HEIGHT - PLAYER_SPRITE_HEIGHT) {
        pos.y = SCREEN_HEIGHT - PLAYER_SPRITE_HEIGHT;

        ySpeed = 0; // temp here so it works
        collide.floor = true;
    } else {
        collide.floor = false;
    }
}

void Player::setSprite()
{
    switch(action) {
        case ACTION_NORMAL:
            sprite.s = SPRITE;
            switch(input.key) {
                case RIGHT:
                    sprite.flip = false;
                    break;
                case LEFT:
                    sprite.flip = true;
                    break;
            }
            break;
        case ACTION_CROUCH:
            sprite.s = SPRITE_DOWN;
            break;
        case ACTION_LOOKUP:
            sprite.s = SPRITE_UP;
            break;
        case ACTION_SKID:
            sprite.s = SPRITE_SKID;
            switch(input.key) {
                case RIGHT: // pressing right, moving left
                    sprite.flip = true;
                    break;
                case LEFT: // pressing left, moving right
                    sprite.flip = false;
                    break;
            }
            break;
    }
}

// mode for collisions
void Player::setMode()
{
    if((0 <= groundAngle <= 45) || (315 <= groundAngle <= 360)) {
        mode = FLOOR;
    } else if(46 <= groundAngle <= 134) {
        mode = LWALL;
    } else if(135 <= groundAngle <= 225) {
        mode = CEILING;
    } else if(226 <= groundAngle <= 314) {
        mode = RWALL;
    }
}

void Player::getxSpeed()
{
    xSpeed = groundSpeed * cos(groundAngle);
}

void Player::getySpeed()
{
    ySpeed = groundSpeed * -sin(groundAngle);
}

float Player::setFriction(float speed)
{
	if(speed < 0) { // moving left
        speed += FRICTION_SPEED;

        if(speed >= 0) {
            speed = 0;
        }
    } else if(speed > 0) { // moving right
        speed -= FRICTION_SPEED;

        if(speed <= 0) {
            speed = 0;
        }
    }
    
    return speed;
}

float Player::getSpeed(float speed)
{
    // float speed is temp to return to either groundSpeed or xSpeed

    if(input.keyDown) {
        switch(input.key) {
        case LEFT: // pressing left
            //while (speed >= -TOP_SPEED) {
                if(speed > 0) { // moving right
                    if(grounded) {
                        action = ACTION_SKID;
                        speed -= DECEL_SPEED;
                    } else {
                        speed -= AIR_ACCEL_SPEED;
                    }

                    // quick turnaround
                    if(speed <= 0) {
                        speed = -0.5;
                    }
                } else if(speed >= -TOP_SPEED) { // moving left
                    action = ACTION_NORMAL;

                    if(grounded) {
                        speed -= ACCEL_SPEED;
                    } else {
                        speed -= AIR_ACCEL_SPEED;
                    }

                    if(speed <= -TOP_SPEED) {
                        speed = -TOP_SPEED; // limit
                    }
                }
            //}
            break;

        case RIGHT: // pressing right
            //while (speed <= TOP_SPEED) {
                if(speed < 0) { // moving left
                    if(grounded) {
                        action = ACTION_SKID;

                        speed += DECEL_SPEED;
                    } else {
                        speed += AIR_ACCEL_SPEED;
                    }
                    
                    // quick turnaround
                    if(speed >= 0) {
                        speed = 0.5;
                    }

                } else if(speed <= TOP_SPEED) { // moving right
                    action = ACTION_NORMAL;
                    if(grounded) {
                        speed += ACCEL_SPEED;
                    } else {
                        speed += AIR_ACCEL_SPEED;
                    }

                    if(speed >= TOP_SPEED) {
                        speed = TOP_SPEED; // limit
                    }
                }
            //}
            break; //

        case UP:
            if(grounded) {
                action = ACTION_LOOKUP;
            }
            break;

        case DOWN:
            if(grounded) {
                action = ACTION_CROUCH;
            }
            break;
    }

    }

    else if((!input.keyDown) || (input.keyDown) && (input.key == NONE)) {
        action = ACTION_NORMAL;
        if(grounded) {
            speed = setFriction(speed);
        }
    }

    return speed;
}

// STUFF TO IMPLEMENT LATER !!

// JUMPING
void Player::jumpVelocity()
{
    // if player hits jump button, do this
    xSpeed -= JUMP_FORCE * sin(groundAngle);
    ySpeed -= JUMP_FORCE * cos(groundAngle);
}

void Player::variableJumpHeight()
{
    // checked before updating player position & gravity is calculated
    switch (input.key) {
        case NONE:
            if(ySpeed < -4) {
                ySpeed = -4;
            }
            break;
    }
}

// AIRBORNE
void Player::gravity()
{
    // for every step player is airborne
    ySpeed += GRAVITY_FORCE;
}

void Player::airDrag()
{
    // calculated before gravity
    if(ySpeed < 0 && ySpeed > -4) {
        xSpeed -= ((xSpeed / 0.125) / 256);
    }
}

void Player::airRotation()
{
    // for every frame
    // depending on quadrant, smoothly return to 0
    if(groundAngle != 0) {
        groundAngle += 2.8125; // 2 in hex
    }
}

// MISC
/*
void underwater()
{
    ACCEL_SPEED = 0.0234375;
    DECEL_SPEED = 0.25;
    FRICTION_SPEED = 0.0234375;
    TOP_SPEED = 3;

    AIR_ACCEL_SPEED = 0.046875;

    ROLL_FRICTION_SPEED = 0.01171875;
    ROLL_DECEL_SPEED = 0.125; // unchanged

    GRAVITY_FORCE = 0.0625;
    JUMP_FORCE = 3.5;
    JUMP_RELEASE = -2;

    // upon entering water
    player.xSpeed *= 0.5;
    player.ySpeed *= 0.25;

    // upon exiting water
    player.ySpeed *= 2;


}
*/
