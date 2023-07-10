#include "player.h"

// constructor
Player::Player(int x, int y)
{
    type = TYPE_PLAYER;
    action = ACTION_NORMAL;
    mode = FLOOR;

    active = true;

    collide.reset();
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

    //if(collide.floor) {
    //    grounded = true;
    //}

    // AIRBORNE
    if(!grounded) {
        setRadius(19, 9);

        groundSpeed = 0; // not on ground!

            if((collide.islWall() && (xSpeed < 0)) || (collide.isrWall() && (xSpeed > 0))) {
                xSpeed = 0;
            }

        if(action == ACTION_JUMP && !input.isSpace()) {
            // jump button released
        }

        xSpeed = getSpeed(xSpeed);
            // update xSpeed based on input

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

        if(collide.isFloor()) {
            ySpeed = 0;
            groundSpeed = xSpeed; // to keep momentum
            grounded = true;
            action = ACTION_NORMAL;
        }

        // airCollision();
    }

    // NORMAL
    if(grounded) {
        setRadius(19, 9);

        // check for special actions (balancing, etc.)

        if(mode != CEILING) {
            groundSpeed -= SLOPE_FACTOR * sin(groundAngle);
        }
            // adjust groundSpeed based on groundAngle

        if(input.isUp()) {
            action = ACTION_LOOKUP;
        }

        if(input.isDown()) {
            action = ACTION_CROUCH;
            setRadius(14, 7);
        }

        // ifJump();
        if(input.isSpace()) {
            action = ACTION_JUMP;
            grounded = false;
            jumpVelocity();
        }

        if(action == ACTION_NORMAL || action == ACTION_SKID || action == ACTION_CROUCH || action == ACTION_LOOKUP) {

            groundSpeed = getSpeed(groundSpeed);
                // adjust groundSpeed based on input + friction & accel/decel
        
            // wallCollision();
            if((collide.islWall() && (groundSpeed < 0)) || (collide.isrWall() && (groundSpeed > 0))) {
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
    } // if active

    // check hitboxes

    setSprite();

    move();

}

void Player::move()
{
    // move left or right
    pos.x += xSpeed;

    // too far left or right
    collide.screenCollision_hor(pos.x);

    // move up or down
    pos.y += ySpeed;

    // too far up or down
    collide.screenCollision_ver(pos.y);
}

void Player::setSprite()
{
    switch(action) {
        case ACTION_NORMAL:
        case ACTION_JUMP:
            sprite.s = SPRITE;

            if(input.isRight()) {
                sprite.flip = false;
            }
            if(input.isLeft()) {
                sprite.flip = true;
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
                sprite.flip = true;
            }
            if(input.isLeft()) { // pressing left, moving right
                sprite.flip = false;
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

float Player::getSpeed(float speed)
{
    // float speed is temp to return to either groundSpeed or xSpeed

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

    if(input.isNone()) { //!input.isLeft() && !input.isRight()) {
        if(grounded) {
            action = ACTION_NORMAL;
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

void Player::jumpVelocity()
{
    // if player hits jump button, do this
    xSpeed -= JUMP_FORCE * sin(groundAngle);
    ySpeed -= JUMP_FORCE * cos(groundAngle);
}

void Player::variableJumpHeight()
{
    // checked before updating player position & gravity is calculated
    if(input.isNone()) {
        if(ySpeed < -4) {
            ySpeed = -4;
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
