// FOR TESTING & LEARNING
// draw a snowfall on a black background with 6000 randomized snowflakes with a sprite scrolling through the window (spurdo.png).
// this was just a test to see the difference between software rendering vs hardware rendering
// also tested a bunch of addons like SDL_Image->IMG_Load stuff earlier which will come in handy for the game l8r
// for loading complex sprites and shit.
// compile with gcc -std=c11 -fmax-errors=10 -Wextra main.c -lmingw32 -lSDL2main -lSDL2 -o game.exe

#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define WINDOW_HEIGHT 768
#define WINDOW_WIDTH 1024
#define INITIAL_TITLE "Snowfall"
#define SNOW 6000
#define FIFTYFIFTY if(rand() % 2 == 0)

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Surface* gSurface = NULL;
SDL_Texture* gTexture = NULL;

typedef struct
{
	short pointx;
	short pointy;
	short speed;
	bool wheezel;
	bool wheezer;
}flake;

bool init();
void deinit();

int main(int argc, char *argv[])
{
	if(init() == false) // INITIALIZE FUCKING EVERYTHING
	{
		//printf("Error initializing. %s\n", SDL_GetError());
		return -99;
	}
	flake snow[SNOW];
	time_t t;
	SDL_Rect dest;
	dest.h = 226;
	dest.w = 343;
	dest.x = -1000;
	dest.y = WINDOW_HEIGHT / 2 - 75;
	SDL_Event key;
	srand((unsigned) time(&t));
	for(int i = 0; i < SNOW; i++)
	{
		snow[i].pointx = rand() % WINDOW_WIDTH;
		snow[i].pointy = rand() % WINDOW_HEIGHT + rand() % (WINDOW_HEIGHT / 2) - WINDOW_HEIGHT/10;
		snow[i].speed = rand() % 4;
		if(snow[i].speed == 0) 
			snow[i].speed++;
		snow[i].wheezel = rand() % 2;
		if(snow[i].wheezel != 1)
			snow[i].wheezer = rand() % 2;
	}
	SDL_PollEvent(&key);
	for( ; key.type != SDL_QUIT; SDL_PollEvent(&key)) // game loop. using for instead of while because huge nested loops are stupid and gay, plus less clutter
	{
		SDL_RenderClear(gRenderer);
		SDL_RenderCopy(gRenderer, gTexture, NULL, &dest);
		dest.x += 10;
		if(dest.x > WINDOW_WIDTH+50)
		{
			dest.x = -1000;
			dest.y = rand() % WINDOW_HEIGHT - 100;
		}
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		for(int i = 0; i < SNOW; i++) // in this loop we draw snowflakes
		{
			SDL_RenderDrawPoint(gRenderer, snow[i].pointx, snow[i].pointy);
			snow[i].pointy += snow[i].speed;
			if(snow[i].wheezel == true)
				FIFTYFIFTY snow[i].pointx++;
			if(snow[i].wheezer == true)
				FIFTYFIFTY snow[i].pointx--;
			if(snow[i].pointy > WINDOW_HEIGHT)
			{
				snow[i].pointy = -(rand() % WINDOW_HEIGHT);
				snow[i].pointx = rand() % WINDOW_WIDTH;
			}
			if(snow[i].pointx > WINDOW_WIDTH)
			{
				snow[i].pointx = 0;
			}
			else if(snow[i].pointx < 0)
			{
				snow[i].pointx = WINDOW_WIDTH;
			}
		}
		SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
		SDL_RenderPresent(gRenderer);
		SDL_Delay(33); // 30 FRAMES PER SECOND
	}
	deinit();
	return 0;
}

bool init()
{
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		return false;
	}
	gWindow = SDL_CreateWindow(INITIAL_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	if(gWindow == NULL)
	{
		SDL_Quit();
		return false;
	}
	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
	if(gRenderer == NULL)
	{
		SDL_DestroyWindow(gWindow);
		SDL_Quit;
		return false;
	}
	gSurface = SDL_LoadBMP("spurdo.bmp");
	gTexture = SDL_CreateTextureFromSurface(gRenderer, gSurface);
	SDL_FreeSurface(gSurface);
	gSurface = NULL;
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
	return true;
}

void deinit()
{
	SDL_DestroyWindow(gWindow);
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyTexture(gTexture);
	SDL_Quit();
	gWindow = NULL;
	gRenderer = NULL;
	gTexture = NULL;
}
