#include "object.h"

void Object::setPos(Position &pos)
{
    pos.x = 100;
    pos.y = 5;
}

/*Object::Object()
{
    type = TYPE_UNKNOWN;
    pos.x = 0;
    pos.y = 0;
}*/

/*
void Object::setHitbox(Player player, Hitbox &hitbox)
{
    hitbox.pos.x = player.pos.x;
    hitbox.pos.y = player.pos.y;

    if(player.type == TYPE_PLAYER) {
        switch(player.action) {
            case ACTION_NORMAL:
                hitbox.hRadius = player.hRadius - 3;
                hitbox.wRadius = 8;
                break;
            case ACTION_CROUCH:
                hitbox.pos.y += 12;
                hitbox.hRadius = 10;
                break;
        }
    }
}*/