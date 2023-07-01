#include "object.h"

Object::Object()
{
    type = TYPE_UNKNOWN;
}

Position Object::setPos(int x, int y)
{
    pos.x = x;
    pos.y = y;

    return pos;
}

Radius Object::setRadius(int h, int w)
{
    radius.h = h;
    radius.w = w;

    return radius;
}

Radius Object::setRadius(int h, int w, int push)
{
    radius.h = h;
    radius.w = w;
    radius.push = push;

    return radius;
}

/*void Object::setHitbox(Player player, Hitbox &hitbox)
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