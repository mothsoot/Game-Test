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
		else {
			// Shit, we are running behind!
		}
	}
	
	// shutdown SDL
	shutDown(window, renderer, texture);

	return 0;
}

timer::timer()
{
    //Initialize the variables
    mStartTicks = 0;
    mPausedTicks = 0;

    mPaused = false;
    mStarted = false;
}

void timer::start()
{
    //Start the timer
    mStarted = true;

    //Unpause the timer
    mPaused = false;

    //Get the current clock time
    mStartTicks = SDL_GetTicks();
	mPausedTicks = 0;
}

void timer::stop()
{
    //Stop the timer
    mStarted = false;

    //Unpause the timer
    mPaused = false;

	//Clear tick variables
	mStartTicks = 0;
	mPausedTicks = 0;
}

void timer::pause()
{
    //If the timer is running and isn't already paused
    if( mStarted && !mPaused )
    {
        //Pause the timer
        mPaused = true;

        //Calculate the paused ticks
        mPausedTicks = SDL_GetTicks() - mStartTicks;
		mStartTicks = 0;
    }
}

void timer::unpause()
{
    //If the timer is running and paused
    if( mStarted && mPaused )
    {
        //Unpause the timer
        mPaused = false;

        //Reset the starting ticks
        mStartTicks = SDL_GetTicks() - mPausedTicks;

        //Reset the paused ticks
        mPausedTicks = 0;
    }
}

Uint32 timer::getTicks()
{
	//The actual timer time
	Uint32 time = 0;

    //If the timer is running
    if( mStarted )
    {
        //If the timer is paused
        if( mPaused )
        {
            //Return the number of ticks when the timer was paused
            time = mPausedTicks;
        }
        else
        {
            //Return the current time minus the start time
            time = SDL_GetTicks() - mStartTicks;
        }
    }

    return time;
}

bool timer::isStarted()
{
	//Timer is running and paused or unpaused
    return mStarted;
}

bool timer::isPaused()
{
	//Timer is running and paused
    return mPaused && mStarted;
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
        /*switch(e.key.keysym.sym)
        {
            case SDLK_UP:
                player.ySpeed += deceleration_speed;
                break;
            case SDLK_DOWN:
                player.ySpeed -= deceleration_speed;
                break;
            case SDLK_LEFT:
                player.xSpeed += deceleration_speed;
                break;
            case SDLK_RIGHT:
                player.xSpeed -= deceleration_speed;
				break;
        }
		*/
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

void startUp(SDL_Window* &window, SDL_Renderer* &renderer, SDL_Surface* &image, SDL_Texture* &texture)
{
	SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow("Testy Testy", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);
	renderer = SDL_CreateRenderer(window, -1, 0);
        // First  = window drawing in
        // Second = rendering driver (-1 sets to default)
        // Third  = sets SDL_RendererFlags (0 sets to default hardware rendering) 
	image = SDL_LoadBMP("sonic-sprites.bmp");
	texture = SDL_CreateTextureFromSurface(renderer, image);

	SDL_FreeSurface(image);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // set window colour to white
}

void shutDown(SDL_Window* &window, SDL_Renderer* &renderer, SDL_Texture* &texture)
{
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	// quit SDL
	SDL_Quit();
}

void render(SDL_Renderer* renderer, SDL_Texture* texture, Player player)
{
	// destination rectangle
	SDL_Rect dstrect = {player.x, player.y, 29, 39}; // x coord, y coord, image width, image height

	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, texture, &player.sprite, &dstrect);
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
/*
bool isRight()
{
	int right = getInput();
	if(right == RIGHT) {
		return true;
	} else {
		return false;
	}
}

bool isLeft()
{
	int left = getInput();
	if(left == LEFT) {
		return true;
	} else {
		return false;
	}
}
*/

SDL_Rect spriteDirection(SDL_Event e)
{
	SDL_Rect player;
	static int direction;

	if(e.type == SDL_KEYDOWN) { // && e.key.repeat == 0
	switch (e.key.keysym.sym) {
		case SDLK_LEFT:
			player = SPRITE_LEFT;
			direction = -1;
			break;
		case SDLK_RIGHT:
			player = SPRITE_RIGHT;
			direction = 1;
			break;
		case SDLK_UP:
			if(direction < 0) {
				player = SPRITE_UP_LEFT;
			} else {
				player = SPRITE_UP_RIGHT;
			}
			break;
		case SDLK_DOWN:
			if(direction < 0) {
				player = SPRITE_DOWN_LEFT;
			} else {
				player = SPRITE_DOWN_RIGHT;
			}
			break;
	}
	}

	return player;
}

void movement(int input, Player &player)
{
	switch (input) {
		case LEFT:
			player.x--;
			/*
			while (player.xSpeed > -top_speed) {
            if(player.xSpeed > 0) { // moving right
                player.xSpeed -= deceleration_speed;
                if(player.xSpeed <= 0) {
                    player.xSpeed = -0.5;
                }
            } else if(player.xSpeed > -top_speed) { // moving left
                player.xSpeed -= acceleration_speed;
                if(player.xSpeed <= -top_speed) {
                    player.xSpeed = -top_speed; // limit
                }
            }
        	}
			*/
			break;
		
		case RIGHT:
			player.x++;
			break;
		case UP:
			player.y--;
			break;
		case DOWN:
			player.y++;
			break;
		
	}
	/*
	player.x += player.xSpeed;
	player.y++;
	*/
}

