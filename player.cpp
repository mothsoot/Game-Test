#include "player.h"

// constructor
Player::Player(int x, int y, SDL_Texture* spriteTex)
{
    type = TYPE_PLAYER;
    active = true;
    action = ACTION_NORMAL;

    rings = 0;

    grounded = true;

    pos.set(x, y);
    rad.set(10, 14); // 22, 33 idle sprite
    hitbox.set(pos.x, pos.y, rad.h, rad.w);
    xSpeed = 0;
    ySpeed = 0;
    groundSpeed = 0;
    groundAngle = 0;

    sprite.s = SPRITE;
    sprite.tex = spriteTex;
}

void Player::update()
{
    if(!active) {
        // player dead!!
        return;
    }

    // AIRBORNE
    if(!grounded) {
        //setRadius(19, 9);

        groundSpeed = 0; // not on ground!

        if((collide.islWall() && (xSpeed < 0)) || (collide.isrWall() && (xSpeed > 0))) {
            // hit left wall while moving left
            // hit right wall while moving right
            xSpeed = 0;
        }

        if(action == ACTION_JUMP && !input.isSpace()) {
            // jump button released, adjust jump height
            jumpHeight();
        }

        // update xSpeed based on input
        xSpeed = getSpeed(xSpeed);

        // apply air resistance to xSpeed
        airDrag();
        // apply gravity to ySpeed
        ySpeed += GRAVITY_FORCE;

        // limit ySpeed, 16 in CD
        if(ySpeed >= 6) {
            ySpeed = 6;
        } else if(ySpeed <= -6) {
            ySpeed = -6;
        }

        if(collide.isFloor()) {
            ySpeed = 0;
            groundSpeed = xSpeed; // to keep momentum
            grounded = true;
            action = ACTION_NORMAL; // reset from jump
        }

        // airCollision();
    }

    // NORMAL
    if(grounded) {
        //setRadius(19, 9);

        // adjust groundSpeed based on groundAngle
        groundSpeed -= SLOPE_FACTOR * sin(groundAngle);

        if(input.isUp()) {
            action = ACTION_LOOKUP;
        } else if(input.isDown()) {
            action = ACTION_CROUCH;
            //setRadius(14, 7);
        } else {
            action = ACTION_NORMAL;
        }

        if(input.isSpace()) {
            action = ACTION_JUMP;
            grounded = false;
            jump();
        }

        if(action == ACTION_NORMAL || action == ACTION_SKID || action == ACTION_CROUCH || action == ACTION_LOOKUP) {
            // adjust groundSpeed based on input + friction & accel/decel
            groundSpeed = getSpeed(groundSpeed);

            if((collide.islWall() && (groundSpeed < 0)) || (collide.isrWall() && (groundSpeed > 0))) {
                // hit left wall while moving left
                // hit right wall while moving right
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
            
            // calculate xSpeed & ySpeed from groundSpeed & groundAngle
            getxSpeed();
            getySpeed();

            // }

            // groundCollision();
            // groundAngle = groundSensor.tileAngle;
                // update groundAngle
            // pos.y += groundSensor.distance;
                // align sprite to ground
        }
    }

    setSprite();
    hitbox.set(pos.x, pos.y, rad.h, rad.w);

    move();
}

void Player::move()
{
    // move left/right
    pos.x += xSpeed;

    // move up/down
    pos.y += ySpeed;

    // if out of screen
    collide.screenCollision(pos, sprite.s);
}

void Player::setSprite()
{
    switch(action) {
        case ACTION_NORMAL:
        case ACTION_JUMP:
            sprite.s = SPRITE;

            if(input.isRight()) {
                sprite.flip = SDL_FLIP_NONE;
            }
            if(input.isLeft()) {
                sprite.flip = SDL_FLIP_HORIZONTAL;
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
            if(input.isRight()) { // pressing right, moving left
                sprite.flip = SDL_FLIP_HORIZONTAL;
            }
            if(input.isLeft()) { // pressing left, moving right
                sprite.flip = SDL_FLIP_NONE;
            }
            break;
    }
}

bool Player::objectCollision(Object* objB)
{
    if(active && objB->active) {
        if(checkCollision(hitbox, objB->hitbox)) {
            switch(objB->type) {
                case TYPE_RING:
                        rings++;
                        objB->active = false;
                    break;
            }
            return true;
        }
    }
    return false;
}

float Player::getSpeed(float speed)
{
    // float speed is temp, returned to either groundSpeed or xSpeed

    if(input.isLeft()) { // pressing left
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
            if(grounded) {
                action = ACTION_NORMAL;
                speed -= ACCEL_SPEED;
            } else {
                speed -= AIR_ACCEL_SPEED;
            }

            if(speed <= -TOP_SPEED) {
                speed = -TOP_SPEED; // limit
            }
        }
    }

    if(input.isRight()) { // pressing right
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
            if(grounded) {
                action = ACTION_NORMAL;
                speed += ACCEL_SPEED;
            } else {
                speed += AIR_ACCEL_SPEED;
            }

            if(speed >= TOP_SPEED) {
                speed = TOP_SPEED; // limit
            }
        }
    }

    if(input.isNone() || (!input.isLeft() && !input.isRight() && (input.isDown() || input.isUp()))) {
        if(grounded) {
            speed = setFriction(speed);
        }
    }
    return speed;
}

void Player::getxSpeed()
{
    xSpeed = groundSpeed * cos(groundAngle);
}

void Player::getySpeed()
{
    ySpeed = groundSpeed * -sin(groundAngle);

    // stupid little bug when groundAngle = 0
    if(ySpeed == -0) {
        ySpeed = 0;
    }
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

void Player::jump()
{
    xSpeed -= JUMP_FORCE * sin(groundAngle);
    ySpeed -= JUMP_FORCE * cos(groundAngle);
}

void Player::jumpHeight()
{
    // checked before updating player position & gravity is calculated
    if(ySpeed < -4) {
        ySpeed = -4;
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
    if(-4 < ySpeed < 0) {
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
