#include "screen.h"

bool Screen::startUp() //SDL_Window* &window, SDL_Renderer* &renderer, SDL_Texture* &texture)
{
	// initialize SDL
	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		cerr << "Could not initialize SDL!! SDL_Error: " << SDL_GetError() << endl;
		return false;
	}
	
	// initialize SDL_Image for image files
	if(IMG_Init(IMG_INIT_PNG) < 0) {
		cerr << "Could not initialize SDL_Image!! IMG_Error: " << IMG_GetError() << endl;
		return false;
	}

	// initialize SDL_TTF for fonts
	if(TTF_Init() < 0) {
		cerr << "Could not initialize SDL_TTF!! TTF_Error: " << TTF_GetError() << endl;
		return false;
	}

	// create window to render in
	window = SDL_CreateWindow("Game moment", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	if(window == NULL) {
		cerr << "Window not created! SDL_Error: " << SDL_GetError() << endl;
		return false;
	}

	// create renderer for window
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		// window drawing in, rendering driver (-1 sets to default), sets SDL_RendererFlags
	if(renderer == nullptr) {
        cerr << "Renderer could not be created! SDL Error: " << SDL_GetError() << endl;
        return false;
    }

	// load font
	font = TTF_OpenFont("resources/NiseSegaSonic.ttf", 10);

	// set window colour to white
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    return true;
}

void Screen::shutDown()
{
	// deallocate resources
	SDL_DestroyTexture(textTexture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	window = nullptr;

	TTF_CloseFont(font);

	// quit SDL & extensions
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}

void Screen::prep()
{
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // set window colour to white
}

void Screen::present()
{
	// render screen :)!
	SDL_RenderPresent(renderer);
}

void Screen::drawSprite(int x, int y, SDL_Rect sprite, SDL_Texture* tex, bool flips)
{
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	if(flips == true) {
		flip = SDL_FLIP_HORIZONTAL;
	} else {
		flip = SDL_FLIP_NONE;
	}
	// SDL_FLIP_NONE, SDL_FLIP_HORIZONTAL, SDL_FLIP_VERTICAL

	// destination rectangle
	SDL_Rect dstrect = {x, y, sprite.w, sprite.h}; // x coord, y coord, image width, image height

	SDL_RenderCopyEx(renderer, tex, &sprite, &dstrect, NULL, NULL, flip);
}

void Screen::drawText(int x, int y)
{
	// get text width & height
	int texW, texH;
	SDL_QueryTexture(textTexture, NULL, NULL, &texW, &texH);

	// destination rectangle
	SDL_Rect dstrect = {x, y, texW, texH}; // x coord, y coord, image width, image height

	SDL_RenderCopy(renderer, textTexture, NULL, &dstrect);
}

SDL_Texture* Screen::loadSprites(string file)
{
	SDL_Surface* image = nullptr;

	image = IMG_Load(file.c_str());
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, image);

	// delete image
	SDL_FreeSurface(image);

	return texture;
}

SDL_Texture* Screen::loadText(string text)
{
    // render text surface
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), textColour);

    // create texture
    textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    SDL_FreeSurface(textSurface);

    return textTexture;
}