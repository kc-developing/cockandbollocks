// ayy lmao. this is the the SDL code template that I'll be working with.

#include "init.h"

int main(int argc, char *argv[])
{
	if(init() == 0) // INITIALIZE FUCKING EVERYTHING
	{
		//printf("Error initializing. %s\n", SDL_GetError());
		return -99;
	}

	deinit();
	return 0;
}
