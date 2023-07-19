#include "object.h"

bool objectCollision(Object objA, Object objB)
{
    if(objA.active && objB.active) {
        return checkCollision(objA.hitbox, objB.hitbox);
    }
    return false;
}

void Object::destroy()
{
    SDL_DestroyTexture(sprite.tex);
}

void Object::update()
{

}

void Object::draw(Screen scr, Camera cam)
{
    if(active) {
        if(checkCollision(hitbox, cam.hitbox)) {
            scr.drawSprite((pos.x - cam.c.x), (pos.y - cam.c.y), sprite.s, sprite.tex, sprite.flip);
        }
    }
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

void Object::setRadius(int h, int w)
{
    radius.h = h;
    radius.w = w;
}

void Object::setRadius(int h, int w, int push)
{
    radius.h = h;
    radius.w = w;
    radius.push = push;
}

void Object::setHitbox()
{
    hitbox.pos.x = pos.x + radius.w;
    hitbox.pos.y = pos.y + radius.h;

    hitbox.left = pos.x;
    hitbox.right = pos.x + 16;
    hitbox.top = pos.y;
    hitbox.bottom = pos.y + 16;
}

/*void Object::setHitbox(Player player, Hitbox &hitbox)
{
    hitbox.pos.x = player.pos.x;
    hitbox.pos.y = player.pos.y;

    if(type == TYPE_PLAYER) {
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