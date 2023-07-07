#include "items.h"

// RINGS
Ring::Ring(int x, int y)
{
    type = TYPE_RING;

    setPos(x, y);
    setRadius(6, 6); // 8, 8 when scattered 

    sprite.s = SPRITE_RING;
    sprite.flip = false;
}


// SPRING
Spring::Spring(int x, int y)
{
    type = TYPE_SPRING;
    // type = TYPE_SPRING_HOR;
    // type = TYPE_SPRING_VERT;

    setPos(x, y);
    setRadius(8, 14); // horizontal
    setRadius(16, 8); //vertical

    // sprite.sprite = SPRITE_SPRING;
    sprite.flip = false;
}