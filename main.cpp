#include "main.h"

int main(int argc, char* args[])
{
	// game flags
    bool quit = false;
	bool debug = true;

	// initialize screen
	Screen screen;

	if(!screen.startUp()) {
		cerr << "Failed to initialize! SDL_Error: " << SDL_GetError() << endl;
		return 0;
	}

	// initialize player
	Player player;
	player.create();

	// initialize timer for frames
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

			player.update(e);
		}

		float time = stepTimer.getTicks() / 1000.f;

		player.move(time);

		// restart timer
        stepTimer.start();

		// render sprite at (x, y)
		player.draw(screen);

		if(debug) {
			debugText(player, screen);
		}

		screen.present();
		
		// delay for frame rate
		SDL_Delay(16);
	}

	// shutdown SDL
	screen.shutDown();

	return 0;
}

void debugText(Player player, Screen screen)
{
	static stringstream text1;
	static stringstream text2;

	text1.str("");
	text2.str("");

	text1 << "X Pos: " << player.pos.x << "\nY Pos: " << player.pos.y;
	screen.loadText(text1.str().c_str());
	screen.drawText(1, (SCREEN_HEIGHT - 20));

	text2 << "\nX Speed: " << player.returnxSpeed() << "\nY Speed: " << player.returnySpeed();
	text2 << "\nGround Speed: " << player.returngroundSpeed();
	screen.loadText(text2.str().c_str());
	screen.drawText(1, (SCREEN_HEIGHT - 10));
}