#include "screen.h"

bool Screen::startUp() //SDL_Window* &window, SDL_Renderer* &renderer, SDL_Texture* &texture)
{
	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		cerr << "Could not initialize SDL!! SDL_Error: " << SDL_GetError() << endl;
		return false;
	} 
	
	if(IMG_Init(IMG_INIT_PNG) < 0) {
		cerr << "Could not initialize SDL_Image!! IMG_Error: " << IMG_GetError() << endl;
		return false;
	}

	if(TTF_Init() < 0) {
		cerr << "Could not initialize SDL_TTF!! TTF_Error: " << TTF_GetError() << endl;
		return false;
	}
	
	window = SDL_CreateWindow("Game moment", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	if(window == NULL) {
		cerr << "Window not created! SDL_Error: " << SDL_GetError() << endl;
		return false;
	}

	// create renderer for window
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        // First  = window drawing in
	    // Second = rendering driver (-1 sets to default)
    	// Third  = sets SDL_RendererFlags (0 sets to default hardware rendering)
	if(renderer == nullptr) {
        cerr << "Renderer could not be created! SDL Error: " << SDL_GetError() << endl;
        return false;
    }

	texture = loadSprites("sonic-sprites.png");
	// ringSprites = loadSprites("ring.png");
	// textTexture = loadText("NiseSegaSonic.ttf");

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // set window colour to white

    return true;
}

void Screen::shutDown()
{
	SDL_DestroyTexture(texture);
	// SDL_DestroyTexture(ringSprite);
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
	SDL_RenderPresent(renderer);
}

void Screen::draw(int x, int y, SDL_Rect sprite, bool flipSprite)
{
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	if(flipSprite == true) {
		flip = SDL_FLIP_HORIZONTAL;
	} else {
		flip = SDL_FLIP_NONE;
	}
	// SDL_FLIP_NONE, SDL_FLIP_HORIZONTAL, SDL_FLIP_VERTICAL

	// destination rectangle
	SDL_Rect dstrect = {x, y, sprite.w, sprite.h}; // x coord, y coord, image width, image height

	SDL_RenderCopyEx(renderer, texture, &sprite, &dstrect, NULL, NULL, flip);
}

void Screen::drawText(int x, int y)
{
	int texW = 0;
	int texH = 0;
	SDL_QueryTexture(textTexture, NULL, NULL, &texW, &texH);
	// destination rectangle
	SDL_Rect dstrect = {x, y, texW, texH}; // x coord, y coord, image width, image height

	SDL_RenderCopy(renderer, textTexture, NULL, &dstrect);
}

SDL_Texture* Screen::loadSprites(string file)
{
	SDL_Surface* image = nullptr;

	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", file.c_str()); // "sonic-sprites.png");

	image = IMG_Load(file.c_str()); // "sonic-sprites.png");
	texture = SDL_CreateTextureFromSurface(renderer, image);

	//delete image;
	SDL_FreeSurface(image);

	return texture;
}

SDL_Texture* Screen::loadText(string text)
{
	font = TTF_OpenFont("NiseSegaSonic.ttf", 10);
	SDL_Colour textColour = {0, 0, 0};

    //Render text surface
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), textColour);

    //Create texture from surface pixels
    textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    //Get rid of old surface
    SDL_FreeSurface(textSurface);

    //Return success
    return textTexture;
}