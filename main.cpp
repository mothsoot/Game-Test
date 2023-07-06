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
	// initialize ring
	Ring ring;
	ring.create();

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
			if(e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE) {
				quit = true;
			}

			player.input.keyState(e);
		}

		player.update();

		float time = stepTimer.getTicks() / 1000.f;

		// move player
		player.move(time);

		// restart timer
        stepTimer.start();

		// render sprites
		player.draw(screen);
		ring.draw(screen);

		if(debug) {
			debugText(player, screen);
		}

		// delay for frame rate
		SDL_Delay(16);

		screen.present();
	}

	// shutdown SDL
	screen.shutDown();

	return 0;
}

void debugText(Player player, Screen screen)
{
	stringstream action;
	stringstream keyPress;
	stringstream text1;
	stringstream text2;
	stringstream text3;

	action.str("");
	keyPress.str("");
	text1.str("");
	text2.str("");
	text3.str("");

	action << "Action: " << player.action;
	screen.loadText(action.str().c_str());
	screen.drawText(1, (SCREEN_HEIGHT - 50));

	keyPress << "Key: ";
	if(player.input.key == UP) {
		keyPress << "UP";
	} else if(player.input.key == DOWN) {
		keyPress << "DOWN";
	} else if(player.input.key == LEFT) {
		keyPress << "LEFT";
	} else if(player.input.key == RIGHT) {
		keyPress << "RIGHT";
	}
	screen.loadText(keyPress.str().c_str());
	screen.drawText(1, (SCREEN_HEIGHT - 40));

	text1 << "X Pos: " << player.pos.x << "\nY Pos: " << player.pos.y << "\nCollide? ";
	if(player.collide.floor || player.collide.lWall || player.collide.rWall || player.collide.ceiling) {
		text1 << "true";
	} else if(!player.collide.floor || !player.collide.lWall || !player.collide.rWall || !player.collide.ceiling) {
		text1 << "false";
	}
	screen.loadText(text1.str().c_str());
	screen.drawText(1, (SCREEN_HEIGHT - 30));

	text2 << "X Speed: " << player.xSpeed << "\nY Speed: " << player.ySpeed;
	text2 << "\nGround Speed: " << player.groundSpeed;
	screen.loadText(text2.str().c_str());
	screen.drawText(1, (SCREEN_HEIGHT - 20));

	text3 << "Height Radius: " << player.radius.h << "\nWidth Radius: " << player.radius.w;
	screen.loadText(text3.str().c_str());
	screen.drawText(1, (SCREEN_HEIGHT - 10));
}

void InputHandler::keyState(SDL_Event e)
{
    switch(e.type) {
	case SDL_KEYDOWN:
        keyDown = true;
        switch(e.key.keysym.sym) {
            case SDLK_UP:
                key = UP;
                break;
            case SDLK_DOWN:
                key = DOWN;
                break;
            case SDLK_LEFT:
                key = LEFT;
                break;
            case SDLK_RIGHT:
                key = RIGHT;
                break;
        }
		break;

    case SDL_KEYUP:
        keyDown = false;
        key = NONE;
		break;
	}
}