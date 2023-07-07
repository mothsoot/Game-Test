#include "object.h"

Object::Object()
{
    type = TYPE_UNKNOWN;
    active = true;
}

void Object::destroy()
{
    SDL_DestroyTexture(sprite.tex);
}

Position Object::setPos(int x, int y)
{
    // SDL draws from top-left corner
    // want position in center of sprite
    // player center is x - 9, y - 19 (x - 14, y - 7 when crouch/roll)

    pos.x = x; // - 9;
    pos.y = y; // - 19;

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

void Object::draw(Screen screen)
{
    screen.drawSprite(pos.x, pos.y, sprite.s, sprite.tex, sprite.flip);
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