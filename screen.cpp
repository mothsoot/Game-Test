#include "screen.h"

bool startUp(SDL_Window* &window, SDL_Renderer* &renderer, SDL_Surface* &image, SDL_Texture* &texture)
{
	bool success = true;

	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		cerr << "Could not initialize! SDL_Error: " << SDL_GetError() << endl;
		success = false;
	} else {
		window = SDL_CreateWindow("Testy Testy", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
		if(window == NULL) {
			cerr << "Window not created! SDL_Error: " << SDL_GetError() << endl;
		} else {
			//Create renderer for window
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        		// First  = window drawing in
	        	// Second = rendering driver (-1 sets to default)
    	    	// Third  = sets SDL_RendererFlags (0 sets to default hardware rendering)
			if(renderer == nullptr) {
                cerr << "Renderer could not be created! SDL Error: " << SDL_GetError() << endl;
                success = false;
            } else {
				image = SDL_LoadBMP("sonic-sprites.bmp");
				texture = SDL_CreateTextureFromSurface(renderer, image);

				SDL_FreeSurface(image);
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // set window colour to white
			}
		}
	}

    return success;
}

void shutDown(SDL_Window* &window, SDL_Renderer* &renderer, SDL_Texture* &texture)
{
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	window = nullptr;

	// quit SDL
	SDL_Quit();
}

void render(SDL_Renderer* renderer, SDL_Texture* texture, Player player)
{
	SDL_RendererFlip flip;
	if(player.flipSprite == true) {
		flip = SDL_FLIP_HORIZONTAL;
	} else {
		flip = SDL_FLIP_NONE;
	}
	// SDL_FLIP_NONE, SDL_FLIP_HORIZONTAL, SDL_FLIP_VERTICAL

	// destination rectangle
	SDL_Rect dstrect = {player.pos.x, player.pos.y, 29, 39}; // x coord, y coord, image width, image height

	SDL_RenderClear(renderer);
	SDL_RenderCopyEx(renderer, texture, &player.sprite, &dstrect, player.groundAngle, NULL, flip);
}