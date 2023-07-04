#include "player.h"

// constructor
Player::Player()
{
    type = TYPE_PLAYER;
    action = ACTION_NORMAL;
    mode = FLOOR;

    setPos(5,5);
    setRadius(19, 9, 10); // height, width, push. 14, 7, 10 when jump/roll
    xSpeed = 0;
    ySpeed = 0;
    groundSpeed = 0;
    groundAngle = 0;

    sprite = SPRITE;
}

void Player::update(SDL_Event e)
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
        setGroundSpeed(e);
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
        // check for jump button release
        // isSuper();
        // update xSpeed based on input
        // apply air drag
        // move(time);
        // apply gravity
            // update ySpeed by adding gravity
        // isUnderWater();
        airRotation();
            // rotate groundAngle back to 0
        // airCollision();
    }

    // NORMAL
    // if(action == ACTION_NORMAL) {
    else {
        setRadius(19, 9);
        // check for special actions (balancing, etc.)
        /*if(action == ACTION_CROUCH) {
            setRadius(14, 7);
            // isSpinDash();
        }*/

        if(mode != CEILING) {
            groundSpeed -= SLOPE_FACTOR * sin(groundAngle);
        }
            // adjust groundSpeed based on groundAngle
        // isJump();
        setGroundSpeed(e);
            // adjust groundSpeed based on input + friction & accel/decel
        
        // wallCollision();
            /* if(groundSpeed < 0) { // moving left
                sensorF.pos.x += xSpeed;
            } else if(groundSpeed > 0) { // moving right
                sensorE.pos.x += xSpeed;
            } */
                // add xSpeed & ySpeed to sensor position
        // isRoll();
        // setCamera();
    
        // HANDLE EVENT
        xSpeed = getxSpeed();
		setySpeed(e);
        // ySpeed = getySpeed();
            // calculate xSpeed & ySpeed from groundSpeed & groundAngle

        if(action == ACTION_CROUCH) {
            setRadius(14, 7);
        }

        //move(time)
            // update xPos & yPos based on xSpeed & ySpeed

        // groundCollision();
        // groundAngle = sensor.tileAngle;
            // update groundAngle
        // pos.y += groundSensor.distance;
            // align sprite to ground

        // isSlipping()/isFalling();
            // if groundSpeed too low on walls/ceilings
    }

    // check hitboxes
}

void Player::move(float time)
{
    collide = false;
    // move left or right
    pos.x += xSpeed * time;

    // too far left or right
	if(pos.x < 0) {
        pos.x = 0;
        collide = true;
    } else if(pos.x > SCREEN_WIDTH - 29) {
        pos.x = SCREEN_WIDTH - 29;
        collide = true;
    }
    
    // move up or down
    pos.y += ySpeed * time;

    // too far up or down
	if(pos.y < 0) {
        collide = true;
        pos.y = 0;
    } else if(pos.y > SCREEN_HEIGHT - 38) {
        pos.y = SCREEN_HEIGHT - 38;
        collide = true;
    }
}

void Player::draw(Screen screen)
{
    screen.drawSprite(pos.x, pos.y, sprite, flipSprite);
}

void Player::setSprite(int input)
{
    switch(action) {
        case ACTION_NORMAL:
            switch(input) {
                case SDLK_RIGHT:
                    sprite = SPRITE;
                    flipSprite = false;
                    break;
                case SDLK_LEFT:
                    sprite = SPRITE;
                    flipSprite = true;
                    break;
                case SDLK_UP:
                    sprite = SPRITE_UP;
                    break;
                case SDLK_DOWN:
                    sprite = SPRITE_DOWN;
                    break;
            }
        case ACTION_SKID:
            sprite = SPRITE_SKID;
            if(groundSpeed < 0) { // moving left
                flipSprite = false;
            } else if(groundSpeed > 0) { // moving right
                flipSprite = true;
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

float Player::getxSpeed()
{
    xSpeed = groundSpeed * cos(groundAngle);
    return xSpeed;
}

void Player::setxSpeed(SDL_Event e)
{
    if(e.type == SDL_KEYDOWN && e.key.repeat == 0) {
    switch (e.key.keysym.sym) {
        case SDLK_LEFT: // pressing left
            if(xSpeed > 0) { // moving right
                sprite = SPRITE_SKID;
                flipSprite = false;

                // xSpeed -= DECEL_SPEED;

                /* // quick turnaround
                if(xSpeed <= 0) {
                    xSpeed = -0.5;
                }*/
            
		     } else if(xSpeed <= 0) { // moving left
                sprite = SPRITE;
                flipSprite = true;

                xSpeed += -ACCEL_SPEED;

                if(xSpeed <= -TOP_SPEED) {
				    xSpeed = -TOP_SPEED; // limit
                }
            }
            break;

        case SDLK_RIGHT: // pressing right
            if(xSpeed < 0) { // moving left
                sprite = SPRITE_SKID;
                flipSprite = true;

                // xSpeed += DECEL_SPEED;

                /* // quick turnaround
                if(xSpeed >= 0) {
                    xSpeed = 0.5;
                }*/
            
		    } else if(xSpeed >= 0) { // moving right
                sprite = SPRITE;
                flipSprite = false;

                xSpeed += ACCEL_SPEED;

                if(xSpeed >= TOP_SPEED) {
				    xSpeed = TOP_SPEED; // limit
                }
            }
            break;
    }

    } else if(e.type == SDL_KEYUP && e.key.repeat == 0) {
        setFriction();
    }
}

float Player::getySpeed()
{
    ySpeed = groundSpeed * -sin(groundAngle);
    return ySpeed;
}

void Player::setySpeed(SDL_Event e)
{
    if(e.type == SDL_KEYDOWN && e.key.repeat == 0) {
    switch(e.key.keysym.sym) {
        case SDLK_UP:
            action = ACTION_LOOKUP;
            sprite = SPRITE_UP;
            break;

        case SDLK_DOWN:
            action = ACTION_CROUCH;
            sprite = SPRITE_DOWN;
            break;
    }
    } else if(e.type == SDL_KEYUP && e.key.repeat == 0) {
        action = ACTION_NORMAL;
        sprite = SPRITE;
    }
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
void Player::setGroundSpeed(SDL_Event e)
{
    if(e.type == SDL_KEYDOWN && e.key.repeat == 0) {
    switch (e.key.keysym.sym) {
        case SDLK_LEFT: // pressing left
            //while (groundSpeed >= -TOP_SPEED) {
                if(groundSpeed > 0) { // moving right
                    action = ACTION_SKID;
                    sprite = SPRITE_SKID;
                    flipSprite = false;

                    // groundSpeed -= DECEL_SPEED;

                    // quick turnaround
                    /* if(groundSpeed <= 0) {
                        groundSpeed = -0.5;
                    }*/
                } else if(groundSpeed >= -TOP_SPEED) { // moving left
                    action = ACTION_NORMAL;
                    sprite = SPRITE;
                    flipSprite = true;

                    groundSpeed -= ACCEL_SPEED;

                    if(groundSpeed <= -TOP_SPEED) {
                        groundSpeed = -TOP_SPEED; // limit
                    }
                }
            //}
            break;

        case SDLK_RIGHT: // pressing right
            //while (groundSpeed <= TOP_SPEED) {
                if(groundSpeed < 0) { // moving left
                    action = ACTION_SKID;
                    sprite = SPRITE_SKID;
                    flipSprite = true;
                    // groundSpeed += DECEL_SPEED;
                    
                    // quick turnaround
                    /* if(groundSpeed >= 0) {
                        groundSpeed = 0.5;
                    }*/

                } else if(groundSpeed <= TOP_SPEED) { // moving right
                    action = ACTION_NORMAL;
                    sprite = SPRITE;
                    flipSprite = false;

                    groundSpeed += ACCEL_SPEED;

                    if(groundSpeed >= TOP_SPEED) {
                        groundSpeed = TOP_SPEED; // limit
                    }
                }
            //}
            break;
    }

    } else if(e.type == SDL_KEYUP && e.key.repeat == 0) {
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

void Player::variableJumpHeight(SDL_Event e)
{
    // checked before updating player position & gravity is calculated
    switch (e.key.keysym.sym) {
        case NULL:
            if(ySpeed < -4) {
                ySpeed = -4;
            }
            break;
    }
}

// AIRBORNE
void Player::airAcceleration(SDL_Event e)
{
    if(e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.sym) {
            case SDLK_RIGHT:
                xSpeed -= AIR_ACCEL_SPEED;
                break;
            case SDLK_LEFT:
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
    groundAngle += 2.8125; // 2 in hex
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
