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

void updatePlayer()
{
    // NORMAL
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

    // ROLLING
    // adjust ground_speed based on groundAngle
    // isJump();
    // adjust groundSpeed based on input + friction & accel/decel
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

Position Player::getPos()
{
    return pos;
}

void Player::setPos(Position &pos)
{
    pos.x = 5;
    pos.y = 5;
}

Hitbox Player::getHitbox()
{
    return hitbox;
}

void Player::setHitbox(Hitbox &hitbox)
{
    hitbox.pos.x = pos.x;
    hitbox.pos.y = pos.y;

	hitbox.hRadius = hRadius - 3;
	hitbox.wRadius = 8;

    int isCrouch; // TEMP SO NO ERROR IN IF

    if(isCrouch) {
        hitbox.pos.y += 12;
        hitbox.hRadius = 10;
    }
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

float Player::get_xSpeed(int input)
{
    //x = player.groundSpeed * cos(player.groundAngle);
    switch (input) {
    case LEFT: // pressing left
        if(xSpeed > 0) { // moving right
			xSpeed -= deceleration_speed;
			//player.sprite = SPRITE_SKID_LEFT;
			if(xSpeed <= 0) {
				xSpeed = -0.5;
			}
		} else if(xSpeed >= 0) { // moving left
			xSpeed -= acceleration_speed;
			//player.sprite = SPRITE_LEFT;
			if(xSpeed <= -top_speed) {
				xSpeed = -top_speed; // limit
			}
        }
        break;

    case RIGHT: // pressing right
        if(xSpeed < 0) { // moving left
			xSpeed += deceleration_speed;
			//player.sprite = SPRITE_SKID_RIGHT;
			if(xSpeed >= 0) {
				xSpeed = 0.5;
			}
		} else if(xSpeed >= 0) { // moving right
			xSpeed += acceleration_speed;
			//player.sprite = SPRITE_RIGHT;
			if(xSpeed >= top_speed) {
				xSpeed = top_speed; // limit
			}
		}
        break;
    }

    return xSpeed;
}

float Player::get_ySpeed()
{
    ySpeed = groundSpeed * -sin(groundAngle);
    return ySpeed;
}

float Player::get_friction()
{
	if(xSpeed < 0) { // moving left
            xSpeed += friction_speed;
            if(xSpeed >= 0) {
                xSpeed = 0;
            }
        } else if(xSpeed > 0) { // moving right
            xSpeed -= friction_speed;
            if(xSpeed <= 0) {
                xSpeed = 0;
            }
        }

    return xSpeed;
}

// STUFF TO IMPLEMENT LATER !!

// SPEED FOR SLOPES
float Player::get_groundSpeed(int input)
{
    if(input == LEFT) { // pressing left
        while (groundSpeed > -top_speed) {
            if(groundSpeed > 0) { // moving right
                groundSpeed -= deceleration_speed;
                if(groundSpeed <= 0) {
                    groundSpeed = -0.5;
                }
            } else if(groundSpeed > -top_speed) { // moving left
                groundSpeed -= acceleration_speed;
                if(groundSpeed <= -top_speed) {
                    groundSpeed = -top_speed; // limit
                }
            }
        }
    }

    if(input == RIGHT) { // pressing right
        while (groundSpeed < top_speed) {
            if(groundSpeed < 0) { // moving left
                groundSpeed += deceleration_speed;
                if(groundSpeed >= 0) {
                    groundSpeed = 0.5;
                }
            } else if(groundSpeed > top_speed) { // moving right
                groundSpeed += acceleration_speed;
                if(groundSpeed >= top_speed) {
                    groundSpeed = top_speed; // limit
                }
            }
        }
    }

    // friction
    if(input == NONE) {
        if(groundSpeed < 0) { 
            groundSpeed += friction_speed;
            if(groundSpeed >= 0) {
                groundSpeed = 0;
            }
        } else if(groundSpeed > 0) {
            groundSpeed -= friction_speed;
            if(groundSpeed <= 0) {
                groundSpeed = 0;
            }
        }
    }

    return groundSpeed;
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
