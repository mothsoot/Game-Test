#include "main.h"

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

	timer stepTimer;

	stepTimer.start();

	//pos startPos;
	//startPos.x = 5;
	//startPos.y = 5;

	// handle events
	// loop getting player input
	// getting sprite to draw
	// do movement
	// drawing sprite on screen
	// update
	while (!quit)
	{
		SDL_Event e;

		// PollEvent returns 1 if there is an event in queue
		// returns 0 if none
		// while events in queue
        while (SDL_PollEvent(&e) != 0) {
			if(e.type == SDL_QUIT) {
				quit = true;
			}

			handleEvent(e, player);
		}

		float time = stepTimer.getTicks() / 1000.f;

		move(time, player);

		// restart step timer
        stepTimer.start();

		// render sprite at (x, y)
		render(renderer, texture, player);

		// update screen
		SDL_RenderPresent(renderer);
		
		SDL_Delay(16);
	}
	
	// shutdown SDL
	shutDown(window, renderer, texture);

	return 0;
}

void handleEvent(SDL_Event e, Player &player)
{
	static int direction;


    // key pressed
	if(e.type == SDL_KEYDOWN && e.key.repeat == 0) {
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
				player.xSpeed = player.get_xSpeed(LEFT);
				break;

            case SDLK_RIGHT:
				player.sprite = SPRITE_RIGHT;
				direction = 1;
				player.xSpeed = player.get_xSpeed(RIGHT);
				break;
		}
	}
    
    // key released
	// if this frame receives no input
    if (e.type == SDL_KEYUP && e.key.repeat == 0) {
		player.xSpeed = player.get_friction();
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
