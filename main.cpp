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
	//if(!startUp(window, renderer, image, texture)) {
	//	cerr << "Failed to initialize! SDL_Error: " << SDL_GetError() << endl;
	//	return 0;
	//}

	startUp(window, renderer, image, texture);
	
	// initialize player
	Player player;

	Timer timer;

	timer.start();

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

		float time = timer.getTicks() / 1000.f;

		player.move(time, player);

		// restart timer
        timer.start();

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

int getInput(SDL_Event e)
{
	SDL_PollEvent(&e);

	int input;

	switch (e.type)
	{
		case SDL_QUIT:
			input = KEY_QUIT;
			break;
		case SDL_KEYDOWN:
			switch (e.key.keysym.sym)
			{
				case SDLK_LEFT:
					input = KEY_LEFT;
					break;
				case SDLK_RIGHT:
					input = KEY_RIGHT;
					break;
				case SDLK_UP:
					input = KEY_UP;
					break;
				case SDLK_DOWN:
					input = KEY_DOWN;
					break;
			}
			break;
	}
	
	return input;
}
