#include "main.h"
#include "player.h"

int main(int argc, char* args[])
{
	// variables
    bool quit = false;
	
	// initialize SDL
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Surface* image;
	SDL_Texture* texture;
	startUp(window, renderer, image, texture);

	// initialize player
	Player player;

	SDL_Event e;
	timer stepTimer;

	stepTimer.start();

	float next_game_tick = SDL_GetTicks();
	int sleep_time = 0;

	// handle events
	// loop getting player input
	// getting sprite to draw
	// do movement
	// drawing sprite on screen
	// update
	while (!quit)
	{
        while (SDL_PollEvent(&e) != 0) {
			if(e.type == SDL_QUIT) {
				quit = true;
			}
			handleEvent(e, player);
		}

		float time = stepTimer.getTicks() / 1000.f;

		//player.sprite = spriteDirection(e);
		move(time, player);

		//Restart step timer
        stepTimer.start();

		// render sprite at (x, y)
		render(renderer, texture, player);
		
		// update screen
		SDL_RenderPresent(renderer);

		next_game_tick += SKIP_TICKS;
		sleep_time = next_game_tick - SDL_GetTicks();
		if(sleep_time >= 0) {
        Sleep(sleep_time);
		}
	}
	
	// shutdown SDL
	shutDown(window, renderer, texture);

	return 0;
}

void handleEvent(SDL_Event e, Player &player)
{
	static int direction;

    // key pressed
	if(e.type == SDL_KEYDOWN) { // && e.key.repeat == 0) {
        switch(e.key.keysym.sym) {
            case SDLK_UP:
				player.ySpeed -= acceleration_speed;

				// sprite
				if(direction < 0) {
					player.sprite = SPRITE_UP_LEFT;
				} else {
					player.sprite = SPRITE_UP_RIGHT;
				}
				break;
            case SDLK_DOWN:
				player.ySpeed += acceleration_speed;
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
            	if(player.xSpeed > 0) { // moving right
					player.xSpeed -= deceleration_speed;
					//player.sprite = SPRITE_SKID_LEFT;
                if(player.xSpeed <= 0) {
                    player.xSpeed = -0.5;
                }
				} else if(player.xSpeed >= 0) { // moving left
					player.xSpeed -= acceleration_speed;
					//player.sprite = SPRITE_LEFT;
					if(player.xSpeed <= -top_speed) {
						player.xSpeed = -top_speed; // limit
					}
				}
				break;
            case SDLK_RIGHT:
				player.sprite = SPRITE_RIGHT;
				direction = 1;
				if(player.xSpeed < 0) { // moving left
					player.xSpeed += deceleration_speed;
					//player.sprite = SPRITE_SKID_RIGHT;
					if(player.xSpeed >= 0) {
						player.xSpeed = 0.5;
					}
				} else if(player.xSpeed >= 0) { // moving right
					player.xSpeed += acceleration_speed;
					// player.sprite = SPRITE_RIGHT;
					if(player.xSpeed >= top_speed) {
						player.xSpeed = top_speed; // limit
					}
				}
				break;
		}			
    }
    
    // key released
    else if(e.type == SDL_KEYUP && e.key.repeat == 0) {
		if(player.xSpeed < 0) { // moving left
            player.xSpeed += friction_speed;
            if(player.xSpeed >= 0) {
                player.xSpeed = 0;
            }
        } else if(player.xSpeed > 0) { // moving right
            player.xSpeed -= friction_speed;
            if(player.xSpeed <= 0) {
                player.xSpeed = 0;
            }
        }
		}
}

void move(float time, Player &player)
{
	float DOT_WIDTH = 29;
	float DOT_HEIGHT = 38;
	float SCREEN_WIDTH = 640;
	float SCREEN_HEIGHT = 480;

    // move left or right
    player.x += player.xSpeed * time;

    // too far left or right
	if(player.x < 0) {
        player.x = 0;
    } else if(player.x > SCREEN_WIDTH - DOT_WIDTH) {
        player.x = SCREEN_WIDTH - DOT_WIDTH;
    }
    
    // move up or down
    player.y += player.ySpeed * time;

    // too far up or down
	if(player.y < 0) {
        player.y = 0;
    } else if(player.y > SCREEN_HEIGHT - DOT_HEIGHT) {
        player.y = SCREEN_HEIGHT - DOT_HEIGHT;
    }
}

int getInput(SDL_Event e)
{
	SDL_PollEvent(&e);

	int input;

	switch (e.type)
	{
		case SDL_QUIT:
			input = QUIT;
			break;
		case SDL_KEYDOWN:
			switch (e.key.keysym.sym)
			{
				case SDLK_LEFT:
					input = LEFT;
					break;
				case SDLK_RIGHT:
					input = RIGHT;
					break;
				case SDLK_UP:
					input = UP;
					break;
				case SDLK_DOWN:
					input = DOWN;
					break;
				case SDLK_SPACE:
					input = QUIT;
					break;
			}
			break;
	}
	
	return input;
}

