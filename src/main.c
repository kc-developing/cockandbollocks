// ayy lmao. this is the the SDL code template that I'll be working with.
// compile with just bare-bones gcc main.c init.c -lSDL2 -lSDL2main -o game

#include "init.h"

int main(int argc, char *argv[])
{
	if(init() != 0) // INITIALIZE FUCKING EVERYTHING
	{
		//printf("Error initializing. %s\n", SDL_GetError());
		return -99;
	}

	deinit();
	return 0;
}
