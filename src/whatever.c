// this is just a placeholder I guess. Doesn't really do anything apart from drawing
// a .png-man on the screen with the ability to scale him up or down with '-' and '='
// keydown events. Also, pressing 'c' toggles between a sprite of a man and a benis.
// it also has some really simple collision detection with the edges of the window,
// but it only works perfectly on unscaled sprites at default sizes.

#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <time.h>
#include <stdlib.h>

#define WW 800
#define WH 600

#define MANW 50
#define MANH 50

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Surface *image = NULL;
SDL_Texture *texture = NULL;
SDL_Surface *image2 = NULL;
SDL_Texture *texture2 = NULL;

int init();
void deinit();

int main(int argc, char *argv[])
{

    if(init() != 0) return 42; // INITIALIZING FUCKING EVERYTHING


    SDL_Event key;
    SDL_Rect dest;
    dest.h = MANH; dest.w = MANW;
    dest.x = (WW / 2) - (MANW / 2); dest.y = (WH / 2) - (MANH / 2);
    int quit = 0;
    SDL_RenderCopy(renderer, texture, NULL, &dest);
    SDL_RenderPresent(renderer);
    while(quit != 1) // GAME LOOP FOR QUITTING
    {
        while(SDL_PollEvent(&key) != 0) // GAME LOOP FOR DETECTING KEY PRESSES
        {
            if(key.type == SDL_QUIT)
                quit = 1;
            else if(key.type == SDL_KEYDOWN)
            {
                if(key.key.keysym.sym == SDLK_UP)
                {
                    if(dest.y < 5)
                        continue;
                    else
                    {
                        dest.y -= 5;
                        SDL_RenderClear(renderer);
                        SDL_RenderCopy(renderer, texture, NULL, &dest);
                        SDL_RenderPresent(renderer);
                    }
                }
                else if(key.key.keysym.sym == SDLK_DOWN)
                {
                    if(dest.y+MANH+5 > WH)
                        continue;
                    else
                    {
                        dest.y += 5;
                        SDL_RenderClear(renderer);
                        SDL_RenderCopy(renderer, texture, NULL, &dest);
                        SDL_RenderPresent(renderer);
                    }
                }
                else if(key.key.keysym.sym == SDLK_LEFT)
                {
                    if(dest.x < 5)
                        continue;
                    else
                    {
                        dest.x -= 5;
                        SDL_RenderClear(renderer);
                        SDL_RenderCopy(renderer, texture, NULL, &dest);
                        SDL_RenderPresent(renderer);
                    }
                }
                else if(key.key.keysym.sym == SDLK_RIGHT)
                {
                    if(dest.x+MANW+5 > WW)
                        continue;
                    else
                    {
                        dest.x += 5;
                        SDL_RenderClear(renderer);
                        SDL_RenderCopy(renderer, texture, NULL, &dest);
                        SDL_RenderPresent(renderer);
                    }
                }
                else if(key.key.keysym.sym == SDLK_MINUS)
                {
                    dest.w -= 5;
                    dest.h -= 5;
                    SDL_RenderClear(renderer);
                    SDL_RenderCopy(renderer, texture, NULL, &dest);
                    SDL_RenderPresent(renderer);
                }
                else if(key.key.keysym.sym == SDLK_EQUALS)
                {
                    dest.w += 5;
                    dest.h += 5;
                    SDL_RenderClear(renderer);
                    SDL_RenderCopy(renderer, texture, NULL, &dest);
                    SDL_RenderPresent(renderer);

                }
                else if(key.key.keysym.sym == SDLK_c)
                {
                    SDL_RenderCopy(renderer, texture2, NULL, &dest);
                    SDL_RenderPresent(renderer);
                }
            }
        } // SECOND GAME LOOP W/ EVENT
    } // MAIN GAME LOOP END W/ QUIT

    deinit(); // DEINITIALIZE FUCKING EVERYTHING
    return 0;
}

int init()
{
    int failure = 0;
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Error #100: %s\n", SDL_GetError());
        failure = 1;
    }
    window = SDL_CreateWindow("Man Moving on Screen",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              WW, WH, SDL_WINDOW_SHOWN);
    if(!window)
    {
        printf("Error #1: %s\n", SDL_GetError());
        SDL_Quit();
        failure = 1;
    }
    Uint32 renderer_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    renderer = SDL_CreateRenderer(window, -1, renderer_flags);
    if(!renderer)
    {
        printf("Error #2: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        failure = 1;
    }
    image = IMG_Load("man.png");
    if(!image)
    {
        printf("Error #3: %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        failure = 1;
    }
    texture = SDL_CreateTextureFromSurface(renderer, image);
    if(!texture)
    {
        printf("Error #4: %s\n", SDL_GetError());

        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        failure = 1;
    }

    image2 = IMG_Load("cock.png");
    if(!image2)
    {
        printf("Error #3: %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        failure = 1;
    }
    texture2 = SDL_CreateTextureFromSurface(renderer, image2);
    if(!texture2)
    {
        printf("Error #4: %s\n", SDL_GetError());

        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        failure = 1;
    }

    return failure;
}

void deinit()
{
    SDL_FreeSurface(image);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(image2);
    SDL_DestroyTexture(texture2);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    window = NULL;
    renderer = NULL;
    image = NULL;
    texture = NULL;
}
