#include "player.h"

// constructor
Player::Player()
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

    setPos(20, 20);
    setRadius(19, 9, 10); // height, width, push. 14, 7, 10 when jump/roll
    xSpeed = 0;
    ySpeed = 0;
    groundSpeed = 0;
    groundAngle = 0;

    sprite = SPRITE;
}

void Player::update()
{
    // ROLLING
    if(action == ACTION_ROLL) {
        setRadius(14, 7);

        if(sign(groundSpeed) == sign(sin(groundAngle))) {
            groundSpeed -= SLOPE_FACTOR_ROLLUP * sin(groundAngle);
        } else if(sign(groundSpeed) != sign(sin(groundAngle))) {
            groundSpeed -= SLOPE_FACTOR_ROLLDOWN * sin(groundAngle);
        }
            // adjust groundSpeed based on groundAngle
        // isJump();
        getGroundSpeed();
            // adjust groundSpeed based on input + friction & accel/decel
        // wallCollision();
        // setCamera();
        // move(time);
        // groundCollision();
        // isSlipping()/isFalling();
    }

    // AIRBORNE
    else if(!grounded) {
        setRadius(19, 9);
        if(collide.lWall || collide.rWall) {
            xSpeed = 0;
        }
        // check for jump button release
        // isSuper();
        // update xSpeed based on input
        // apply air drag
        // move(time);
        if(!collide.floor) {
            getxSpeed();
            getySpeed();
            ySpeed += GRAVITY_FORCE;
                // apply gravity, update ySpeed by adding gravity
            if(ySpeed >= 70) {
                ySpeed = 70; // limit, 16 in CD
            }

            airRotation();
                // rotate groundAngle back to 0
        } else if(collide.floor) {
            ySpeed = 0;
            grounded = true;
        }
        // airCollision();
    }

    // NORMAL
    // if(action == ACTION_NORMAL) {
    else {
        setRadius(19, 9);
        // check for special actions (balancing, etc.)
        if(action == ACTION_CROUCH) {
            // isSpinDash();
        }

        if(mode != CEILING) {
            groundSpeed -= SLOPE_FACTOR * sin(groundAngle);
        }
            // adjust groundSpeed based on groundAngle
        // isJump();
        getGroundSpeed();
            // adjust groundSpeed based on input + friction & accel/decel

        if(action == ACTION_CROUCH) {
            setRadius(14, 7);
        }
        
        // wallCollision();
        if(collide.lWall || collide.rWall) {
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
        // isRoll();
        // setCamera();

        getxSpeed();
        // getySpeed();
            // calculate xSpeed & ySpeed from groundSpeed & groundAngle


        // }

        // move(time)
            // update xPos & yPos based on xSpeed & ySpeed

        // groundCollision();
        // groundAngle = groundSensor.tileAngle;
            // update groundAngle
        // pos.y += groundSensor.distance;
            // align sprite to ground

        // isSlipping()/isFalling();
            // if groundSpeed too low on walls/ceilings
    }

    // check hitboxes

    setSprite();
}

void Player::move(float time)
{
    // move left or right
    pos.x += xSpeed * time;

    // too far left or right
	if(pos.x < 0) {
        pos.x = 0;
        collide.lWall = true;
        //active = false;
    } else if(pos.x > SCREEN_WIDTH - PLAYER_SPRITE_WIDTH) {
        pos.x = SCREEN_WIDTH - PLAYER_SPRITE_WIDTH;
        collide.rWall = true;
    } else {
        collide.lWall = false;
        collide.rWall = false;
    }

    // move up or down
    pos.y += ySpeed * time;

    // too far up or down
	if(pos.y <= 0) {
        pos.y = 0;
        collide.ceiling = true;
    } else if(pos.y >= SCREEN_HEIGHT - PLAYER_SPRITE_HEIGHT) {
        pos.y = SCREEN_HEIGHT - PLAYER_SPRITE_HEIGHT;
        collide.floor = true;
    } else {
        collide.ceiling = false;
        collide.floor = false;
    }
}

void Player::draw(Screen screen)
{
    screen.drawSprite(pos.x, pos.y, sprite, flipSprite);
}

void Player::setSprite()
{
    switch(action) {
        case ACTION_NORMAL:
            sprite = SPRITE;
            switch(input.key) {
                case RIGHT:
                    flipSprite = false;
                    break;
                case LEFT:
                    flipSprite = true;
                    break;
            }
            break;
        case ACTION_CROUCH:
            sprite = SPRITE_DOWN;
            break;
        case ACTION_LOOKUP:
            sprite = SPRITE_UP;
            break;
        case ACTION_SKID:
            sprite = SPRITE_SKID;
            switch(input.key) {
                case RIGHT: // pressing right, moving left
                    flipSprite = true;
                    break;
                case LEFT: // pressing left, moving right
                    flipSprite = false;
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

    if(xSpeed >= TOP_SPEED) {
        xSpeed = TOP_SPEED;
    } else if(xSpeed <= -TOP_SPEED) {
        xSpeed = -TOP_SPEED;
    }
}

void Player::getySpeed()
{
    ySpeed = groundSpeed * -sin(groundAngle);
}

void Player::setFriction()
{
	if(groundSpeed < 0) { // moving left
        groundSpeed += FRICTION_SPEED;

        if(groundSpeed >= 0) {
            groundSpeed = 0;
        }
    } else if(groundSpeed > 0) { // moving right
        groundSpeed -= FRICTION_SPEED;

        if(groundSpeed <= 0) {
            groundSpeed = 0;
        }
    }
}

// speed for slopes
void Player::getGroundSpeed()
{
    if(input.keyDown) {
        switch(input.key) {
        case LEFT: // pressing left
            //while (groundSpeed >= -TOP_SPEED) {
                if(groundSpeed > 0) { // moving right
                    action = ACTION_SKID;

                    //groundSpeed -= DECEL_SPEED;

                    // quick turnaround
                    if(groundSpeed <= 0) {
                        groundSpeed = -0.5;
                    }
                } else if(groundSpeed >= -TOP_SPEED) { // moving left
                    action = ACTION_NORMAL;

                    groundSpeed -= ACCEL_SPEED;

                    if(groundSpeed <= -TOP_SPEED) {
                        groundSpeed = -TOP_SPEED; // limit
                    }
                }
            //}
            break;

        case RIGHT: // pressing right
            //while (groundSpeed <= TOP_SPEED) {
                if(groundSpeed < 0) { // moving left
                    action = ACTION_SKID;

                    //groundSpeed += DECEL_SPEED;
                    
                    // quick turnaround
                    if(groundSpeed >= 0) {
                        groundSpeed = 0.5;
                    }

                } else if(groundSpeed <= TOP_SPEED) { // moving right
                    action = ACTION_NORMAL;

                    groundSpeed += ACCEL_SPEED;

                    if(groundSpeed >= TOP_SPEED) {
                        groundSpeed = TOP_SPEED; // limit
                    }
                }
            //}
            break;

        case UP:
            action = ACTION_LOOKUP;
            break;

        case DOWN:
            action = ACTION_CROUCH;
            break;

        case NONE:
            action = ACTION_NORMAL;
            setFriction();
            break;
    }

    } else if(!input.keyDown || input.key == NONE) {
        action = ACTION_NORMAL;
            setFriction();
    }
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
void Player::airAcceleration()
{
    if(input.keyDown) {
        switch (input.key) {
            case RIGHT:
                xSpeed -= AIR_ACCEL_SPEED;
                break;
            case LEFT:
                xSpeed += AIR_ACCEL_SPEED;
                break;
        }

        if(xSpeed >= TOP_SPEED) {
            xSpeed = TOP_SPEED;
        }
    }
}

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
