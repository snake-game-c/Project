#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>

#include "function.h"


// linux gcc main.c function.c $(sdl2-config --cflags --libs) -o snake

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

	fenetre=SDL_CreateWindow("Jeu du Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,900,700,0);

	if(fenetre==NULL){
		ExitWithError("Impossible de créer une fenetre");
	} 

	/*-----------RENDU-----------*/

	rendu=SDL_CreateRenderer(fenetre,-1,SDL_RENDERER_SOFTWARE);

	if (rendu==NULL){
		SDL_DestroyWindow(fenetre);
		ExitWithError("Impossible de créer un rendu");

	}

}


int main(int argc, char *argv[])
{	
	/*--------Initialisation de la fenêtre et du rendu--------*/

	//SDL_Window *fenetre=NULL;
	//SDL_Renderer *rendu=NULL; 

	//Initialise(fenetre,rendu);
	
	SnakeCell* tete=malloc(sizeof(SnakeCell));
	tete->rectangle->x=100;
	tete->rectangle->y=100;
	tete->direction =EAST;
	tete->next=NULL;
	Snake* snake=malloc(sizeof(Snake));
	snake->head=tete;
	snake->length=0;
	PrintSnakeConsole(snake);
	printf("Add Case \n");
	snake=AddRectangle(snake);
	PrintSnakeConsole(snake);
	printf("Move SOUTH\n");
	snake=MoveSnake(snake,SOUTH);
	PrintSnakeConsole(snake);
	printf("Add 2 Cases \n");
	snake=AddRectangle(snake);
	snake=AddRectangle(snake);
	PrintSnakeConsole(snake);
	printf("Move WEST\n");
	snake=MoveSnake(snake,WEST);
	PrintSnakeConsole(snake);

	/*Execution du programme*/
	//SDL_Delay(3000);
	//SDL_DestroyWindow(fenetre);
	//SDL_DestroyRenderer(rendu);
	//SDL_Quit();
	return 0;
}
