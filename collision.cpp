#include "collision.h"

bool checkCol(Hitbox boxA, Hitbox boxB)
{
    // if the side of A is outside B
    if(boxA.top >= boxB.bottom) { // top of A is lower than bottom of B
        return false;
    }
    if(boxA.bottom <= boxB.top) { // bottom of A is higher than top of B
        return false;
    }
    if(boxA.left >= boxB.right) { // left of A is further right than right of B
        return false;
    }
    if(boxA.right <= boxB.left) { // right of A is further left than left of B
        return false;
    }

    // is colliding!
    return true;
}

bool tileCol(Hitbox tileBox, Hitbox playerBox, int type)
{
    switch (type) {
        case 0: // TILE_NONE
            return false;
            break;
    
        case 1: // TILE_TOPSOLID
            if(!tileColAbove(playerBox.bottom, tileBox.top)) {
                return false;
            }
            break;

        case 2: // TILE_SIDEBOTTOMSOLID
            if(!tileColLeft(playerBox.right, tileBox.left)) {
                return false;
            }
            if(!tileColRight(playerBox.left, tileBox.right)) {
                return false;
            }
            if(!tileColBelow(playerBox.top, tileBox.bottom)) {
                return false;
            }
            break;

        case 3: // TILE_FULLSOLID
            if(!tileColLeft(playerBox.right, tileBox.left)) {
                return false;
            }
            if(!tileColRight(playerBox.left, tileBox.right)) {
                return false;
            }
            if(!tileColAbove(playerBox.bottom, tileBox.top)) {
                return false;
            }
            if(!tileColBelow(playerBox.top, tileBox.bottom)) {
                return false;
            }
            break;
    }

    return true;
}

bool tileColAbove(int pBottom, int tTop)
{
    if(pBottom < tTop) { // bottom of A is higher than top of B
        return false;
    }
    return true;
}

bool tileColBelow(int pTop, int tBottom)
{
    if(pTop > tBottom) { // top of A is lower than bottom of B
        return false;
    }
    return true;
}

bool tileColRight(int pLeft, int tRight)
{
    if(pLeft > tRight) { // left of A is further right than right of B
        return false;
    }
    return true;
}

bool tileColLeft(int pRight, int tLeft)
{
    if(pRight < tLeft) { // right of A is further left than left of B
        return false;
    }
    return true;
}

Collision::Collision()
{
    reset();
}

bool Collision::isNone()
{
    if(!floor && !lWall && !rWall && !ceiling) {
        return true;
    }
    return false;
}

bool Collision::isNoneScr()
{
    if(!bottomScr && !leftScr && !rightScr && !topScr) {
        return true;
    }
    return false;
}

void Collision::reset()
{
    floor = false;
    lWall = false;
    rWall = false;
    ceiling = false;

    topScr = false;
    leftScr = false;
    rightScr = false;
    bottomScr = false;
}

void Collision::screenCol(Position &pos, Hitbox box, SDL_Rect sprite)
{
	if(pos.x <= 0) {
        leftScr = true;
        pos.x = 0;
    } else if(pos.x >= LEVEL_WIDTH - sprite.w) {
        rightScr = true;
        pos.x = LEVEL_WIDTH - sprite.w;
    } else {
        leftScr = false;
        rightScr = false;
    }

    if(pos.y <= 0) {
        topScr = true;
        pos.y = 0;
    } else if(pos.y >= LEVEL_HEIGHT - sprite.h) {
        bottomScr = true;
        pos.y = LEVEL_HEIGHT - sprite.h;
    } else {
        topScr = false;
        bottomScr = false;
    }
}

// SENSORS!!

// right ground
void Sensor::sensorA(bool grounded)
{
    if(!grounded) {
        active = false;
    } else {
        active = true;

        pos.x; // = player.hitbox.pos.x
        pos.y; // = player.hitbox.pos.y + player.hitbox.height;

        //Tile* tile = getTile(pos);

        //tilePos = tile->getPos();
        //tileID = tile->getID();
    }
}

// left ground
void Sensor::sensorB(bool grounded)
{
    if(!grounded) {
        active = false;
    } else {
        active = true;

        pos.x; // = player.getxPos() + player.getwRad();
        pos.y; // = player.getyPos() + player.gethRad();
    }
}

void Sensor::sensorC()
{
    active = false;
}


void Sensor::sensorD()
{
    active = false;

}

// left wall
void Sensor::sensorE(float speed)
{
    if(speed < 0) {
        active = true;
    }
}

// right wall
void Sensor::sensorF(float speed)
{
    if(speed > 0) {
        active = true;
    }
}

// GROUND SENSORS

// whichever finds nearest ground tile has its distance & tile angle returned
// 
/*
bool Collision::groundCollision(Player player)
{
    Sensor ground;
    Sensor A = sensorA(player);
    Sensor B = sensorB(player);
    if(A.distance < B.distance) {
        ground.distance = A.distance;
        ground.tileAngle = A.tileAngle;
    } else if(A.distance > B.distance) {
        ground.distance = B.distance;
        ground.tileAngle = B.tileAngle;
    }

    if(player.grounded) { // player not airborne
        if(ground.distance < -14 || ground.distance > 14) {
            // no collision
            return false;
        } else {
            // collision
            player.pos.x += ground.distance;
            return true;
        }

        if(ground.flagged) { // check if tile is flagged
            // snap to nearest 90 degree
            // snapped_angle = (round(Ground Angle / 90) % 4) * 90;
            return true;
        } else {
            player.groundAngle = ground.tileAngle;
            return true;
        }
    }

    else if(!player.grounded) { // player airborne
        if(ground.distance >= 0) {
            // sensor not overlapping ground
            // no collision
            return false;
        }

        if((player.ySpeed < 0) && (player.xSpeed < absolute(player.ySpeed))) { // check if player moving mostly down, player falling
            if(A.distance >= -(player.ySpeed + 8) || B.distance >= -(player.ySpeed + 8)) {
                // collision
                return true;
                
                // landingGround(ground, player);
            }
        }
    
        if(player.xSpeed > absolute(player.ySpeed)) { // check if player moving mostly left/right
            if(player.ySpeed >= 0) {
                // collision
                return true;

                // landingGround(ground, player);
            }
        }

        if((player.ySpeed > 0) && (player.xSpeed < player.ySpeed)) { // check if player moving mostly up, player flying up
            // collision
            return true;
                
            // slope
            if(91 <= player.groundAngle <= 135 || 226 <= player.groundAngle <= 270) { // 191-160 & 95-64 in hex
                // player reattaches to ceiling
                player.groundSpeed = player.ySpeed * -sign(sin(player.groundAngle));
            }
            // ceiling
            else if(136 <= player.groundAngle <= 225) { // 159-96 in hex
                // player hits ceiling & doesn't reattach
                player.ySpeed = 0;
                // xSpeed is unaffected
            }
        }
    }
}*/

/* void landingGround(Sensor ground, Player &player)
{
    player.grounded = true;
    // get tile angle landed on
    player.groundAngle = ground.tileAngle;

    // shallow slope
    if(0 <= player.groundAngle <= 23 || 339 <= player.groundAngle <= 360) { // 255-240 & 15-0 in hex
        player.groundSpeed = player.xSpeed;
    }
    // slope
    else if(24 <= player.groundAngle <= 45 || 316 <= player.groundAngle <= 338) { // 239-224 & 31-16 in hex
        if(player.xSpeed > absolute(player.ySpeed)) { // check if player moving mostly left/right
            player.groundSpeed = player.xSpeed;
        } else {
            player.groundSpeed = player.ySpeed * 0.5 * -sign(sin(player.groundAngle));
        }
    }
    // steep slope
    else if(46 <= player.groundAngle <= 90 || 271 <= player.groundAngle <= 315) { // 223-192 & 63-32 in hex
        if(player.xSpeed > absolute(player.ySpeed)) { // check if player moving mostly left/right
            player.groundSpeed = player.xSpeed;
        } else {
            player.groundSpeed = player.ySpeed * -sign(sin(player.groundAngle));
        }
    }
} */

/* bool Collision::ceilingCollision(Player player)
{
    Sensor ceiling;
    Sensor C = sensorC(player);
    Sensor D = sensorD(player);
    if(C.distance < D.distance) {
        ceiling.distance = C.distance;
        ceiling.tileAngle = C.tileAngle;
    } else if(C.distance > D.distance) {
        ceiling.distance = D.distance;
        ceiling.tileAngle = D.tileAngle;
    }

    if(ceiling.distance > 0) {
        // no collision
        return false;
    } else {
        // collision
        player.pos.y -= ceiling.distance;
        return true;
    }
} */

/* bool Collision::wallCollision(Player player)
{
    // if collide with wall
    // if moving towards wall
    Sensor wall;

    if(player.groundSpeed > 0) { // moving right
        wall = sensorE(player);

        if() { // check if collide with wall
            // no collision
            return false;
        } else {
            // collision
            return true;
            // hitWall(wall, player);
        }
    }

    if(player.groundSpeed < 0) { // moving left
        wall = sensorF(player);

        if() { // check if collide with wall
            // no collision
            return false;
        } else {
            // collision
            return true;
            // hitWall(wall, player);
        }
    }
} */

/* void hitWall(Sensor wall, Player &player)
{
    if(player.mode == FLOOR) {
        if(wall.distance > 0) {
            // ignore
            // no collision
        } else {
            // collision
            player.groundSpeed = 0;

            if(player.groundSpeed < 0) { // moving right
                player.xSpeed += wall.distance;
            } else if(player.groundSpeed > 0) { // moving left
                player.xSpeed -= wall.distance;
            }
        }
    }

    if(player.mode == RWALL || player.mode == LWALL) {
        if(wall.distance > 0) {
            // ignore
            // no collision
        } else {
            // collision
            player.groundSpeed = 0;

            if(player.groundSpeed < 0) { // moving right
                player.ySpeed += wall.distance;
            } else if(player.groundSpeed > 0) { // moving left
                player.ySpeed -= wall.distance;
            }
        }
    }

    if(!player.grounded) {
        if(wall.distance > 0) {
            // ignore
            // no collision
        } else {
            player.xSpeed = 0;
            if(player.groundSpeed < 0) { // moving right
                player.pos.x += wall.distance;
            } else if(player.groundSpeed > 0) { // moving left
                player.pos.x -= wall.distance;
            }
        }
    }
} */

/*
// right ground
Sensor Collision::sensorA(Player player)
{
    Sensor A;
    A.pos.x = player.pos.x - player.radius.w;
    A.pos.y = player.pos.y - player.radius.h;

    // A.detected_height = A.pos.x - tile.pos.x;

    if(1 <= A.detected_height <= 15) {
        // good, no more checks needed
    }

    // surface is likely in adjacent tile
    else if(A.detected_height == 16) {
        // sensor regression

        // check UP by one solid tile
        if(A.detected_height == 0) { // or if empty
            // return distance to first tile
        }
    }
    else if(A.detected_height == 0) { // or if emtpy
        // sensor extension

        // check DOWN by one solid tile
        if(A.detected_height == 0) { // or if empty
            // no surface found
            // return distance to second tile
        }
    }

    // calculate distance to tile found


    return A;
}

// left ground
Sensor Collision::sensorB(Player player) 
{
    Sensor B;
    B.pos.x = player.pos.x + player.radius.w;
    B.pos.y = player.pos.y - player.radius.h;

    return B;
}

// right ceiling
Sensor Collision::sensorC(Player player)
{
    Sensor C;
    C.pos.x = player.pos.x - player.radius.w;
    C.pos.y = player.pos.y + player.radius.h;

    return C;
}

// left ceiling
Sensor Collision::sensorD(Player player)
{
    Sensor D;
    D.pos.x = player.pos.x + player.radius.w;
    D.pos.y = player.pos.y + player.radius.h;

    return D;
}

// right wall
Sensor sensorE(Player player)
{
    Sensor E;
    
    E.pos.x = player.pos.x - player.radius.push;
    if(player.groundAngle != 0 || !player.grounded) {
        E.pos.y = player.pos.y;
    } else {
        E.pos.y =  player.pos.y + 8;
    }
    return E;
}

// left wall
Sensor sensorF(Player player)
{
    Sensor F;
    F.pos.x = player.pos.x + player.radius.push;
    if(player.groundAngle != 0 || !player.grounded) {
        F.pos.y = player.pos.y;
    } else {
        F.pos.y =  player.pos.y + 8;
    }
    return F;
}
*/