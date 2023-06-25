#include "player.h"

// constructor
Player::Player()
{
    setPos(pos);
    xSpeed = 0;
    ySpeed = 0;
}

// destructor
Player::~Player()
{
    // nothing to do here
}

void Player::update()
{
    // ROLLING
    if(rolling == true) {
    // adjust groundSpeed based on groundAngle
    // isJump();
    // get_groundSpeed();
        // adjust groundSpeed based on input + friction & accel/decel
    // wallCollision();
    // setCamera();
    // move();
    // floorCollision();
    // isSlipping()/isFalling();
    }

    // AIRBORNE
    else if(airborne == true) {
    // check for jump button release
    // isSuper();
    // update xSpeed based on input
    // apply air drag
    // move();
    // apply gravity
        // update ySpeed by adding gravity
    // isUnderWater();
    // groundAngle = 0;
    // airCollision();
    }

    // NORMAL
    else {
    // check for special actions (balancing, etc.)
    // isSpinDash();
    // adjust ground_speed based on groundAngle
    // isJump();
    // adjust groundSpeed based on input + friction & accel/decel
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
    }

    // check hitboxes
}

void Player::move(float time, Player &player)
{
    // move left or right
    pos.x += xSpeed * time;

    // too far left or right
	if(pos.x < 0) {
        pos.x = 0;
    } else if(pos.x > SCREEN_WIDTH - 29) {
        pos.x = SCREEN_WIDTH - 29;
    }
    
    // move up or down
    pos.y += ySpeed * time;

    // too far up or down
	if(pos.y < 0) {
        pos.y = 0;
    } else if(pos.y > SCREEN_HEIGHT - 38) {
        pos.y = SCREEN_HEIGHT - 38;
    }
}

void Player::setPos(Position &pos)
{
    pos.x = 5;
    pos.y = 5;
}

void Player::setHitbox(Hitbox &hitbox)
{
    hitbox.pos.x = pos.x;
    hitbox.pos.y = pos.y;

	hitbox.hRadius = hRadius - 3;
	hitbox.wRadius = 8;

    if(action == ACTION_CROUCH) {
        hitbox.pos.y += 12;
        hitbox.hRadius = 10;
    }
}

SDL_Rect Player::setSprite(int input)
{
    switch(action) {
        case ACTION_NORMAL:
            switch(input) {
                case KEY_RIGHT:
                    sprite = SPRITE;
                    flipSprite = false;
                    break;
                case KEY_LEFT:
                    sprite = SPRITE;
                    flipSprite = true;
                    break;
                case KEY_UP:
                    sprite = SPRITE_UP;
                    break;
                case KEY_DOWN:
                    sprite = SPRITE_DOWN;
                    break;
            }
        case ACTION_SKID:
            sprite = SPRITE_SKID;
            break;
    }

    return sprite;
}

// mode for collisions
void Player::setMode(Player &player)
{
    if(0 <= groundAngle <= 45 || 315 <= groundAngle <= 360) {
        mode = FLOOR;
    } else if(46 <= groundAngle <= 134) {
        mode = LEFT_WALL;
    } else if(135 <= groundAngle <= 225) {
        mode = CEILING;
    } else if(226 <= groundAngle <= 314) {
        mode = RIGHT_WALL;
    }
}

void Player::setxSpeed(int input, Player &player)
{
    //x = player.groundSpeed * cos(player.groundAngle);

    switch (input) {
        case KEY_LEFT: // pressing left
            if(xSpeed > 0) { // moving right
                xSpeed -= DECEL_SPEED;

                sprite = SPRITE_SKID;
                flipSprite = false;

                // quick turnaround
                if(xSpeed <= 0) {
                    xSpeed = -0.5;
                }
		    } else if(xSpeed >= 0) { // moving left
                xSpeed -= ACCEL_SPEED;

                if(xSpeed <= -TOP_SPEED) {
				    xSpeed = -TOP_SPEED; // limit
                }
            }
            break;

    case KEY_RIGHT: // pressing right
        if(xSpeed < 0) { // moving left
			xSpeed += DECEL_SPEED;

			sprite = SPRITE_SKID;
            flipSprite = true;

            // quick turnaround
			if(xSpeed >= 0) {
				xSpeed = 0.5;
			}
		} else if(xSpeed >= 0) { // moving right
			xSpeed += ACCEL_SPEED;

			if(xSpeed >= TOP_SPEED) {
				xSpeed = TOP_SPEED; // limit
			}
		}
        break;
    }
}

void Player::setySpeed(int input, Player &player)
{
    // ySpeed = groundSpeed * -sin(groundAngle);
    
    if(input == KEY_UP) {
        ySpeed -= ACCEL_SPEED;
    } else if(input == KEY_DOWN) {
        ySpeed += ACCEL_SPEED;
    }
}

void Player::setFriction(Player &player)
{
	if(xSpeed < 0) { // moving left
            xSpeed += FRICTION_SPEED;
            if(xSpeed >= 0) {
                xSpeed = 0;
            }
        } else if(xSpeed > 0) { // moving right
            xSpeed -= FRICTION_SPEED;
            if(xSpeed <= 0) {
                xSpeed = 0;
            }
        }
}

// STUFF TO IMPLEMENT LATER !!

// SPEED FOR SLOPES
void Player::setGroundSpeed(int input, Player &player)
{
    if(input == KEY_LEFT) { // pressing left
        while (groundSpeed > -TOP_SPEED) {
            if(groundSpeed > 0) { // moving right
                groundSpeed -= DECEL_SPEED;
                if(groundSpeed <= 0) {
                    groundSpeed = -0.5;
                }
            } else if(groundSpeed > -TOP_SPEED) { // moving left
                groundSpeed -= ACCEL_SPEED;
                if(groundSpeed <= -TOP_SPEED) {
                    groundSpeed = -TOP_SPEED; // limit
                }
            }
        }
    }

    if(input == KEY_RIGHT) { // pressing right
        while (groundSpeed < TOP_SPEED) {
            if(groundSpeed < 0) { // moving left
                groundSpeed += DECEL_SPEED;
                if(groundSpeed >= 0) {
                    groundSpeed = 0.5;
                }
            } else if(groundSpeed > TOP_SPEED) { // moving right
                groundSpeed += ACCEL_SPEED;
                if(groundSpeed >= TOP_SPEED) {
                    groundSpeed = TOP_SPEED; // limit
                }
            }
        }
    }

    // friction
    if(input == NULL) {
        if(groundSpeed < 0) { 
            groundSpeed += FRICTION_SPEED;
            if(groundSpeed >= 0) {
                groundSpeed = 0;
            }
        } else if(groundSpeed > 0) {
            groundSpeed -= FRICTION_SPEED;
            if(groundSpeed <= 0) {
                groundSpeed = 0;
            }
        }
    }
}

// JUMPING
/*
void jumpVelocity(Player player)
{
    player.xSpeed -= JUMP_FORCE * sin(player.groundAngle);
    player.ySpeed -= JUMP_FORCE * cos(player.groundAngle);
}

void variableJumpHeight(int input, Player player)
{
    // checked before updating player position & gravity is calculated
    if(input == NULL) {
        if(player.ySpeed < -4) {
            player.ySpeed = -4;
        }
    }
}

// AIRBORNE
void airAcceleration(int input, Player player)
{
    if(input == KEY_RIGHT) {
        player.xSpeed -= AIR_ACCEL_SPEED;
    }
    if(input == KEY_LEFT) {
        player.xSpeed += AIR_ACCEL_SPEED;
    }

    if(player.xSpeed >= TOP_SPEED) {
        player.xSpeed = TOP_SPEED;
    }
}

void gravity(Player player)
{
    // for every step player is airborne
    player.ySpeed += GRAVITY_FORCE;
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
*/
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
