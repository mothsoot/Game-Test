#include "items.h"

// RINGS
void Ring::create()
{
    type = TYPE_RING;

    setPos(50, 50);
    setRadius(6, 6); // 8, 8 when scattered 

    sprite = SPRITE_RING;
}

void Ring::draw(Screen screen)
{
    screen.drawSprite(pos.x, pos.y, sprite);
}

void Ring::destroy()
{

}

// SPRING
Spring::Spring()
{
    type = TYPE_SPRING;
    // type = TYPE_SPRING_HOR;
    // type = TYPE_SPRING_VERT;

    setPos(0, 0);
    setRadius(8, 14); // horizontal
    setRadius(16, 8); //vertical

    // sprite = SPRITE_SPRING;
}