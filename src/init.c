#include <SDL2/SDL.h>
#define WINDOW_HEIGHT 768
#define WINDOW_WIDTH 1024
#define true 1
#define false 0

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
int init();
void deinit();

int init()
{
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		return false;
	}
	gWindow = SDL_CreateWindow("PLACEHOLDER_TITLE", SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH,
                                WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	if(gWindow == NULL)
	{
		SDL_Quit();
		return false;
	}
	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
	if(gRenderer == NULL)
	{
		SDL_DestroyWindow(gWindow);
		SDL_Quit();
		return false;
	}
	return true;
}

void deinit()
{
	SDL_DestroyWindow(gWindow);
	SDL_DestroyRenderer(gRenderer);
	SDL_Quit();
	gWindow = NULL;
	gRenderer = NULL;
}
