#include "main.h"

int main(int argc, char* args[])
{
	// variables
    bool quit = false;
	
	// initialize SDL
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* texture;

	if(!startUp(window, renderer, texture)) {
		cerr << "Failed to initialize! SDL_Error: " << SDL_GetError() << endl;
		return 0;
	}

	// universal timer
	Timer gameTimer;
	gameTimer.start();

	// initialize player
	Player player;

	// initialize timer
	Timer stepTimer;
	stepTimer.start();

	// handle events
	// loop getting player input
	// getting sprite to draw
	// do movement
	// drawing sprite on screen
	// update
	while (!quit)
	{
		prep(renderer);

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

		player.move(time, player);

		// restart timer
        stepTimer.start();

		// render sprite at (x, y)
		drawPlayer(renderer, texture, player);

		present(renderer);
		
		// delay for frame rate
		SDL_Delay(16);
	}
	
	// shutdown SDL
	shutDown(window, renderer, texture);

	return 0;
}

void handleEvent(SDL_Event e, Player &player)
{
    // key pressed
	if(e.type == SDL_KEYDOWN && e.key.repeat == 0) {
		player.setxSpeed(e, player);
	}

    // key released
	// if this frame receives no input
    else if(e.type == SDL_KEYUP && e.key.repeat == 0) {
		player.setFriction(player);
	}
}