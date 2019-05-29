#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>

void ExitWithError(char *message){
	SDL_Log("ERREUR %s -> %s", message,SDL_GetError());
	SDL_Quit();
	exit(EXIT_FAILURE);
}




int main(int argc, char *argv[])
{
	if (SDL_Init(SDL_INIT_EVERYTHING)!=0){
		SDL_Log("ERREUR %s")

	}


	SDL_Quit();

	return 0;
}