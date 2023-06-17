#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

#include <SDL.h>
#include <SDL_image.h>

// input directions
enum INPUT {
	LEFT = 1, RIGHT = 2, UP = 3, DOWN = 4, QUIT = 5
};

// sprite directions
#define SPRITE_LEFT {29, 0, 29, 39}; // x coord, y coord, image width, image height
#define SPRITE_RIGHT {0, 0, 29, 39};
#define SPRITE_UP_LEFT {29 * 3, 0, 29, 39};
#define SPRITE_UP_RIGHT {29 * 2, 0, 29, 39};
#define SPRITE_DOWN_LEFT {29 * 5, 0, 29, 39};
#define SPRITE_DOWN_RIGHT {29 * 4, 0, 29, 39};

void startUp(SDL_Window* &window, SDL_Renderer* &renderer, SDL_Surface* &image, SDL_Texture* &texture);

void render(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect &srcrect, int x, int y);
void shutDown(SDL_Window* &window, SDL_Renderer* &renderer, SDL_Texture* &texture);
int getInput();
SDL_Rect spriteDirection(int input);
void movement(int input, int &x, int &y);
