// infinite sidescroll/platform test
// player can jump and walk around. sprite changes while walking to imitate """""animation"""""
// compile with gcc -std=c11 -fmax-errors=10 -Wextra main.c -lmingw32 -lSDL2main -lSDL2 -o game.exe

#include <SDL2/SDL.h>

#define WINDOW_HEIGHT 768
#define WINDOW_WIDTH 1024
#define INITIAL_TITLE "Snowfall"
#define true 1
#define false 0

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Surface* gSurfaceBG = NULL;
SDL_Surface* gSurfacePL1 = NULL;
SDL_Surface* gSurfacePL2 = NULL;
short playerW = 0;
short playerH = 0;
SDL_Texture* gTextureBG = NULL;
SDL_Texture* gTexturePL1 = NULL;
SDL_Texture* gTexturePL2 = NULL;
short alternator = 0;
int init();
void deinit();

int main(int argc, char *argv[])
{
	if(init() == false) // INITIALIZE FUCKING EVERYTHING
	{
		//printf("Error initializing. %s\n", SDL_GetError());
		return -99;
	}
	SDL_Event key;
	SDL_Rect playerRect = {100, 500, 150, 150};
	int jumped = false, moving = false;
	for(SDL_PollEvent(&key); key.type != SDL_QUIT; SDL_PollEvent(&key)) // game loop
	{
		SDL_RenderClear(gRenderer);
		SDL_RenderCopy(gRenderer, gTextureBG, NULL, NULL);
		
		if(moving == true || jumped == true)
		{
			if(alternator < 15)
				SDL_RenderCopy(gRenderer, gTexturePL1, NULL, &playerRect);
			else
				SDL_RenderCopy(gRenderer, gTexturePL2, NULL, &playerRect);
		}
		else
			SDL_RenderCopy(gRenderer, gTexturePL1, NULL, &playerRect);
		if(key.type == SDL_KEYDOWN)
		{
			switch(key.key.keysym.sym)
			{
				case SDLK_LEFT:
					playerRect.x -= 2;
					moving = true;
					break;
				case SDLK_RIGHT:
					playerRect.x += 2;
					moving = true;
					break;
				case SDLK_SPACE:
					if(jumped == false)
					jumped = true;
					break;
			} 
		}
		else if(key.type == SDL_KEYUP)
		{
			key.key.keysym.sym = 0;
			moving = false;
		}
		//jump
		if(jumped == true)
		{
			playerRect.y -= 5;
			if(playerRect.y < 400)
			{
				jumped = false;
			}
		}
		else if(jumped == false && playerRect.y != 500)
			playerRect.y += 5;
		//endjump
		if(playerRect.x > WINDOW_WIDTH + 150)
			playerRect.x = -150;
		SDL_RenderPresent(gRenderer);
		SDL_Delay(15); // ~60 FRAMES PER SECOND
		alternator++;
		if(alternator > 30)
			alternator = 0;
	}
	deinit();
	return 0;
}

int init()
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
	gSurfacePL1 = SDL_LoadBMP("player.bmp");
	gSurfacePL2 = SDL_LoadBMP("player_two.bmp");
	gSurfaceBG = SDL_LoadBMP("background.bmp");
	SDL_SetColorKey(gSurfacePL1, SDL_TRUE, SDL_MapRGB(gSurfacePL1->format, 0xC0, 0xC0, 0xC0));
	SDL_SetColorKey(gSurfacePL2, SDL_TRUE, SDL_MapRGB(gSurfacePL2->format, 0xC0, 0xC0, 0xC0));
	gTexturePL1 = SDL_CreateTextureFromSurface(gRenderer, gSurfacePL1);
	gTexturePL2 = SDL_CreateTextureFromSurface(gRenderer, gSurfacePL2);
	playerH = gSurfacePL1->h;
	playerW = gSurfacePL1->w;
	gTextureBG = SDL_CreateTextureFromSurface(gRenderer, gSurfaceBG);
	SDL_FreeSurface(gSurfacePL1);
	SDL_FreeSurface(gSurfacePL2);
	SDL_FreeSurface(gSurfaceBG);
	if(!gTextureBG || !gTexturePL1 || !gTexturePL2)
		return false;
	gSurfacePL1 = NULL;
	gSurfacePL2 = NULL;
	gSurfaceBG = NULL;
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
	return true;
}

void deinit()
{
	SDL_DestroyWindow(gWindow);
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyTexture(gTextureBG);
	SDL_DestroyTexture(gTexturePL1);
	SDL_DestroyTexture(gTexturePL2);
	SDL_Quit();
	gWindow = NULL;
	gRenderer = NULL;
	gTexturePL1 = NULL;
	gTexturePL2 = NULL;
	gTextureBG = NULL;
}
