#pragma once

#include "main.h"
#include "player.h"

void handleEvent(Player player);

void handleEvent(SDL_Event e, Player &player)
{
	static int direction;

    // key pressed
	if(e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        switch(e.key.keysym.sym) {
            case SDLK_UP:
				player.ySpeed -= ACCEL_SPEED;

				// sprite
				if(direction < 0) {
					player.sprite = SPRITE_UP_LEFT;
				} else {
					player.sprite = SPRITE_UP_RIGHT;
				}
				break;

            case SDLK_DOWN:
				player.ySpeed += ACCEL_SPEED;
				// sprite
				if(direction < 0) {
					player.sprite = SPRITE_DOWN_LEFT;
				} else {
					player.sprite = SPRITE_DOWN_RIGHT;
				}
				break;

            case SDLK_LEFT:
				player.sprite = SPRITE_LEFT;
				direction = -1;
				player.xSpeed = player.get_xSpeed(KEY_LEFT);
				break;

            case SDLK_RIGHT:
				player.sprite = SPRITE_RIGHT;
				direction = 1;
				player.xSpeed = player.get_xSpeed(KEY_RIGHT);
				break;
		}
	}
    
    // key released
	// if this frame receives no input
    if (e.type == SDL_KEYUP && e.key.repeat == 0) {
		player.xSpeed = player.get_friction();
	}
}
