#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>

#include "function.h"

void ExitWithError(char *message)
{
	SDL_Log("ERREUR %s -> %s", message,SDL_GetError());
	SDL_Quit();
	exit(EXIT_FAILURE);
}

void Initialise(SDL_Window *fenetre, SDL_Renderer *rendu)
{
	/*-----------Initilisation de la SDL-----------*/

	if (SDL_Init(SDL_INIT_EVERYTHING)!=0){
		ExitWithError("Impossible de charger la SDL");
	}

	/*-----------FENETRE-----------*/

	fenetre=SDL_Window("Jeu du Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,900,700,0);

	if(fenetre==NULL){
		ExitWithError("Impossible de créer une fenetre");
	} 

	/*-----------RENDU-----------*/

	rendu=SDL_CreateRenderer(fenetre,-1,SDL_RENDERER_ACCELERATED);

	if (rendu==NULL){
		SDL_DestroyWindow(fenetre);
		ExitWithError("Impossible de créer un rendu");

	}

}


int main(int argc, char *argv[])
{	
	/*--------Initialisation de la fenêtre et du rendu--------*/

	SDL_Window *fenetre=NULL;
	SDL_Renderer *rendu=NULL; 

	Initialise(fenetre,rendu);


	/*Execution du programme*/

	SDL_DestroyWindow(fenetre);
	SDL_DestroyRenderer(rendu);
	SDL_Quit();

	return 0;
}