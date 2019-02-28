//here be dragons
#include <SDL2/SDL.h>
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
int init();
void deinit();

int init(void)
{
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		return 1;
	}
	gWindow = SDL_CreateWindow("PLACEHOLDER_TITLE", SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH,
                                WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	if(gWindow == NULL)
	{
		SDL_Quit();
		return 2;
	}
	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
	if(gRenderer == NULL)
	{
		SDL_DestroyWindow(gWindow);
		SDL_Quit();
		return 3;
	}
	return 0;
}

void deinit(void)
{
	SDL_DestroyWindow(gWindow);
	SDL_DestroyRenderer(gRenderer);
	SDL_Quit();
	gWindow = NULL;
	gRenderer = NULL;
}
