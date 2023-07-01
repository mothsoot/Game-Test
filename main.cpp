#include "main.h"

int main(int argc, char* args[])
{
	// game running flag
    bool quit = false;

	// initialize screen
	Screen screen;

	if(!screen.startUp()) {
		cerr << "Failed to initialize! SDL_Error: " << SDL_GetError() << endl;
		return 0;
	}

	// initialize player
	Player player;
	player.create();

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
		screen.prep();

		SDL_Event e;

		// PollEvent returns 1 if there is an event in queue
		// returns 0 if none
		// while events in queue
        while (SDL_PollEvent(&e) != 0) {
			if(e.type == SDL_QUIT) {
				quit = true;
			}
			//handleEvent(e, player);
			player.update(e);
		}

		float time = stepTimer.getTicks() / 1000.f;

		player.move(time);

		// restart timer
        stepTimer.start();

		// render sprite at (x, y)
		player.draw(screen);

		screen.present();
		
		// delay for frame rate
		SDL_Delay(16);
	}

	// shutdown SDL
	screen.shutDown();

	return 0;
}