#include "items.h"

// RINGS
Ring::Ring(int x, int y)
{
    type = TYPE_RING;
    active = true;

    setPos(x, y);
    setRadius(6, 6); // 8, 8 when scattered 
    setHitbox(); // 13, 13

    sprite.s = ringSprites[0];
}

void Ring::update()
{
    if(!active) {
        // not in play
    } else {
        sprite.s = ringSprites[animFrame / 4]; // slows to 1/4 speed
        animFrame++;

        if(animFrame / 4 > 3) {
            animFrame = 0;
        }
    }

    setHitbox();
}

// SPRING
Spring::Spring(int x, int y)
{
    type = TYPE_SPRING;
    // type = TYPE_SPRING_HOR;
    // type = TYPE_SPRING_VERT;
    active = true;

    setPos(x, y);
    setRadius(8, 14); // horizontal
    setRadius(16, 8); //vertical

    // sprite.sprite = SPRITE_SPRING;
    sprite.flip = false;
}