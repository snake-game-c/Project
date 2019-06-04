#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "function.h"


// linux gcc main.c function.c $(sdl2-config --cflags --libs) -o snake
// Windows gcc -Wall src/Project/main.c src/Project/function.c -o bin/Snake -I include -L lib -lmingw32 -lSDL2main -lSDL2

void ExitWithError(char *message)
{
	SDL_Log("ERREUR %s -> %s", message,SDL_GetError());
	SDL_Quit();
	exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{	
	/*--------Initialisation de la fenêtre et du rendu--------*/

	SDL_Window *fenetre=NULL;
	SDL_Renderer *rendu=NULL; 
	srand(time(NULL));

	
	/*-----------Initilisation de la SDL-----------*/

	if (SDL_Init(SDL_INIT_EVERYTHING)!=0){
		ExitWithError("Impossible de charger la SDL");
	}

	/*-----------FENETRE-----------*/

	fenetre=SDL_CreateWindow("Jeu du Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,HEIGHT,WIDTH,0);

	if(fenetre==NULL){
		ExitWithError("Impossible de créer une fenetre");
	} 

	/*-----------RENDU-----------*/

	rendu=SDL_CreateRenderer(fenetre,-1,SDL_RENDERER_SOFTWARE);

	if (rendu==NULL){
		SDL_DestroyWindow(fenetre);
		ExitWithError("Impossible de créer un rendu");

	}
	

	/*Initialisation du Snake*/
	Snake *snake=InitialiseSnake(100,100,EAST);
	printf("(x,y)=(%d,%d)\n",snake->head->rectangle->x,snake->head->rectangle->y);
	/*----------------------*/

	/*Test des fonctions*/
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
	/*----------------------*/

	if (SDL_SetRenderDrawColor(rendu,255,255,255,255)!=0){
		SDL_Log("Erreur changement de couleur: %s\n",SDL_GetError());
	}


	PrintSnake(snake,rendu);

	/*Gestion des evenements*/

	SDL_bool program_launched=SDL_TRUE;

	while(program_launched){
		SDL_Event event;

		while(SDL_PollEvent(&event)){
			switch(event.type){    //En fonction de l'evenement 

				case SDL_QUIT:    //Croix de la fenetre
					program_launched=SDL_FALSE;
					break;

				case SDL_KEYDOWN:  //Une touche est pressee
					switch(event.key.keysym.sym){  //En fonction de la touche pressee

						case SDLK_LEFT: 
							/*Action a faire si la touche gauche est pressee*/
							printf("LEFT\n");
							MoveSnake(snake,EAST);
							break;

						case SDLK_RIGHT: 
							/*Action a faire si la touche droite est pressee*/
							printf("RIGHT\n");
							MoveSnake(snake,WEST);
							break;

						case SDLK_UP:
							/*Action a faire si la touche haute est pressee*/ 
							printf("UP\n");
							MoveSnake(snake,NORTH);
							break;
					
						case SDLK_DOWN: 
							/*Action a faire si la touche basse est pressee*/
							printf("DOWN\n");
							MoveSnake(snake,SOUTH);
							break;

						case SDLK_ESCAPE:
							program_launched=SDL_FALSE;
							break;

						default:
							break;
					}
					break;

				default:
					break;
			}

		}
	}


	/*----------------------*/


	/*Fermeture de la SDL*/
	SDL_DestroyWindow(fenetre);
	SDL_DestroyRenderer(rendu);
	SDL_Quit();
	return 0;
}
