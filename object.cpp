#include "object.h"

void Object::destroy()
{
    SDL_DestroyTexture(sprite.tex);
}

void Object::update()
{
    pos.x++;
}

void Object::draw(Screen scr, SDL_Rect cam)
{
    SDL_Rect box;
    box.x = pos.x;
    box.y = pos.y;
    box.w = radius.w;
    box.h = radius.h;

    //if(checkCollision(box, cam)) {
        scr.drawSprite((pos.x - cam.x), (pos.y - cam.y), sprite.s, sprite.tex, sprite.flip);
    //}
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

void Object::setHitbox(int h, int w)
{
    hitbox.h = h;
    hitbox.w = w;
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