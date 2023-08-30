#include "player.h"

void Player::create()
{
    type = TYPE_PLAYER;
    active = true;
    action = ACTION_NORMAL;

    rings = 0;

    grounded = true;

    sprite.s = PLAYER_SPRITES_IDLE[0];

    hitbox.set(pos, sprite.s.w, sprite.s.h, sprite.s.y);
    xSpeed = 0;
    ySpeed = 0;
    groundSpeed = 0;
    groundAngle = 0;
}

void Player::update(Tile* tileList)
{
    if(!active) {
        // player dead!!
        return;
    }

    // AIRBORNE
    if(!grounded) {
        groundSpeed = 0; // not on ground!

        if((collide.isLeftScr() && (xSpeed < 0)) || (collide.isRightScr() && (xSpeed > 0))) {
            // hit left side of screen while moving left
            // hit right side of screen while moving right
            xSpeed = 0;
        }

        if(action == ACTION_JUMP && !input.isSpace()) {
            // jump button released, adjust jump height
            if(ySpeed < JUMP_RELEASE) {
                ySpeed = JUMP_RELEASE;
            }
        }

        // update xSpeed based on input
        xSpeed = setSpeed(xSpeed);
        // apply air resistance to xSpeed
        if(-4 < ySpeed < 0) {
            xSpeed -= ((xSpeed / 0.125) / 256);
        }

        // apply gravity to ySpeed
        ySpeed += GRAVITY_FORCE;

        // limit ySpeed, 16 in CD
        if(ySpeed >= 6) {
            ySpeed = 6;
        } else if(ySpeed <= -6) {
            ySpeed = -6;
        }

        // if hit the floor
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
        // adjust groundSpeed based on groundAngle
        groundSpeed -= SLOPE_FACTOR * sin(groundAngle);

        if(input.isUp()) {
            action = ACTION_LOOKUP;
        } else if(input.isDown()) {
            action = ACTION_CROUCH;
        } else {
            action = ACTION_NORMAL;
        }

        if(input.isSpace()) {
            jump();
        }

        if(action == ACTION_NORMAL || action == ACTION_SKID || action == ACTION_CROUCH || action == ACTION_LOOKUP) {
            // adjust groundSpeed based on input + friction & accel/decel
            groundSpeed = setSpeed(groundSpeed);

            if((collide.isLeftScr() && (groundSpeed < 0)) || (collide.isRightScr() && (groundSpeed > 0))) {
                // hit left side of screen while moving left
                // hit right side of screen while moving right
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
            setxSpeed();
            setySpeed();

            // }
            // groundAngle = groundSensor.tileAngle;
                // update groundAngle
            // pos.y += groundSensor.distance;
                // align sprite to ground
        }
    }

    setSprite();
    hitbox.set(pos, sprite.s.w, sprite.s.h, sprite.s.y);

    move();

    // should be moved up higher later
    for (int p = 0; p < MAX_TILES; p++) {
        groundCollision(&tileList[p]);
    }
}

void Player::move()
{
    // move left/right
    pos.x += xSpeed;
    // move up/down
    pos.y += ySpeed;

    // if out of screen
    collide.screenCollision(pos, hitbox, sprite.s);
}

void Player::setSprite()
{
    switch(action) {
        case ACTION_NORMAL:
            sprite.s = PLAYER_SPRITES_IDLE[0];

            // animate walk sprites
            if(groundSpeed != 0) {
                sprite.s = PLAYER_SPRITES_WALK[animFrame / animSpeed]; // slow
                animFrame++;

                if(animFrame / animSpeed > 7) {
                    animFrame = 0;
                }
            } else {
                animFrame = 0;
            }

            if(input.isRight()) {
                sprite.flip = SDL_FLIP_NONE;
            }
            if(input.isLeft()) {
                sprite.flip = SDL_FLIP_HORIZONTAL;
            }
            break;

        case ACTION_JUMP:
            sprite.s = PLAYER_SPRITES_JUMP[0];

            if(ySpeed >= 0) {
                sprite.s = PLAYER_SPRITES_JUMP[1]; // falling sprite
            }

            if(input.isRight()) {
                sprite.flip = SDL_FLIP_NONE;
            }
            if(input.isLeft()) {
                sprite.flip = SDL_FLIP_HORIZONTAL;
            }

            break;

        case ACTION_CROUCH:
            sprite.s = PLAYER_SPRITES_CROUCH[0];
            break;

        case ACTION_LOOKUP:
            sprite.s = PLAYER_SPRITES_LOOKUP[0];
            break;

        case ACTION_SKID:
            sprite.s = PLAYER_SPRITES_SKID[0];
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
        if(checkCollision(hitbox, objB->getHitbox())) {
            switch(objB->getType()) {
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

void Player::groundCollision(Tile* tile) //Tile tileList[])
{
    if(action != ACTION_JUMP || (action == ACTION_JUMP && ySpeed > 0)) {
        /* for (int p = 0; p < MAX_TILES; p++) {
            if(tileCollision(tileList[p].hitbox, hitbox, tileList[p].getType())) {
                collide.floor = true;
                pos.y = tileList[p].getyPos() - sprite.s.h;
            }
        }*/
        if(tileCollision(tile->hitbox, hitbox, tile->getType())) {
            collide.floor = true;
            pos.y = tile->getyPos() - (sprite.s.h + sprite.s.y);
        }
    } else {
        collide.floor = false;
    }
}

float Player::setSpeed(float speed)
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

void Player::setxSpeed()
{
    xSpeed = groundSpeed * cos(groundAngle);
}

void Player::setySpeed()
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
    action = ACTION_JUMP;
    grounded = false;

    xSpeed -= JUMP_FORCE * sin(groundAngle);
    ySpeed -= JUMP_FORCE * cos(groundAngle);
}

void Player::airRotation()
{
    // for every frame
    // depending on quadrant, smoothly return to 0
    if(groundAngle != 0) {
        groundAngle += 2.8125; // 2 in hex
    }
}
